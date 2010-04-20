//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiName_h
#define _CmpiName_h

#include <ostream>
#include <string>

namespace CmpiCpp {

    using namespace std;

    //
    // An object representing a CIM name (class name, property name,
    // namespace, host etc).  The main point here is that comparisons are
    // done in a case-insensitive manner.
    //

    class CmpiName {

    public:

        CmpiName();
        CmpiName(const char *name);
        CmpiName(const string &name);
        CmpiName(const CmpiName &name);

        virtual ~CmpiName();

        // Accessors

        string str() const;
        const char *c_str() const;
        size_t size() const;
        bool empty() const;
        void assign(const string &name);

        // Overloaded operators

        bool operator==(const CmpiName &name) const;
        bool operator!=(const CmpiName &name) const;
        bool operator<(const CmpiName &name) const;

        CmpiName &operator=(const CmpiName &name);
        
        // XXX: I'm in two minds of this operator.  I suspect it will
        // allow the demotion of CmpiName instances to std::string,
        // when we nearly always want to encourage promotion of
        // std::string to CmpiName.

        operator string() const;

    private:

        string _name;
    };    
    
    // Stream output

    ostream &operator<<(ostream &output, const CmpiName &obj);

} // namespace CmpiCpp

#endif // _CmpiName_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
