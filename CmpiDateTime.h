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

#ifndef _CmpiDateTime_h
#define _CmpiDateTime_h

#include <string>

#include <stdint.h>
#include <time.h>

#include "cmpift.h"

namespace CmpiCpp {

    using namespace std;

    //
    // An object representing a CMPI datetime.
    //

    class CmpiDateTime {

    public:

        CmpiDateTime(const CMPIDateTime *dt);
        CmpiDateTime(const CmpiDateTime &dt);

        virtual ~CmpiDateTime();

        // Accessors

        bool isInterval() const;
        uint64_t getBinaryFormat() const;
        time_t getTimeT() const;

        string str() const;

        CMPIDateTime *toCMPI() const;

        // Overloaded operators

        bool operator==(const CmpiDateTime &dt) const;
        bool operator!=(const CmpiDateTime &dt) const;

        CmpiDateTime &operator=(const CmpiDateTime &rhs);
        
    private:

        CMPIDateTime *_data;
        bool _wasCloned;
    };    
    
    // CMPI time is number of microseconds since Unix epoch, compared to
    // time_t which is the number of seconds since epoch.

    const int cmpiBinFormatMsecs = 1000000;

    // Helper functions

    ostream &operator<<(ostream &output, const CmpiDateTime &obj);

    CmpiDateTime makeCmpiDateTime(const CMPIBroker *broker);

    CmpiDateTime makeCmpiDateTime(const CMPIBroker *broker, uint64_t binTime,
                                  bool isInterval);

    CmpiDateTime makeCmpiDateTime(const CMPIBroker *broker, 
                                  const string &utcTime);

    CmpiDateTime makeCmpiDateTime(const CMPIBroker *broker, time_t t);

    CmpiDateTime makeCurrentDateTime(const CMPIBroker *broker);

} // namespace CmpiCpp

#endif // _CmpiDateTime_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
