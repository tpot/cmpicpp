//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiStatus_h
#define _CmpiStatus_h

#include <string>
#include "CMPI/cmpidt.h"

namespace CmpiCpp {

    using namespace std;

    //
    // Wrap a CMPIrc return code
    //

    class CmpiStatus {

    public:

        CmpiStatus();
        CmpiStatus(const CMPIrc rc);
        CmpiStatus(const CMPIrc rc, const string &msg);
        CmpiStatus(const CMPIStatus *status);
        CmpiStatus(const CmpiStatus &status);

        virtual ~CmpiStatus();

        CMPIrc getRC() const;
        string getMsg() const;

        string str() const;

        CMPIStatus toCMPI(const CMPIBroker *broker) const;

        bool operator==(const CmpiStatus &status) const;
        bool operator!=(const CmpiStatus &status) const;
        bool operator<(const CmpiStatus &status) const;

        CmpiStatus &operator=(const CmpiStatus &rhs);

        static string rcToString(CMPIrc rc);

    private:

        CMPIrc _rc;
        string _msg;
    };

} // namespace CmpiCpp

#endif // _CmpiStatus_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
