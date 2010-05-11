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

#include "CmpiBrokerBroker.h"
#include "CmpiStatus.h"

using namespace CmpiCpp;

Broker::CmpiBroker::CmpiBroker()
{
    _broker.hdl = (void *)this;

    // Initialise CMPIBrokerFT

    _brokerFT.brokerVersion = CMPICurrentVersion;
    _brokerFT.brokerName = "CmpiCpp::Broker";

    _brokerFT.prepareAttachThread = _drivePrepareAttachThread;
    _brokerFT.attachThread = _driveAttachThread;
    _brokerFT.detachThread = _driveDetachThread;
    _brokerFT.deliverIndication = _driveDeliverIndication;
    _brokerFT.enumInstanceNames = _driveEnumInstanceNames;
    _brokerFT.getInstance = _driveGetInstance;
    _brokerFT.createInstance = _driveCreateInstance;
    _brokerFT.modifyInstance = _driveModifyInstance;
    _brokerFT.deleteInstance = _driveDeleteInstance;
    _brokerFT.execQuery = _driveExecQuery;
    _brokerFT.enumInstances = _driveEnumInstances;
    _brokerFT.associators = _driveAssociators;
    _brokerFT.associatorNames = _driveAssociatorNames;
    _brokerFT.references = _driveReferences;
    _brokerFT.referenceNames = _driveReferenceNames;
    _brokerFT.invokeMethod = _driveInvokeMethod;
    _brokerFT.setProperty = _driveSetProperty;
    _brokerFT.getProperty = _driveGetProperty;

    _broker.bft = &_brokerFT;

    // Initialise CMPIBrokerEncFT

    _brokerEncFT.ftVersion = CMPICurrentVersion;

    _brokerEncFT.newInstance = _driveNewInstance;
    _brokerEncFT.newObjectPath = _driveNewObjectPath;
    _brokerEncFT.newArgs = _driveNewArgs;
    _brokerEncFT.newString = _driveNewString;
    _brokerEncFT.newArray = _driveNewArray;
    _brokerEncFT.newDateTime = _driveNewDateTime;
    _brokerEncFT.newDateTimeFromBinary = _driveNewDateTimeFromBinary;
    _brokerEncFT.newDateTimeFromChars = _driveNewDateTimeFromChars;
    _brokerEncFT.newSelectExp = _driveNewSelectExp;
    _brokerEncFT.classPathIsA = _driveClassPathIsA;
    _brokerEncFT.toString = _driveToString;
    _brokerEncFT.isOfType = _driveIsOfType;
    _brokerEncFT.getType = _driveGetType;
    _brokerEncFT.getMessage = _driveGetMessage;
    _brokerEncFT.logMessage = _driveLogMessage;
    _brokerEncFT.trace = _driveTrace;

    _broker.eft = &_brokerEncFT;

    // CMPIBrokerExtFT functions not supported

    _broker.xft = NULL;
}

Broker::CmpiBroker::~CmpiBroker()
{
}

CMPIBroker *Broker::CmpiBroker::toCMPI()
{
    return &_broker;
}

// CMPIBrokerFT driver functions

CMPIContext *
Broker::CmpiBroker::_drivePrepareAttachThread(const CMPIBroker *mb,
                                              const CMPIContext *context)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->prepareAttachThread(context);
}

CMPIStatus 
Broker::CmpiBroker::_driveAttachThread(const CMPIBroker *mb,
                                       const CMPIContext *context)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->attachThread(context);
}

CMPIStatus 
Broker::CmpiBroker::_driveDetachThread(const CMPIBroker *mb,
                                       const CMPIContext *context)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->detachThread(context);
}

CMPIStatus 
Broker::CmpiBroker::_driveDeliverIndication(const CMPIBroker *mb,
                                            const CMPIContext *context,
                                            const char *nameSpace,
                                            const CMPIInstance *ind)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->deliverIndication(context, nameSpace, ind);
}

CMPIEnumeration *
Broker::CmpiBroker::_driveEnumInstanceNames(const CMPIBroker *mb,
                                            const CMPIContext *context,
                                            const CMPIObjectPath *path,
                                            CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->enumInstanceNames(context, path, rc);
}

CMPIInstance *
Broker::CmpiBroker::_driveGetInstance(const CMPIBroker *mb,
                                      const CMPIContext *context,
                                      const CMPIObjectPath *path,
                                      const char **properties,
                                      CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->getInstance(context, path, properties, rc);
}

CMPIObjectPath *
Broker::CmpiBroker::_driveCreateInstance(const CMPIBroker *mb,
                                         const CMPIContext *context,
                                         const CMPIObjectPath *path,
                                         const CMPIInstance *inst,
                                         CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->createInstance(context, path, inst, rc);
}

CMPIStatus 
Broker::CmpiBroker::_driveModifyInstance(const CMPIBroker *mb,
                                         const CMPIContext *context,
                                         const CMPIObjectPath *path,
                                         const CMPIInstance *inst,
                                         const char **properties)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->modifyInstance(context, path, inst, properties);
}

CMPIStatus 
Broker::CmpiBroker::_driveDeleteInstance(const CMPIBroker *mb,
                                         const CMPIContext *context,
                                         const CMPIObjectPath *path)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->deleteInstance(context, path);
}

CMPIEnumeration *
Broker::CmpiBroker::_driveExecQuery(const CMPIBroker *mb,
                                    const CMPIContext *context,
                                    const CMPIObjectPath *path,
                                    const char *query,
                                    const char *lang,
                                    CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->execQuery(context, path, query, lang, rc);
}

CMPIEnumeration *
Broker::CmpiBroker::_driveEnumInstances(const CMPIBroker *mb,
                                        const CMPIContext *context,
                                        const CMPIObjectPath *path,
                                        const char **properties,
                                        CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->enumInstances(context, path, properties, rc);
}

CMPIEnumeration *
Broker::CmpiBroker::_driveAssociators(const CMPIBroker *mb,
                                      const CMPIContext *context,
                                      const CMPIObjectPath *path,
                                      const char *assocClass,
                                      const char *resultClass,
                                      const char *role,
                                      const char *resultRole,
                                      const char **properties,
                                      CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->associators(context, path, assocClass, resultClass, role,
                            resultRole, properties, rc);
}

CMPIEnumeration *
Broker::CmpiBroker::_driveAssociatorNames(const CMPIBroker *mb,
                                          const CMPIContext *context,
                                          const CMPIObjectPath *path,
                                          const char *assocClass,
                                          const char *resultClass,
                                          const char *role,
                                          const char *resultRole,
                                          CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->associatorNames(context, path, assocClass, resultClass, role,
                                resultRole, rc);
}

CMPIEnumeration *
Broker::CmpiBroker::_driveReferences(const CMPIBroker *mb,
                                     const CMPIContext *context,
                                     const CMPIObjectPath *path,
                                     const char *resultClass,
                                     const char *role,
                                     const char **properties,
                                     CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->references(context, path, resultClass, role, properties, rc);
}

CMPIEnumeration *
Broker::CmpiBroker::_driveReferenceNames(const CMPIBroker *mb,
                                         const CMPIContext *context,
                                         const CMPIObjectPath *path,
                                         const char *resultClass,
                                         const char *role,
                                         CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->referenceNames(context, path, resultClass, role, rc);
}

CMPIData 
Broker::CmpiBroker::_driveInvokeMethod(const CMPIBroker *mb,
                                       const CMPIContext *context,
                                       const CMPIObjectPath *path,
                                       const char *method,
                                       const CMPIArgs *in,
                                       CMPIArgs *out,
                                       CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->invokeMethod(context, path, method, in, out, rc);
}

CMPIStatus 
Broker::CmpiBroker::_driveSetProperty(const CMPIBroker *mb,
                                      const CMPIContext *context,
                                      const CMPIObjectPath *path,
                                      const char *name,
                                      const CMPIValue *value,
                                      CMPIType type)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->setProperty(context, path,name, value, type);
}

CMPIData 
Broker::CmpiBroker::_driveGetProperty(const CMPIBroker *mb,
                                      const CMPIContext *context,
                                      const CMPIObjectPath *path,
                                      const char *name,
                                      CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->getProperty(context, path, name, rc);
}

// CMPIBrokerEncFT driver functions

CMPIInstance *
Broker::CmpiBroker::_driveNewInstance(const CMPIBroker *mb,
                                      const CMPIObjectPath *op,
                                      CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->newInstance(op, rc);
}

CMPIObjectPath *
Broker::CmpiBroker::_driveNewObjectPath(const CMPIBroker *mb,
                                        const char *ns,
                                        const char *cn,
                                        CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->newObjectPath(ns, cn, rc);
}

CMPIArgs *
Broker::CmpiBroker::_driveNewArgs(const CMPIBroker *mb,
                                  CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->newArgs(rc);
}

CMPIString *
Broker::CmpiBroker::_driveNewString(const CMPIBroker *mb,
                                    const char *data,
                                    CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->newString(data, rc);
}

CMPIArray *
Broker::CmpiBroker::_driveNewArray(const CMPIBroker *mb,
                                   CMPICount max,
                                   CMPIType type,
                                   CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->newArray(max, type, rc);
}

CMPIDateTime *
Broker::CmpiBroker::_driveNewDateTime(const CMPIBroker *mb,
                                      CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->newDateTime(rc);
}

CMPIDateTime *
Broker::CmpiBroker::_driveNewDateTimeFromBinary(const CMPIBroker *mb,
                                                CMPIUint64 binTime,
                                                CMPIBoolean interval,
                                                CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->newDateTimeFromBinary(binTime, interval, rc);
}

CMPIDateTime *
Broker::CmpiBroker::_driveNewDateTimeFromChars(const CMPIBroker *mb,
                                               const char *utcTime,
                                               CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->newDateTimeFromChars(utcTime, rc);
}

CMPISelectExp *
Broker::CmpiBroker::_driveNewSelectExp(const CMPIBroker *mb,
                                       const char *query,
                                       const char *lang,
                                       CMPIArray* *projection,
                                       CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);
    
    return obj->newSelectExp(query, lang, projection, rc);
}

CMPIBoolean 
Broker::CmpiBroker::_driveClassPathIsA(const CMPIBroker *mb,
                                       const CMPIObjectPath *op,
                                       const char *type,
                                       CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->classPathIsA(op, type, rc);
}

CMPIString *
Broker::CmpiBroker::_driveToString(const CMPIBroker *mb,
                                   const void *object,
                                   CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->toString(object, rc);
}

CMPIBoolean 
Broker::CmpiBroker::_driveIsOfType(const CMPIBroker *mb,
                                   const void *object,
                                   const char *type,
                                   CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);
    
    return obj->isOfType(object, type, rc);
}

CMPIString *
Broker::CmpiBroker::_driveGetType(const CMPIBroker *mb,
                                  const void *object,
                                  CMPIStatus *rc)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->getType(object, rc);
}

CMPIString *
Broker::CmpiBroker::_driveGetMessage(const CMPIBroker *mb,
                                     const char *msgId,
                                     const char *defMsg,
                                     CMPIStatus *rc,
                                     CMPICount, // count
                                     ...)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);


    return obj->getMessage(msgId, defMsg, rc);
}

CMPIStatus 
Broker::CmpiBroker::_driveLogMessage(const CMPIBroker *mb,
                                     int severity,
                                     const char *id,
                                     const char *text,
                                     const CMPIString *string)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->logMessage(severity, id, text, string);
}

CMPIStatus 
Broker::CmpiBroker::_driveTrace(const CMPIBroker *mb,
                                int level,
                                const char *component,
                                const char *text,
                                const CMPIString *string)
{
    CmpiBroker *obj = reinterpret_cast<CmpiBroker *>(mb->hdl);

    return obj->trace(level, component, text, string);
}

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
