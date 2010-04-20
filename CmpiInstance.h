//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiInstance_h
#define _CmpiInstance_h

#include <string>

namespace CmpiCpp {

    using namespace std;

    class CmpiName;
    class CmpiArray;
    class CmpiDateTime;
    class CmpiObjectPath;

    //
    // Wrap a CMPIInstance
    //
    
    class CmpiInstance {

    public:

        CmpiInstance(const CMPIInstance *obj);
        CmpiInstance(const CmpiInstance &obj);

        virtual ~CmpiInstance();

        // Accessors

        CmpiObjectPath getPath() const;
        void setPath(const CmpiObjectPath &path);

        // Accessors passed through to object path

        CmpiName getHost() const;
        CmpiName getNameSpace() const;
        CmpiName getClassName() const;

        // Property accessors

        void addProperty(const CmpiName &key, CMPIUint8 value);
        void addProperty(const CmpiName &key, CMPISint8 value);
        void addProperty(const CmpiName &key, CMPIUint16 value);
        void addProperty(const CmpiName &key, CMPISint16 value);
        void addProperty(const CmpiName &key, CMPIUint32 value);
        void addProperty(const CmpiName &key, CMPISint32 value);
        void addProperty(const CmpiName &key, CMPIUint64 value);
        void addProperty(const CmpiName &key, CMPISint64 value);
        void addProperty(const CmpiName &key, CMPIReal32 value);
        void addProperty(const CmpiName &key, CMPIReal64 value);
        void addProperty(const CmpiName &key, bool value);
        void addProperty(const CmpiName &key, const char *value);
        void addProperty(const CmpiName &key, const string &value);
        void addProperty(const CmpiName &key, const stringstream &value);
        void addProperty(const CmpiName &key, const CmpiObjectPath &value);
        void addProperty(const CmpiName &key, const CmpiArray &value);
        void addProperty(const CmpiName &key, const CmpiDateTime &value);

        CmpiData getProperty(const CmpiName &key) const;
        pair<CmpiName,CmpiData> getPropertyAt(unsigned int ndx) const;
        unsigned int getPropertyCount() const;

        CMPIInstance *toCMPI() const;

        // operators

        bool operator==(const CmpiInstance &obj) const;
        bool operator!=(const CmpiInstance &obj) const;
        CmpiInstance &operator=(const CmpiInstance &rhs);

    private:
        bool _wasCloned;                // Only release cloned instances
        CMPIInstance *_data;
    };

    // Factory function

    CmpiInstance makeCmpiInstance(const CMPIBroker *broker,
                                  const CmpiObjectPath &path);

} // namespace CmpiCpp

#endif // _CmpiInstance_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
