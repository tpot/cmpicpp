//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiIndicationProvider_h
#define _CmpiIndicationProvider_h

#include "cmpift.h"
#include "CmpiProvider.h"

namespace CmpiCpp {

    using namespace std;

    class CmpiIndicationProvider : public virtual CmpiProvider {

    public:

        CmpiIndicationProvider();
        ~CmpiIndicationProvider();

        // Indication provider interface

        virtual void
        authorizeFilter(const CmpiContext &context,
                        const CMPISelectExp *filter,
                        const string &className,
                        const CmpiObjectPath &path,
                        const string &user) = 0;

        virtual void
        mustPoll(const CmpiContext &context,
                 const CMPISelectExp *filter,
                 const string &className,
                 const CmpiObjectPath &path) = 0;

        virtual void
        activateFilter(const CmpiContext &context,
                       const CMPISelectExp *filter,
                       const string &className,
                       const CmpiObjectPath &path,
                       bool last) = 0;

        virtual void
        deactivateFilter(const CmpiContext &context,
                       const CMPISelectExp *filter,
                       const string &className,
                       const CmpiObjectPath &path,
                       bool last) = 0;
                         
        virtual void
        enableIndications(const CmpiContext &context) = 0;

        virtual void
        disableIndications(const CmpiContext &context) = 0;

        // Return CMPI function table

        CMPIIndicationMI *getIndicationMI();

    private:

        // Static functions to drive C++ methods from C
        
        static CMPIStatus 
        _driveCleanup(CMPIIndicationMI *mi, 
                      const CMPIContext *context, 
                      CMPIBoolean terminating);
	
        static CMPIStatus
        _driveAuthorizeFilter(CMPIIndicationMI *mi, const CMPIContext *context,
                              const CMPISelectExp *se, const char *ns, 
                              const CMPIObjectPath *op, const char *user);

        static CMPIStatus 
        _driveMustPoll(CMPIIndicationMI *mi, const CMPIContext *context, 
                       const CMPISelectExp *se, const char *ns, 
                       const CMPIObjectPath *op);

        static CMPIStatus 
        _driveActivateFilter(CMPIIndicationMI *mi, const CMPIContext *context, 
                             const CMPISelectExp *se, const char *ns, 
                             const CMPIObjectPath *op, CMPIBoolean first);

        static CMPIStatus 
        _driveDeActivateFilter(CMPIIndicationMI *mi, const CMPIContext *context,
                               const CMPISelectExp *se, const char *ns, 
                               const CMPIObjectPath *op, CMPIBoolean last);

        static CMPIStatus
        _driveEnableIndications(CMPIIndicationMI *mi, 
                                const CMPIContext *context);

        static CMPIStatus
        _driveDisableIndications(CMPIIndicationMI *mi, 
                                 const CMPIContext *context);

        // MI function table

        CMPIIndicationMI _indicationMI;
        CMPIIndicationMIFT _indicationMIFT;
    };

} // namespace CmpiCpp

#endif // _CmpiIndicationProvider_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
