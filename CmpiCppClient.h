//
// Copyright (C) 2009 by Hewlett-Packard Development Company L.P.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2 of the License.
//   
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//   
// You should have received a copy of the GNU Lesser General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiCppClient_h
#define _CmpiCppClient_h

#include <string>
#include <vector>

class XMLTextReader;

// Some ugly forward declarations to avoid including libxml2 and curl
// header files by users of the client.

typedef void CURL;
struct curl_slist;

namespace CmpiCpp {

    using namespace std;
    
    class CmpiContext;
    class CmpiInstance;
    class CmpiObjectPath;
    class CmpiEnumeration;

    class CmpiCppClient {

    public:

        CmpiCppClient(const CMPIBroker *broker, const string &socketPath);
        CmpiCppClient(const CMPIBroker *broker, const string &url, 
                      const string &user, const string &pass);
        
        ~CmpiCppClient();

        CmpiEnumeration enumInstances(const CmpiContext &context,
                                      const CmpiObjectPath &path,
                                      const char **properties);

        CmpiInstance getInstance(const CmpiContext &context,
                                 const CmpiObjectPath &path,
                                 const char **properties);

    private:

        const CMPIBroker *_broker;
        const string _socketPath;
        const string _url, _user, _pass;

        CURL *_handle;
        void _curl_common_init();

        struct curl_slist *_makeHeaders();

        string _makeEnumerateInstancesRequest(const CmpiObjectPath &path);
        string _makeGetInstanceRequest(const CmpiObjectPath &path);

        vector<CmpiInstance> 
        _parseEnumerateInstancesResponse(const string &data,
                                         const CmpiName &nameSpace);

        CmpiInstance _parseGetInstanceResponse(const string &data,
                                               const CmpiName &nameSpace);

        pair<unsigned,string> _processError(XMLTextReader &reader);
        string _processValue(XMLTextReader &reader);
        vector<string> _processValueArray(XMLTextReader &reader);
        void _processProperty(XMLTextReader &reader, CmpiInstance &inst);
        void _processPropertyArray(XMLTextReader &reader, CmpiInstance &inst);
        pair<string,string> _processKeyvalue(XMLTextReader &reader);
        void _processKeybinding(XMLTextReader &reader, CmpiObjectPath &path);
        void _processInstanceName(XMLTextReader &reader, CmpiObjectPath &path);
        CmpiName _processInstance(XMLTextReader &reader, CmpiInstance &inst);
        CmpiInstance _processValueNamedInstance(XMLTextReader &reader,
                                                const CmpiName &nameSpace);

        CmpiArray _convertArray(const string &type, const vector<string> &data);

        // Copy constructor and assignment operator
        
        CmpiCppClient(const CmpiCppClient &);
        const CmpiCppClient &operator=(const CmpiCppClient &);
    };

    // Factory function

    CmpiCppClient *makeCmpiCppClient(const CMPIBroker *broker);
};

#endif // _CmpiCppClient_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
