//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include <sstream>

#include "cmpift.h"

#include "CmpiData.h"
#include "CmpiName.h"
#include "CmpiArray.h"
#include "CmpiStatus.h"
#include "CmpiInstance.h"
#include "CmpiDateTime.h"
#include "CmpiObjectPath.h"

using namespace std;
using namespace CmpiCpp;

CmpiInstance::CmpiInstance(const CMPIInstance *obj)
{
    _data = const_cast<CMPIInstance *>(obj);
    _wasCloned = false;
}

CmpiInstance::CmpiInstance(const CmpiInstance &obj)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    _data = obj._data->ft->clone(obj._data, &status);
    _wasCloned = true;

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiInstance::~CmpiInstance()
{
    // Don't check return value and throw an exception - it's a pretty
    // bad idea.   

    if (_wasCloned)
       _data->ft->release(_data);
}

CmpiObjectPath CmpiInstance::getPath() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    CMPIObjectPath *path = _data->ft->getObjectPath(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiObjectPath result(path);

    return result;
}

void CmpiInstance::setPath(const CmpiObjectPath &path)
{
    CMPIStatus status = _data->ft->setObjectPath(_data, path.toCMPI());

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiName CmpiInstance::getHost() const
{
    return getPath().getHost();
}

CmpiName CmpiInstance::getNameSpace() const
{
    return getPath().getNameSpace();
}

CmpiName CmpiInstance::getClassName() const
{
    return getPath().getClassName();
}

void CmpiInstance::addProperty(const CmpiName &key, CMPIUint8 value)
{
    CMPIData d;

    d.type = CMPI_uint8;
    d.state = CMPI_goodValue;
    d.value.uint8 = value;

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type); 

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, CMPISint8 value)
{
    CMPIData d;

    d.type = CMPI_sint8;
    d.state = CMPI_goodValue;
    d.value.sint8 = value;

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type); 

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, CMPIUint16 value)
{
    CMPIData d;

    d.type = CMPI_uint16;
    d.state = CMPI_goodValue;
    d.value.uint16 = value;

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type); 

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, CMPISint16 value)
{
    CMPIData d;

    d.type = CMPI_sint16;
    d.state = CMPI_goodValue;
    d.value.sint16 = value;

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type); 

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, CMPIUint32 value)
{
    CMPIData d;

    d.type = CMPI_uint32;
    d.state = CMPI_goodValue;
    d.value.uint32 = value;

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type); 

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, CMPISint32 value)
{
    CMPIData d;

    d.type = CMPI_sint32;
    d.state = CMPI_goodValue;
    d.value.sint32 = value;

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type); 

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, CMPIUint64 value)
{
    CMPIData d;

    d.type = CMPI_uint64;
    d.state = CMPI_goodValue;
    d.value.uint64 = value;

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type); 

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, CMPISint64 value)
{
    CMPIData d;

    d.type = CMPI_sint64;
    d.state = CMPI_goodValue;
    d.value.sint64 = value;

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type); 

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, CMPIReal32 value)
{
    CMPIData d;

    d.type = CMPI_real32;
    d.state = CMPI_goodValue;
    d.value.real32 = value;

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type); 

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, CMPIReal64 value)
{
    CMPIData d;

    d.type = CMPI_real64;
    d.state = CMPI_goodValue;
    d.value.real64 = value;

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type); 

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, bool value)
{
    CMPIData d;

    d.type = CMPI_boolean;
    d.state = CMPI_goodValue;
    d.value.boolean = value;

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type); 

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, const char *value)
{
    CMPIStatus status =
        _data->ft->setProperty (_data, key.str().c_str(),
                                reinterpret_cast<const CMPIValue *>(value),
                                CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, const string &value)
{
    CMPIStatus status = 
        _data->ft->setProperty(_data, key.str().c_str(),
                               reinterpret_cast<const CMPIValue *>(value.c_str()),
                               CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, const stringstream &value)
{
    // Calling addProperty() of a stringstream instead of calling
    // stringstream.str() is an easy mistake to make and unfortunately
    // this is cast to a bool by the compiler.

    CMPIStatus status = 
        _data->ft->setProperty(
            _data, key.str().c_str(),
            reinterpret_cast<const CMPIValue *>(value.str().c_str()),
            CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiInstance::addProperty(const CmpiName &key, const CmpiObjectPath &value)
{
    CMPIData d;

    d.type = CMPI_ref;
    d.state = CMPI_goodValue;
    d.value.ref = value.toCMPI();

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, const CmpiArray &value)
{
    CMPIData d;

    d.type = value.getSimpleType() | CMPI_ARRAY;
    d.state = CMPI_goodValue;
    d.value.array = value.toCMPI();

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiInstance::addProperty(const CmpiName &key, const CmpiDateTime &value)
{
    CMPIData d;

    d.type = CMPI_dateTime;
    d.state = CMPI_goodValue;
    d.value.dateTime = value.toCMPI();

    CMPIStatus status;

    status = _data->ft->setProperty(
        _data, key.str().c_str(), &d.value, d.type);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiData CmpiInstance::getProperty(const CmpiName &key) const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    CMPIData d = _data->ft->getProperty(_data, key.str().c_str(), &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return CmpiData(&d);
}

pair<CmpiName,CmpiData> CmpiInstance::getPropertyAt(unsigned int ndx) const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    CMPIString *name;

    CMPIData d = _data->ft->getPropertyAt(_data, ndx, &name, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiName propname(CMGetCharsPtr(name, &status));

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return make_pair(propname, CmpiData(&d));
}

unsigned int CmpiInstance::getPropertyCount() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    unsigned int result = _data->ft->getPropertyCount(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
    
    return result;
}

CMPIInstance *CmpiInstance::toCMPI() const
{
    return _data;
}

bool CmpiInstance::operator==(const CmpiInstance &obj) const
{
    // Compare object paths

    if (getPath() != obj.getPath())
        return false;

    // Compare property counts

    if (getPropertyCount() != obj.getPropertyCount())
        return false;

    // Compare property values

    for (unsigned int a = 0; a < getPropertyCount(); a++) {

        pair<CmpiName,CmpiData> aProp = getPropertyAt(a);
        bool found = false;

        for (unsigned int b = 0; b < obj.getPropertyCount(); b++) {
            pair<CmpiName,CmpiData> bProp = obj.getPropertyAt(b);

            if (aProp == bProp) {
                found = true;
                break;
            }
        }

        if (!found)
            return false;
    }

    return true;
}

bool CmpiInstance::operator!=(const CmpiInstance &obj) const
{
    return !(*this == obj);
}

CmpiInstance &CmpiInstance::operator=(const CmpiInstance &rhs)
{
    if (this == &rhs)
        return *this;

    // Release lhs

    CMPIStatus status;

    if (_wasCloned) {

        status = _data->ft->release(_data);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);
    }

    // Assign rhs to lhs

    _data = rhs._data;

    status.rc = CMPI_RC_OK;
    status.msg = NULL;

    _data = rhs._data->ft->clone(rhs._data, &status);
    _wasCloned= true;

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return *this;
}

CmpiInstance
CmpiCpp::makeCmpiInstance(const CMPIBroker *broker, const CmpiObjectPath &path)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    
    CMPIInstance *inst = 
        broker->eft->newInstance(broker, path.toCMPI(), &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);   

    return CmpiInstance(inst);
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
