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

#ifndef _CmpiBrokerResult_h
#define _CmpiBrokerResult_h

#include "cmpidt.h"
#include "cmpift.h"

namespace CmpiCpp {

    namespace Broker {

        class CmpiResult {

        public:

            CmpiResult();
            virtual ~CmpiResult();

            CMPIResult *toCMPI();

            virtual CMPIStatus release() = 0;

            virtual CMPIResult *clone(CMPIStatus *rc) = 0;

            virtual CMPIStatus returnData(const CMPIValue *value, 
                                          CMPIType type) = 0;

            virtual CMPIStatus returnInstance(const CMPIInstance *inst) = 0;

            virtual CMPIStatus returnObjectPath(const CMPIObjectPath *ref) = 0;

            virtual CMPIStatus returnDone() = 0;

        private:

            // Prevent copying

            CmpiResult(CmpiResult &);
            CmpiResult &operator=(CmpiResult &);

            // CMPI function table and driver functions

            CMPIResult _result;
            CMPIResultFT _resultFT;

            static CMPIStatus _driveRelease(CMPIResult *rslt);

            static CMPIResult *_driveClone(const CMPIResult *rslt, 
                                           CMPIStatus *rc);

            static CMPIStatus _driveReturnData(const CMPIResult *rslt,
                                               const CMPIValue *value, 
                                               CMPIType type);

            static CMPIStatus _driveReturnInstance(const CMPIResult *rslt,
                                                   const CMPIInstance *inst);

            static CMPIStatus _driveReturnObjectPath(const CMPIResult *rslt, 
                                                     const CMPIObjectPath *ref);

            static CMPIStatus _driveReturnDone(const CMPIResult *rslt);
        };

    } // namespace Broker

} // namespace CmpiCpp

#endif // _CmpiBrokerResult_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
