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

#ifndef _CmpiStatus_h
#define _CmpiStatus_h

#include <string>
#include "cmpidt.h"

namespace CmpiCpp {

    using namespace std;

    //
    // Wrap a CMPIrc return code
    //

    class CmpiBroker;

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

        CMPIStatus toCMPI(const CmpiBroker &broker) const;

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
