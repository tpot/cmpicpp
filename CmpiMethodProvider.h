//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiMethodProvider_h
#define _CmpiMethodProvider_h

#include "CMPI/cmpift.h"
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
