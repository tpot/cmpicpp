//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
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

#ifndef _CmpiObjectPath_h
#define _CmpiObjectPath_h

#include <string>
#include "cmpidt.h"

namespace CmpiCpp {

    using namespace std;

    class CmpiName;
    class CmpiData;

    //
    // Wrap a CMPIObjectPath
    //

    class CmpiObjectPath {

    public:

        // Constructors

        CmpiObjectPath(const CMPIObjectPath *path);
        CmpiObjectPath(const CmpiObjectPath &path);

        virtual ~CmpiObjectPath();

        // Accessors

        CmpiName getHost() const;
        void setHost(const CmpiName &host);

        CmpiName getNameSpace() const;
        void setNameSpace(const CmpiName &nameSpace);

        CmpiName getClassName() const;
        void setClassName(const CmpiName &className);

        bool classPathIsA(const CMPIBroker *broker, const string &parentClassName);

        bool empty() const;
        string str() const;

        CMPIObjectPath *toCMPI() const;

        // Keybinding accessors

        void addKey(const CmpiName &key, const CmpiData &value);
        void addKey(const CmpiName &key, CMPIUint8 value);
        void addKey(const CmpiName &key, CMPISint8 value);
        void addKey(const CmpiName &key, CMPIUint16 value);
        void addKey(const CmpiName &key, CMPISint16 value);
        void addKey(const CmpiName &key, CMPIUint32 value);
        void addKey(const CmpiName &key, CMPISint32 value);
        void addKey(const CmpiName &key, CMPIUint64 value);
        void addKey(const CmpiName &key, CMPISint64 value);
        void addKey(const CmpiName &key, CMPIReal32 value);
        void addKey(const CmpiName &key, CMPIReal64 value);
        void addKey(const CmpiName &key, bool value);
        void addKey(const CmpiName &key, const char *value);
        void addKey(const CmpiName &key, const string &value);
        void addKey(const CmpiName &key, const stringstream &value);
        void addKey(const CmpiName &key, const CmpiObjectPath &value);

        CmpiData getKey(const CmpiName &key) const;
        pair<CmpiName,CmpiData> getKeyAt(unsigned int ndx) const;
        unsigned int getKeyCount() const;

        // Operators

        bool operator==(const CmpiObjectPath &obj) const;
        bool operator!=(const CmpiObjectPath &obj) const;
        CmpiObjectPath &operator=(const CmpiObjectPath &rhs);

    private:

        CMPIObjectPath *_data;
        bool _wasCloned;
    };    

    // Helper functions

    ostream &operator<<(ostream &output, const CmpiObjectPath &obj);

    CmpiObjectPath makeCmpiObjectPath(const CMPIBroker *broker);

    CmpiObjectPath makeCmpiObjectPath(const CMPIBroker *broker,
                                      const CmpiName &nameSpace,
                                      const CmpiName &className);

    CmpiObjectPath makeCmpiObjectPath(const CMPIBroker *broker,
                                      const CmpiName &nameSpace,
                                      const CmpiName &className,
                                      const CmpiName &hostName);

    bool CMPIStringCompare(const CMPIString *a, const CMPIString *b);

    bool CMPIObjectPathCompare(const CMPIObjectPath *a, 
                               const CMPIObjectPath *b);

} // namespace CmpiCpp

#endif // _CmpiObjectPath_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
