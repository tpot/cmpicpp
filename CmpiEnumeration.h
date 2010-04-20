//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiEnumeration_h
#define _CmpiEnumeration_h

namespace CmpiCpp {

    using namespace std;

    //
    // Wrap a CMPIEnumeration
    //

    class CmpiData;
    class CmpiArray;
    class CmpiInstance;
    class CmpiObjectPath;

    class CmpiEnumeration {

    public:

        // Constructors

        CmpiEnumeration(const CMPIEnumeration *args);
        CmpiEnumeration(const CmpiEnumeration &args);

        ~CmpiEnumeration();

        // Accessors

        CmpiData getNext() const;
        bool hasNext() const;
        CmpiArray toArray() const;

    private:

        bool _wasCloned;
        CMPIEnumeration *_data;

        const CmpiEnumeration &operator=(const CmpiEnumeration &rhs);
    };    

} // namespace CmpiCpp

#endif // _CmpiEnumeration_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
