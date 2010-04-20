//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiBrokerBroker_h
#define _CmpiBrokerBroker_h

#include "CMPI/cmpidt.h"
#include "CMPI/cmpift.h"

namespace CmpiCpp {

    namespace Broker {

        // Wrapper for CMPIBroker

        class CmpiBroker {

        public:

            CmpiBroker();
            virtual ~CmpiBroker();

            CMPIBroker *toCMPI();

            // BrokerFT interface

            virtual CMPIContext *
            prepareAttachThread(const CMPIContext *context) = 0;

            virtual CMPIStatus attachThread(const CMPIContext *context) = 0;

            virtual CMPIStatus detachThread(const CMPIContext *context) = 0;

            virtual CMPIStatus deliverIndication(const CMPIContext *context, 
                                                 const char *nameSpace, 
                                                 const CMPIInstance *ind) = 0;

            virtual CMPIEnumeration *
            enumInstanceNames(const CMPIContext *context,
                              const CMPIObjectPath *path,
                              CMPIStatus *rc) = 0;

            virtual CMPIInstance *getInstance(const CMPIContext *context,
                                              const CMPIObjectPath *path,
                                              const char **properties,
                                              CMPIStatus *rc) = 0;

            virtual CMPIObjectPath *createInstance(const CMPIContext *context,
                                                   const CMPIObjectPath *path,
                                                   const CMPIInstance *inst,
                                                   CMPIStatus *rc) = 0;

            virtual CMPIStatus modifyInstance(const CMPIContext *context,
                                              const CMPIObjectPath *path,
                                              const CMPIInstance *inst,
                                              const char **properties) = 0;

            virtual CMPIStatus deleteInstance(const CMPIContext *context,
                                              const CMPIObjectPath *path) = 0;

            virtual CMPIEnumeration *execQuery(const CMPIContext *context,
                                               const CMPIObjectPath *path,
                                               const char *query,
                                               const char *lang,
                                               CMPIStatus *rc) = 0;

            virtual CMPIEnumeration *enumInstances(const CMPIContext *context,
                                                   const CMPIObjectPath *path,
                                                   const char **properties,
                                                   CMPIStatus *rc) = 0;

            virtual CMPIEnumeration *associators(const CMPIContext *context,
                                                 const CMPIObjectPath *path,
                                                 const char *assocClass,
                                                 const char *resultClass,
                                                 const char *role,
                                                 const char *resultRole,
                                                 const char **properties,
                                                 CMPIStatus *rc) = 0;

            virtual CMPIEnumeration *associatorNames(const CMPIContext *context,
                                                     const CMPIObjectPath *path,
                                                     const char *assocClass,
                                                     const char *resultClass,
                                                     const char *role,
                                                     const char *resultRole,
                                                     CMPIStatus *rc) = 0;

            virtual CMPIEnumeration *references(const CMPIContext *context,
                                                const CMPIObjectPath *path,
                                                const char *resultClass,
                                                const char *role,
                                                const char **properties,
                                                CMPIStatus *rc) = 0;

            virtual CMPIEnumeration *referenceNames(const CMPIContext *context,
                                                    const CMPIObjectPath *path,
                                                    const char *resultClass,
                                                    const char *role,
                                                    CMPIStatus *rc) = 0;

            virtual CMPIData invokeMethod(const CMPIContext *context,
                                          const CMPIObjectPath *path,
                                          const char *method,
                                          const CMPIArgs *in,
                                          CMPIArgs *out,
                                          CMPIStatus *rc) = 0;

            virtual CMPIStatus setProperty(const CMPIContext *context,
                                           const CMPIObjectPath *path,
                                           const char *name,
                                           const CMPIValue *value,
                                           CMPIType type) = 0;

            virtual CMPIData getProperty(const CMPIContext *context,
                                         const CMPIObjectPath *path,
                                         const char *name,
                                         CMPIStatus *rc) = 0;

            // BrokerEncFT interface

            virtual CMPIInstance *newInstance(const CMPIObjectPath *op, 
                                              CMPIStatus *rc) = 0;

            virtual CMPIObjectPath *newObjectPath(const char *ns, 
                                                  const char *cn, 
                                                  CMPIStatus *rc) = 0;

            virtual CMPIArgs *newArgs(CMPIStatus *rc) = 0;

            virtual CMPIString *newString(const char *data, CMPIStatus *rc) = 0;

            virtual CMPIArray *newArray(CMPICount max, CMPIType type, 
                                        CMPIStatus *rc) = 0;

            virtual CMPIDateTime *newDateTime(CMPIStatus *rc) = 0;

            virtual CMPIDateTime *newDateTimeFromBinary(CMPIUint64 binTime, 
                                                        bool interval,
                                                        CMPIStatus *rc) = 0;

            virtual CMPIDateTime *newDateTimeFromChars(const char *utcTime, 
                                                       CMPIStatus *rc) = 0;
            
            virtual CMPISelectExp *newSelectExp(const char *query, 
                                                const char *lang, 
                                                CMPIArray **projection,
                                                CMPIStatus *rc) = 0;

            virtual CMPIBoolean classPathIsA(const CMPIObjectPath *op,
                                             const char *type, 
                                             CMPIStatus *rc) = 0;

            virtual CMPIString *toString(const void *object, 
                                         CMPIStatus *rc) = 0;

            virtual CMPIBoolean isOfType(const void *object, const char *type, 
                                         CMPIStatus *rc) = 0;

            virtual CMPIString *getType(const void *object, CMPIStatus *rc) = 0;

            virtual CMPIString *getMessage(const char *msgId, 
                                           const char *defMsg, 
                                           CMPIStatus *rc) = 0;

            virtual CMPIStatus logMessage(int severity, const char *id, 
                                          const char *text, 
                                          const CMPIString *string) = 0;

            virtual CMPIStatus trace(int level, const char *component, 
                                     const char *text, 
                                     const CMPIString *string) = 0;
                                     
        private:

            // CMPI function table and driver functions

            CMPIBroker      _broker;
            CMPIBrokerFT    _brokerFT;

            static CMPIContext *_drivePrepareAttachThread
            (const CMPIBroker *mb, const CMPIContext *ctx);

            static CMPIStatus _driveAttachThread
            (const CMPIBroker *mb, const CMPIContext*);

            static CMPIStatus _driveDetachThread
            (const CMPIBroker *mb, const CMPIContext *ctx);

            static CMPIStatus _driveDeliverIndication
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const char *ns, const CMPIInstance *ind);

            static CMPIEnumeration *_driveEnumInstanceNames
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, CMPIStatus *rc);

            static CMPIInstance *_driveGetInstance
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const char* *properties, 
             CMPIStatus *rc);

            static CMPIObjectPath *_driveCreateInstance
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const CMPIInstance *inst, 
             CMPIStatus *rc);

            static CMPIStatus _driveModifyInstance
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const CMPIInstance *inst, 
             const char **properties);

            static CMPIStatus _driveDeleteInstance
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op);

            static CMPIEnumeration *_driveExecQuery
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const char *query, const char *lang, 
             CMPIStatus *rc);

            static CMPIEnumeration *_driveEnumInstances
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const char **properties, 
             CMPIStatus *rc);

            static CMPIEnumeration *_driveAssociators
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const char *assocClass, 
             const char *resultClass, const char *role, const char *resultRole,
             const char **properties, CMPIStatus *rc);

            static CMPIEnumeration *_driveAssociatorNames
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const char *assocClass, 
             const char *resultClass, const char *role, const char *resultRole,
             CMPIStatus *rc);

            static CMPIEnumeration *_driveReferences
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const char *resultClass,
             const char *role, const char **properties, CMPIStatus *rc);

            static CMPIEnumeration *_driveReferenceNames
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const char *resultClass, 
             const char *role, CMPIStatus *rc);

            static CMPIData _driveInvokeMethod
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const char *method,
             const CMPIArgs *in, CMPIArgs *out, CMPIStatus *rc);

            static CMPIStatus _driveSetProperty
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const char *name, 
             const CMPIValue *value, CMPIType type);

            static CMPIData _driveGetProperty
            (const CMPIBroker *mb, const CMPIContext *ctx,
             const CMPIObjectPath *op, const char *name, CMPIStatus *rc);

            // CMPIBrokerEncFT functions

            CMPIBrokerEncFT _brokerEncFT;

            static CMPIInstance *_driveNewInstance
            (const CMPIBroker *mb, const CMPIObjectPath *op, CMPIStatus *rc);

            static CMPIObjectPath *_driveNewObjectPath
            (const CMPIBroker *mb, const char *ns, const char *cn, 
             CMPIStatus *rc);

            static CMPIArgs *_driveNewArgs(const CMPIBroker *mb, 
                                           CMPIStatus *rc);

            static CMPIString *_driveNewString
            (const CMPIBroker *mb, const char *data, CMPIStatus *rc);

            static CMPIArray *_driveNewArray
            (const CMPIBroker *mb, CMPICount max, CMPIType type, 
             CMPIStatus *rc);

            static CMPIDateTime *_driveNewDateTime
            (const CMPIBroker *mb, CMPIStatus *rc);

            static CMPIDateTime *_driveNewDateTimeFromBinary
            (const CMPIBroker *mb, CMPIUint64 binTime, CMPIBoolean interval,
             CMPIStatus *rc);

            static CMPIDateTime *_driveNewDateTimeFromChars
            (const CMPIBroker *mb, const char *utcTime, CMPIStatus *rc);

            static CMPISelectExp *_driveNewSelectExp
            (const CMPIBroker *mb, const char *query, const char *lang,
             CMPIArray* *projection, CMPIStatus *rc);

            static CMPIBoolean _driveClassPathIsA
            (const CMPIBroker *mb, const CMPIObjectPath *op, const char *type, 
             CMPIStatus *rc);

            static CMPIString *_driveToString
            (const CMPIBroker *mb, const void *object, CMPIStatus *rc);

            static CMPIBoolean _driveIsOfType
            (const CMPIBroker *mb, const void *object, const char *type, 
             CMPIStatus *rc);

            static CMPIString *_driveGetType
            (const CMPIBroker *mb, const void *object, CMPIStatus *rc);

            static CMPIString *_driveGetMessage
            (const CMPIBroker *mb, const char *msgId, const char *defMsg, 
             CMPIStatus *rc, CMPICount count, ...);

            static CMPIStatus _driveLogMessage
            (const CMPIBroker *mb, int severity, const char *id,
             const char *text, const CMPIString *string);

            static CMPIStatus _driveTrace
            (const CMPIBroker *mb, int level, const char *component,
             const char *text, const CMPIString *string);
        };

    } // namespace Broker

} // namespace CmpiCpp

#endif // _CmpiBrokerBroker_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
