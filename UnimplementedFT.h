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

#ifndef _UnimplementedFT_h
#define _UnimplementedFT_h

//
// Some useful partial implementations of CmpiBroker interfaces to
// avoid lots of typing.
//

#include "CmpiCppBroker.h"

namespace CmpiCpp {

    namespace Broker {

        class UnimplementedBrokerFT : public virtual CmpiBroker {

        public:

            CMPIContext *prepareAttachThread(const CMPIContext *context);

            CMPIStatus attachThread(const CMPIContext *context);

            CMPIStatus detachThread(const CMPIContext *context);

            CMPIStatus deliverIndication(const CMPIContext *context, 
                                         const char *nameSpace, 
                                         const CMPIInstance *ind);

            CMPIEnumeration *enumInstanceNames(const CMPIContext *context,
                                               const CMPIObjectPath *path,
                                               CMPIStatus *rc);

            CMPIInstance *getInstance(const CMPIContext *context,
                                      const CMPIObjectPath *path,
                                      const char **properties,
                                      CMPIStatus *rc);

            CMPIObjectPath *createInstance(const CMPIContext *context,
                                           const CMPIObjectPath *path,
                                           const CMPIInstance *inst,
                                           CMPIStatus *rc);

            CMPIStatus modifyInstance(const CMPIContext *context,
                                      const CMPIObjectPath *path,
                                      const CMPIInstance *inst,
                                      const char **properties);

            CMPIStatus deleteInstance(const CMPIContext *context,
                                      const CMPIObjectPath *path);

            CMPIEnumeration *execQuery(const CMPIContext *context,
                                       const CMPIObjectPath *path,
                                       const char *query,
                                       const char *lang,
                                       CMPIStatus *rc);

            CMPIEnumeration *enumInstances(const CMPIContext *context,
                                           const CMPIObjectPath *path,
                                           const char **properties,
                                           CMPIStatus *rc);

            CMPIEnumeration *associators(const CMPIContext *context,
                                         const CMPIObjectPath *path,
                                         const char *assocClass,
                                         const char *resultClass,
                                         const char *role,
                                         const char *resultRole,
                                         const char **properties,
                                         CMPIStatus *rc);

            CMPIEnumeration *associatorNames(const CMPIContext *context,
                                             const CMPIObjectPath *path,
                                             const char *assocClass,
                                             const char *resultClass,
                                             const char *role,
                                             const char *resultRole,
                                             CMPIStatus *rc);

            CMPIEnumeration *references(const CMPIContext *context,
                                        const CMPIObjectPath *path,
                                        const char *resultClass,
                                        const char *role,
                                        const char **properties,
                                        CMPIStatus *rc);

            CMPIEnumeration *referenceNames(const CMPIContext *context,
                                            const CMPIObjectPath *path,
                                            const char *resultClass,
                                            const char *role,
                                            CMPIStatus *rc);

            CMPIData invokeMethod(const CMPIContext *context,
                                  const CMPIObjectPath *path,
                                  const char *method,
                                  const CMPIArgs *in,
                                  CMPIArgs *out,
                                  CMPIStatus *rc);

            CMPIStatus setProperty(const CMPIContext *context,
                                   const CMPIObjectPath *path,
                                   const char *name,
                                   const CMPIValue *value,
                                   CMPIType type);

            CMPIData getProperty(const CMPIContext *context,
                                 const CMPIObjectPath *path,
                                 const char *name,
                                 CMPIStatus *rc);
        };

        class UnimplementedBrokerEncFT : public virtual CmpiBroker {

        public:

            CMPIInstance *newInstance(const CMPIObjectPath *op, 
                                      CMPIStatus *rc);

            CMPIObjectPath *newObjectPath(const char *ns, 
                                          const char *cn, 
                                          CMPIStatus *rc);

            CMPIArgs *newArgs(CMPIStatus *rc);

            CMPIString *newString(const char *data, CMPIStatus *rc);

            CMPIArray *newArray(CMPICount max, CMPIType type, 
                                CMPIStatus *rc);

            CMPIDateTime *newDateTime(CMPIStatus *rc);

            CMPIDateTime *newDateTimeFromBinary(CMPIUint64 binTime, 
                                                bool interval,
                                                CMPIStatus *rc);

            CMPIDateTime *newDateTimeFromChars(const char *utcTime, 
                                               CMPIStatus *rc);
            
            CMPISelectExp *newSelectExp(const char *query, 
                                        const char *lang, 
                                        CMPIArray **projection,
                                        CMPIStatus *rc);

            CMPIBoolean classPathIsA(const CMPIObjectPath *op,
                                     const char *type, 
                                     CMPIStatus *rc);

            CMPIString *toString(const void *object, 
                                 CMPIStatus *rc);

            CMPIBoolean isOfType(const void *object, const char *type, 
                                 CMPIStatus *rc);

            CMPIString *getType(const void *object, CMPIStatus *rc);

            CMPIString *getMessage(const char *msgId, 
                                   const char *defMsg, 
                                   CMPIStatus *rc);

            CMPIStatus logMessage(int severity, const char *id, 
                                  const char *text, 
                                  const CMPIString *string);

            CMPIStatus trace(int level, const char *component, 
                             const char *text, 
                             const CMPIString *string);
        };

    } // namespace Broker

} // namespace CmpiCpp

#endif // _UnimplementedFT_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
