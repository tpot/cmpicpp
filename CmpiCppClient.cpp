//
// Copyright (C) 2009 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "CmpiCpp.h"
#include "CmpiCppClient.h"
#include "CmpiCppClientUtils.h"

#include "XMLTextReader.h"
#include "XMLTextWriter.h"

#include <sstream>

#include <sys/un.h>
#include <curl/curl.h>
#include <libxml/xmlreader.h>

using namespace std;
using namespace CmpiCpp;

// Open an AF_UNIX socket callback fn.  Taken from Bart's sfcc patch at:
//
// http://sf.net/tracker/?func=detail&aid=1956407&group_id=128809&atid=712784

static curl_socket_t 
_opensockCB(void *clientp, curlsocktype, struct curl_sockaddr *caddr)
{
    const char* path = (const char*)clientp;
    struct sockaddr_un* unaddr = (struct sockaddr_un*)&caddr->addr;

    caddr->family = AF_UNIX; 
    caddr->addrlen = sizeof(struct sockaddr_un);

    /* This is actually safe.  caddr is padded.  See singleipconnect()
     * in lib/connect.c within libcurl for details */ 

    memset(unaddr, 0, caddr->addrlen);
    unaddr->sun_family = AF_UNIX;
    strncpy(unaddr->sun_path, path, sizeof(unaddr->sun_path));
    caddr->protocol = 0; 

    return socket(caddr->family, caddr->socktype, caddr->protocol);
}

CmpiCppClient::CmpiCppClient(const CMPIBroker *broker, const string &socketPath)
    : _broker(broker), _socketPath(socketPath)
{
    // Initialise curl handle

    _handle = curl_easy_init();

    curl_easy_setopt(_handle, CURLOPT_URL, "http://127.0.0.1"); // Dummy URL

    curl_easy_setopt(_handle, CURLOPT_OPENSOCKETDATA, socketPath.c_str());
    curl_easy_setopt(_handle, CURLOPT_OPENSOCKETFUNCTION, _opensockCB);

    _curl_common_init();
}

CmpiCppClient::
CmpiCppClient(const CMPIBroker *broker, const string &url, 
              const string &user, const string &pass)
    : _broker(broker), _url(url), _user(user), _pass(pass)
{
    // Initialise curl handle

    _handle = curl_easy_init();

    curl_easy_setopt(_handle, CURLOPT_URL, url.c_str());

    stringstream creds;

    creds << user << ":" << pass;

    curl_easy_setopt(_handle, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
    curl_easy_setopt(_handle, CURLOPT_USERPWD, creds.str().c_str());

    _curl_common_init();
}
        
CmpiCppClient::~CmpiCppClient()
{
    curl_easy_cleanup(_handle);
}

void
CmpiCppClient::_curl_common_init()
{
    curl_easy_setopt(_handle, CURLOPT_POST, 1);
    curl_easy_setopt(_handle, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(_handle, CURLOPT_FAILONERROR, 1);
    curl_easy_setopt(_handle, CURLOPT_TIMEOUT_MS, 10000);
    curl_easy_setopt(_handle, CURLOPT_NOSIGNAL, 1);
}

// Make some common HTTP headers

struct curl_slist *
CmpiCppClient::_makeHeaders()
{
    struct curl_slist *headers = NULL;

    headers = curl_slist_append
        (headers,"Content-type: application/xml; charset=\"utf-8\"");

    headers = curl_slist_append(headers, "CIMProtocolVersion: 1.0");    
    headers = curl_slist_append(headers, "CIMOperation: MethodCall");

    return headers;
}

// Append received data to a string passed in the stream arg

static size_t 
storeData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    string *buffer = (string *)stream;

    string data((const char *)ptr, size * nmemb);
    buffer->append(data);

    return size * nmemb;
}

// Convert a vector of strings to a CmpiArray

CmpiArray 
CmpiCppClient::_convertArray(const string &type, const vector<string> &data)
{
    // Create array

    CMPIType arrayType = CMPI_string;

    if (type == "boolean") arrayType = CMPI_boolean;
    else if (type == "string") arrayType = CMPI_string;
    else if (type == "uint8") arrayType = CMPI_uint8;
    else if (type == "sint8") arrayType = CMPI_sint8;
    else if (type == "uint16") arrayType = CMPI_uint16;
    else if (type == "sint16") arrayType = CMPI_sint16;
    else if (type == "uint32") arrayType = CMPI_uint32;
    else if (type == "sint32") arrayType = CMPI_sint32;
    else if (type == "uint64") arrayType = CMPI_uint64;
    else if (type == "sint64") arrayType = CMPI_sint64;

    // TODO: real32, real64, dateTime
    
    CmpiArray array(makeCmpiArray(_broker, data.size(), arrayType));

    // Populate array values

    for (unsigned int i = 0; i < data.size(); i++)
        switch (arrayType) {
        case CMPI_boolean:
            array.setElementAt(i, data[i] == "TRUE");
            break;
        case CMPI_string:
            array.setElementAt(i, data[i]);
            break;
        case CMPI_uint8:
            array.setElementAt
                (i, (CMPIUint8)strtoul(data[i].c_str(), NULL, 10));
            break;
        case CMPI_sint8:
            array.setElementAt
                (i, (CMPISint8)strtol(data[i].c_str(), NULL, 10));
            break;
        case CMPI_uint16:
            array.setElementAt
                (i, (CMPIUint16)strtoul(data[i].c_str(), NULL, 10));
            break;
        case CMPI_sint16:
            array.setElementAt
                (i, (CMPISint16)strtol(data[i].c_str(), NULL, 10));
            break;
        case CMPI_uint32:
            array.setElementAt
                (i, (CMPIUint32)strtoul(data[i].c_str(), NULL, 10));
            break;
        case CMPI_sint32:
            array.setElementAt
                (i, (CMPISint32)strtol(data[i].c_str(), NULL, 10));
            break;
        case CMPI_uint64:
            array.setElementAt
                (i, (CMPIUint64)strtoull(data[i].c_str(), NULL, 10));
            break;
        case CMPI_sint64:
            array.setElementAt
                (i, (CMPISint64)strtoll(data[i].c_str(), NULL, 10));
            break;
    }

    return array;
}

static void
_writeObjectPath(XMLTextWriter &w, const CmpiObjectPath &path)
{
    w.startElement("INSTANCENAME");
    w.writeAttribute("CLASSNAME", path.getClassName());

    for (unsigned int i = 0; i < path.getKeyCount(); i++) {

        pair<CmpiName, CmpiData> key(path.getKeyAt(i));

        w.startElement("KEYBINDING");
        w.writeAttribute("NAME", key.first.str());

        w.startElement("KEYVALUE");
        w.writeAttribute("VALUETYPE", CmpiData::typeToString(key.second.getType()));

        xmlTextWriterWriteString(w.getWriter(), BAD_CAST key.second.str().c_str());

        w.endElement();         // KEYVALUE
        w.endElement();         // KEYBINDING
    }

    w.endElement();             // INSTANCENAME
}

static void 
_writeLocalNamespacePath(XMLTextWriter &w, const CmpiName &nameSpace)
{
    w.startElement("LOCALNAMESPACEPATH");

    string ns(nameSpace.str());
    string::size_type ndx = 0, ndx2;

    while ((ndx2 = ns.find('/', ndx)) != string::npos) {
        w.startElement("NAMESPACE");
        w.writeAttribute("NAME", ns.substr(ndx, ndx2 - ndx));
        w.endElement();             
        ndx = ndx2 + 1;
    }

    w.startElement("NAMESPACE");
    w.writeAttribute("NAME", ns.substr(ndx));
    w.endElement(); // NAMESPACE
            
    w.endElement(); // LOCALNAMESPACEPATH
}

pair<unsigned int,string>
CmpiCppClient::_processError(XMLTextReader &reader)
{
    string code(reader.getAttribute("CODE"));
    string description(reader.getAttribute("DESCRIPTION"));
    
    int ret = reader.read();

    string value;

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_END_ELEMENT && name == "ERROR")
            break;

        ret = reader.read();
    }

    return make_pair(strtoul(code.c_str(), NULL, 10), description);
}

// Parse a KEYVALUE element into a tuple of (valuetype, value)

pair<string,string>
CmpiCppClient::_processKeyvalue(XMLTextReader &reader)
{
    string valueType(reader.getAttribute("VALUETYPE"));

    int ret = reader.read();

    string value;

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_END_ELEMENT && name == "KEYVALUE")
            break;

        if (nodeType == XML_READER_TYPE_TEXT)
            value.assign(reader.nodeValue());

        ret = reader.read();
    }

    return make_pair(valueType, value);
}

void
CmpiCppClient::_processKeybinding(XMLTextReader &reader, CmpiObjectPath &path)
{
    string keyname(reader.getAttribute("NAME"));

    int ret = reader.read();

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_END_ELEMENT && name == "KEYBINDING")
            break;

        if (nodeType == XML_READER_TYPE_ELEMENT && name == "KEYVALUE") {
            pair<string,string> keyvalue = _processKeyvalue(reader);
            path.addKey(keyname, keyvalue.second);
        }

        ret = reader.read();
    }
}

string 
CmpiCppClient::_processValue(XMLTextReader &reader)
{
    string result;

    int ret = reader.read();

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_END_ELEMENT && name == "VALUE")
            break;

        if (nodeType == XML_READER_TYPE_TEXT)
            result.assign(reader.nodeValue());

        ret = reader.read();
    }

    return result;
}

vector<string>
CmpiCppClient::_processValueArray(XMLTextReader &reader)
{
    vector<string> result;

    int ret = reader.read();

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_END_ELEMENT && name == "VALUE.ARRAY")
            break;

        if (nodeType == XML_READER_TYPE_ELEMENT && name == "VALUE")
            result.push_back(_processValue(reader));

        ret = reader.read();
    }

    return result;
}

void
CmpiCppClient::_processProperty(XMLTextReader &reader, CmpiInstance &inst)
{
    string propname(reader.getAttribute("NAME"));
    string proptype(reader.getAttribute("TYPE"));

    string value;

    int ret = reader.read();

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_END_ELEMENT && name == "PROPERTY")
            break;

        if (nodeType == XML_READER_TYPE_ELEMENT && name == "VALUE") {
            string propvalue = _processValue(reader);

            // TODO: real32, real64, dateTime

            if (proptype == "boolean")
                inst.addProperty(propname, propvalue == "TRUE");
            else if (proptype == "uint8")
                inst.addProperty
                    (propname, (CMPIUint8)strtoul(propvalue.c_str(), NULL, 10));
            else if (proptype == "sint8") 
                inst.addProperty
                    (propname, (CMPISint8)strtol(propvalue.c_str(), NULL, 10));
            else if (proptype == "uint16") 
                inst.addProperty
                    (propname, (CMPIUint16)strtoul(propvalue.c_str(), NULL,10));
            else if (proptype == "sint16") 
                inst.addProperty
                    (propname, (CMPISint16)strtol(propvalue.c_str(), NULL, 10));
            else if (proptype == "uint32") 
                inst.addProperty
                    (propname, (CMPIUint32)strtoul(propvalue.c_str(), NULL,10));
            else if (proptype == "sint32") 
                inst.addProperty
                    (propname, (CMPISint32)strtol(propvalue.c_str(), NULL, 10));
            else if (proptype == "uint64") 
                inst.addProperty
                    (propname, (CMPIUint64)strtoull(propvalue.c_str(),NULL,10));
            else if (proptype == "sint64") 
                inst.addProperty
                    (propname, (CMPISint64)strtoull(propvalue.c_str(),NULL,10));
            else
                inst.addProperty(propname, propvalue);
        }

        ret = reader.read();
    }
}

void 
CmpiCppClient::_processPropertyArray(XMLTextReader &reader, CmpiInstance &inst)
{
    string propname(reader.getAttribute("NAME"));
    string proptype(reader.getAttribute("TYPE"));

    int ret = reader.read();

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_END_ELEMENT && name == "PROPERTY.ARRAY")
            break;

        if (nodeType == XML_READER_TYPE_ELEMENT && name == "VALUE.ARRAY") {
            vector<string> propvalue = _processValueArray(reader);

            CmpiArray array(_convertArray(proptype, propvalue));

            inst.addProperty(propname, array);
        }

        ret = reader.read();
    }
}

void
CmpiCppClient::_processInstanceName(XMLTextReader &reader, CmpiObjectPath &path)
{
    string className(reader.getAttribute("CLASSNAME"));

    path.setClassName(className);

    int ret = reader.read();

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_END_ELEMENT && name == "INSTANCENAME")
            break;

        if (nodeType == XML_READER_TYPE_ELEMENT && name == "KEYBINDING")
            _processKeybinding(reader, path);

        ret = reader.read();
    }
}

CmpiName
CmpiCppClient::_processInstance(XMLTextReader &reader, CmpiInstance &inst)
{
    string className(reader.getAttribute("CLASSNAME"));

    int ret = reader.read();    

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_END_ELEMENT && name == "INSTANCE")
            break;

        if (nodeType == XML_READER_TYPE_ELEMENT && name == "PROPERTY")
            _processProperty(reader, inst);

        if (nodeType == XML_READER_TYPE_ELEMENT && name == "PROPERTY.ARRAY")
            _processPropertyArray(reader, inst);

        ret = reader.read();
    }

    return className;
}

CmpiInstance
CmpiCppClient::_processValueNamedInstance(XMLTextReader &reader,
                                          const CmpiName &nameSpace)
{
    int ret = reader.read();

    CmpiObjectPath path(makeCmpiObjectPath(_broker));
    path.setNameSpace(nameSpace);

    CmpiInstance inst(makeCmpiInstance(_broker, path));

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_END_ELEMENT && name == 
                "VALUE.NAMEDINSTANCE")
            break;

        if (nodeType == XML_READER_TYPE_ELEMENT && name == "INSTANCENAME")
            _processInstanceName(reader, path);

        if (nodeType == XML_READER_TYPE_ELEMENT && name == "INSTANCE")
            _processInstance(reader, inst);

        ret = reader.read();
    }

    inst.setPath(path);

    return inst;
}

string
CmpiCppClient::_makeGetInstanceRequest(const CmpiObjectPath &path)
{
    xmlBuffer *buf = xmlBufferCreate();
    xmlTextWriter *writer = xmlNewTextWriterMemory(buf, 0);
    XMLTextWriter w(writer);

    w.startDocument();

    w.startElement("CIM");

    w.writeAttribute("CIMVERSION", "2.0");
    w.writeAttribute("DTDVERSION", "2.0");

    w.startElement("MESSAGE");

    w.writeAttribute("ID", 1234);
    w.writeAttribute("PROTOCOLVERSION", "1.0");
    
    w.startElement("SIMPLEREQ");

    w.startElement("IMETHODCALL");
    
    w.writeAttribute("NAME", "GetInstance");

    _writeLocalNamespacePath(w, path.getNameSpace());

    w.startElement("IPARAMVALUE");

    w.writeAttribute("NAME", "LocalOnly");

    w.startElement("VALUE");
    xmlTextWriterWriteString(writer, BAD_CAST "FALSE");
    w.endElement();             // VALUE

    w.endElement();             // IPARAMVALUE

    w.startElement("IPARAMVALUE");

    w.writeAttribute("NAME", "InstanceName");

    _writeObjectPath(w, path);

    w.endElement();             // IPARAMVALUE

    w.endElement();             // IMETHODCALL
    w.endElement();             // SIMPLEREQ
    w.endElement();             // MESSAGE
    w.endElement();             // CIM

    w.endDocument();

    string result((const char *)buf->content);

    xmlBufferFree(buf);

    return result;
}

string
CmpiCppClient::_makeEnumerateInstancesRequest(const CmpiObjectPath &path)
{
    xmlBuffer *buf = xmlBufferCreate();
    xmlTextWriter *writer = xmlNewTextWriterMemory(buf, 0);
    XMLTextWriter w(writer);

    w.startDocument();

    w.startElement("CIM");

    w.writeAttribute("CIMVERSION", "2.0");
    w.writeAttribute("DTDVERSION", "2.0");

    w.startElement("MESSAGE");

    w.writeAttribute("ID", 1234);
    w.writeAttribute("PROTOCOLVERSION", "1.0");
    
    w.startElement("SIMPLEREQ");

    w.startElement("IMETHODCALL");
    
    w.writeAttribute("NAME", "EnumerateInstances");

    _writeLocalNamespacePath(w, path.getNameSpace());

    w.startElement("IPARAMVALUE");

    w.writeAttribute("NAME", "ClassName");

    w.startElement("CLASSNAME");
    w.writeAttribute("NAME", path.getClassName().str());

    w.endElement();             // CLASSNAME

    w.endElement();             // IPARAMVALUE

    w.endElement();             // IMETHODCALL
    w.endElement();             // SIMPLEREQ
    w.endElement();             // MESSAGE
    w.endElement();             // CIM

    w.endDocument();

    string result((const char *)buf->content);

    xmlBufferFree(buf);

    return result;
}

CmpiInstance
CmpiCppClient::_parseGetInstanceResponse(const string &data,
                                         const CmpiName &nameSpace)
{
    xmlTextReader *r =
        xmlReaderForMemory(data.c_str(), data.size(), NULL, NULL,
                           XML_PARSE_NONET | XML_PARSE_NOBLANKS);

    XMLTextReader reader(r);

    int ret = reader.read();

    CmpiObjectPath path(makeCmpiObjectPath(_broker));    
    CmpiInstance inst(makeCmpiInstance(_broker, path));

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_ELEMENT && name == "ERROR") {
            pair<unsigned int,string> error = _processError(reader);
            throw CmpiStatus(CMPIrc(error.first), error.second);
        }
        
        if (nodeType == XML_READER_TYPE_ELEMENT && name == "INSTANCE") {
            CmpiName className = _processInstance(reader, inst);
            path.setNameSpace(nameSpace);
            path.setClassName(className);
            inst.setPath(path);
        }
        
        ret = reader.read();        
    }

    return inst;
}

vector<CmpiInstance>
CmpiCppClient::_parseEnumerateInstancesResponse(const string &data,
                                                const CmpiName &nameSpace)
{
    xmlTextReader *r =
        xmlReaderForMemory(data.c_str(), data.size(), NULL, NULL,
                           XML_PARSE_NONET | XML_PARSE_NOBLANKS);

    XMLTextReader reader(r);

    int ret = reader.read();

    vector<CmpiInstance> result;

    while (ret == 1) {

        int nodeType = reader.nodeType();
        string name(reader.nodeName());

        if (nodeType == XML_READER_TYPE_ELEMENT && name == "ERROR") {
            pair<unsigned int,string> error = _processError(reader);
            throw CmpiStatus(CMPIrc(error.first), error.second);
        }

        if (nodeType == XML_READER_TYPE_ELEMENT && name =="VALUE.NAMEDINSTANCE")
            result.push_back(_processValueNamedInstance(reader, nameSpace));

        ret = reader.read();
    }

    return result;
}

CmpiEnumeration 
CmpiCppClient::enumInstances(const CmpiContext &, // context
                             const CmpiObjectPath &path,
                             const char **)          // properties
{
    // Add HTTP headers to request

    struct curl_slist *headers = _makeHeaders();

    headers = curl_slist_append(headers, "CIMMethod: EnumerateInstances");

    curl_easy_setopt(_handle, CURLOPT_HTTPHEADER, headers);

    // Add payload

    string payload(_makeEnumerateInstancesRequest(path));

    curl_easy_setopt(_handle, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(_handle, CURLOPT_POSTFIELDSIZE, payload.size());

    // Setup callbacks to store received data

    string response_header, response_payload;

    curl_easy_setopt(_handle, CURLOPT_HEADERFUNCTION, storeData);
    curl_easy_setopt(_handle, CURLOPT_HEADERDATA, &response_header);

    curl_easy_setopt(_handle, CURLOPT_WRITEFUNCTION, storeData);
    curl_easy_setopt(_handle, CURLOPT_WRITEDATA, &response_payload);
    
    // Perform operation

    CURLcode rv;

    rv = curl_easy_perform(_handle);

    if (rv)
        throw CmpiStatus(CMPI_RC_ERR_FAILED, curl_easy_strerror(rv));

    // Parse and return result

    vector<CmpiInstance> result
        (_parseEnumerateInstancesResponse(response_payload, 
                                          path.getNameSpace()));

    InstanceVectorEnumeration *e = new InstanceVectorEnumeration(result);

    return CmpiEnumeration(e->toCMPI());
}

CmpiInstance 
CmpiCppClient::getInstance(const CmpiContext &, const CmpiObjectPath &path, 
                           const char **)
{
    // Add HTTP headers to request

    struct curl_slist *headers = _makeHeaders();

    headers = curl_slist_append(headers, "CIMMethod: GetInstance");

    curl_easy_setopt(_handle, CURLOPT_HTTPHEADER, headers);

    // Add payload

    string payload(_makeGetInstanceRequest(path));

    curl_easy_setopt(_handle, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(_handle, CURLOPT_POSTFIELDSIZE, payload.size());

    // Setup callbacks to store received data

    string response_header, response_payload;

    curl_easy_setopt(_handle, CURLOPT_HEADERFUNCTION, storeData);
    curl_easy_setopt(_handle, CURLOPT_HEADERDATA, &response_header);

    curl_easy_setopt(_handle, CURLOPT_WRITEFUNCTION, storeData);
    curl_easy_setopt(_handle, CURLOPT_WRITEDATA, &response_payload);
    
    // Perform operation

    CURLcode rv;

    rv = curl_easy_perform(_handle);

    if (rv)
        throw CmpiStatus(CMPI_RC_ERR_FAILED, curl_easy_strerror(rv));

    // Parse and return result

    return _parseGetInstanceResponse(response_payload, path.getNameSpace());
}

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
