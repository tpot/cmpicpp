//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiInstanceProvider_h
#define _CmpiInstanceProvider_h

#include "CMPI/cmpift.h"
#include "CmpiProvider.h"

namespace CmpiCpp {

    using namespace std;

    class CmpiInstanceResult;
    class CmpiObjectPathResult;

    class CmpiInstanceProvider : public virtual CmpiProvider {

    public:

        CmpiInstanceProvider();
        ~CmpiInstanceProvider();

        // Instance provider interface

        virtual void 
        enumInstanceNames(const CmpiContext &context, 
                          const CmpiObjectPath &path,
                          CmpiObjectPathResult &result) = 0;

        virtual void 
        enumInstances(const CmpiContext &context, 
                      const CmpiObjectPath &path, 
                      const char **properties,
                      CmpiInstanceResult &result) = 0;
        
        virtual void 
        getInstance(const CmpiContext &context, 
                    const CmpiObjectPath &path, 
                    const char **properties,
                    CmpiInstanceResult &result) = 0;

        virtual void 
        createInstance(const CmpiContext &context, 
                       const CmpiObjectPath &path, 
                       const CmpiInstance &inst,
                       CmpiObjectPathResult &result);
        
        virtual void 
        modifyInstance(const CmpiContext &context, 
                       const CmpiObjectPath &path, 
                       const CmpiInstance &inst, 
                       const char **properties);

        virtual void 
        deleteInstance(const CmpiContext &context, 
                       const CmpiObjectPath &path);

        virtual void 
        execQuery(const CmpiContext &context, 
                  const CmpiObjectPath &path, 
                  const string &language, 
                  const string &query,
                  CmpiObjectPathResult &result);

        // Return CMPI function table

        CMPIInstanceMI *getInstanceMI();

    private:

        // Static functions to drive C++ methods from C

        static CMPIStatus 
        _driveCleanup(CMPIInstanceMI *mi, 
                      const CMPIContext *context, 
                      CMPIBoolean terminating);
        
        static CMPIStatus 
        _driveEnumInstanceNames(CMPIInstanceMI *mi, 
                                const CMPIContext *context, 
                                const CMPIResult *result, 
                                const CMPIObjectPath *path);

        static CMPIStatus 
        _driveEnumInstances(CMPIInstanceMI *mi, 
                            const CMPIContext *context, 
                            const CMPIResult *result, 
                            const CMPIObjectPath *path, 
                            const char **properties);

        static CMPIStatus 
        _driveGetInstance(CMPIInstanceMI *mi, 
                          const CMPIContext *context, 
                          const CMPIResult *result, 
                          const CMPIObjectPath *path, 
                          const char **properties);

        static CMPIStatus 
        _driveCreateInstance(CMPIInstanceMI *mi, 
                             const CMPIContext *context, 
                             const CMPIResult *result, 
                             const CMPIObjectPath *path, 
                             const CMPIInstance *instance);

        static CMPIStatus 
        _driveModifyInstance(CMPIInstanceMI *mi, 
                             const CMPIContext *context, 
                             const CMPIResult *result, 
                             const CMPIObjectPath *path, 
                             const CMPIInstance *instance, 
                             const char **properties);

        static CMPIStatus 
        _driveDeleteInstance(CMPIInstanceMI *mi, 
                             const CMPIContext *context, 
                             const CMPIResult *result, 
                             const CMPIObjectPath *path);

        static CMPIStatus 
        _driveExecQuery(CMPIInstanceMI *mi, 
                        const CMPIContext *context, 
                        const CMPIResult *result, 
                        const CMPIObjectPath *path, 
                        const char *language,
                        const char *query);

        // MI function table

        CMPIInstanceMI _instanceMI;
        CMPIInstanceMIFT _instanceMIFT;
    };

} // namespace CmpiCpp

#endif // _CmpiInstanceProvider_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
