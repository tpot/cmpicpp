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

#ifndef _CmpiMethodProvider_h
#define _CmpiMethodProvider_h

#include "cmpift.h"
#include "CmpiProvider.h"

namespace CmpiCpp {
    
    class CmpiArgs;
    class CmpiMethodResult;

    class CmpiMethodProvider : public virtual CmpiProvider {

    public:

        CmpiMethodProvider();
        ~CmpiMethodProvider();

        // Method provider interface

        virtual void
        invokeMethod(const CmpiContext &context, 
                     const CmpiObjectPath &path, 
                     const CmpiName &methodName,
                     const CmpiArgs &in,
                     CmpiMethodResult &result) = 0;

        // Return CMPI function table

        CMPIMethodMI *getMethodMI();

    private:

        // Static functions to drive C++ methods from C

        static CMPIStatus
        _driveCleanup(CMPIMethodMI *mi, 
                      const CMPIContext *context, 
                      CMPIBoolean terminating);

        static CMPIStatus
        _driveInvokeMethod(CMPIMethodMI *mi,
                           const CMPIContext *context, 
                           const CMPIResult *result,
                           const CMPIObjectPath *path, 
                           const char *methodName,
                           const CMPIArgs *in, 
                           CMPIArgs *out);       

        // MI function table

        CMPIMethodMI _methodMI;
        CMPIMethodMIFT _methodMIFT;
    };

} // namespace CmpiCpp

#endif // _CmpiMethodProvider_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
