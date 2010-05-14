//
// Copyright (C) 2010 by Hewlett-Packard Development Company L.P.
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

#ifndef _CmpiBroker_h
#define _CmpiBroker_h

#include <time.h>
#include <stdint.h>

#include "cmpidt.h"

#include <string>

namespace CmpiCpp {

    using namespace std;

    class CmpiArgs;
    class CmpiData;
    class CmpiName;
    class CmpiArray;
    class CmpiContext;
    class CmpiDateTime;
    class CmpiInstance;
    class CmpiObjectPath;
    class CmpiEnumeration;

    class CmpiBroker {

    public:

        // Constructors and destructor

        CmpiBroker(const CMPIBroker *arg);
        CmpiBroker(const CmpiBroker &arg);

        ~CmpiBroker();

        // Broker EncFT functions

        CmpiInstance getInstance(const CmpiContext &context,
                                 const CmpiObjectPath &path,
                                 const char **properties);

        CmpiEnumeration enumInstanceNames(const CmpiContext &context,
                                          const CmpiObjectPath &path);

        CmpiEnumeration enumInstances(const CmpiContext &context,
                                      const CmpiObjectPath &path,
                                      const char **properties);

        CmpiData invokeMethod(const CmpiContext &context,
                              const CmpiObjectPath &path,
                              const CmpiName &method,
                              const CmpiArgs &in,
                              CmpiArgs &out);

        CMPIStatus deliverIndication(const CmpiContext & context,
                                     const CmpiName & nameSpace,
                                     const CmpiInstance &indication);

        bool classPathIsA(const CmpiObjectPath &path,
                          const string &parentClassName);

        // Factory functions

        CmpiArgs makeArgs();

        CmpiDateTime makeCmpiDateTime();
        CmpiDateTime makeCmpiDateTime(time_t t);
        CmpiDateTime makeCmpiDateTime(const string &utcTime);
        CmpiDateTime makeCmpiDateTime(uint64_t binTime, bool isInterval);
        CmpiDateTime makeCurrentDateTime();

        CmpiArray makeCmpiArray(int maxsize, CMPIType type);

        CmpiObjectPath makeCmpiObjectPath(const CmpiName &nameSpace,
                                          const CmpiName &className);
        CmpiObjectPath makeCmpiObjectPath(const CmpiName &nameSpace,
                                          const CmpiName &className,
                                          const CmpiName &hostName);

        CmpiInstance makeCmpiInstance(const CmpiObjectPath &path);

        // Other stuff

        const CMPIBroker *toCMPI() const;
        const CmpiBroker &operator=(const CmpiBroker &);

    private:

        const CMPIBroker *_data;
    };

} // namespace CmpiCpp

#endif // _CmpiBroker_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
