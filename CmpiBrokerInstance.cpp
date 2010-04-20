//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "CmpiBrokerInstance.h"
#include "CmpiStatus.h"
#include "CmpiBrokerObjectPath.h"

using namespace CmpiCpp;

//
// Implementation of MyCMPIInstanceBase
//

Broker::CmpiInstance::CmpiInstance()
{
    _instance.hdl = this;

    _instanceFT.ftVersion = CMPICurrentVersion;
    _instanceFT.release = _driveRelease;
    _instanceFT.clone = _driveClone;
    _instanceFT.getProperty = _driveGetProperty;
    _instanceFT.getPropertyAt = _driveGetPropertyAt;
    _instanceFT.getPropertyCount = _driveGetPropertyCount;
    _instanceFT.setProperty = _driveSetProperty;
    _instanceFT.getObjectPath = _driveGetObjectPath;
    _instanceFT.setPropertyFilter = _driveSetPropertyFilter;
    _instanceFT.setObjectPath = _driveSetObjectPath;

    _instance.ft = &_instanceFT;
}

Broker::CmpiInstance::~CmpiInstance()
{
}

CMPIInstance *
Broker::CmpiInstance::toCMPI()
{
    return &_instance;
};

CMPIStatus 
Broker::CmpiInstance::_driveRelease(CMPIInstance *inst)
{
    Broker::CmpiInstance *obj = 
        reinterpret_cast<Broker::CmpiInstance *>(inst->hdl);

    obj->release();

    CMReturn(CMPI_RC_OK);
}

CMPIInstance * 
Broker::CmpiInstance::_driveClone(const CMPIInstance *inst, CMPIStatus *rc)
{
    Broker::CmpiInstance *obj = 
        reinterpret_cast<Broker::CmpiInstance *>(inst->hdl);

    return obj->clone(rc);
}

CMPIData 
Broker::CmpiInstance::_driveGetProperty(const CMPIInstance *inst, 
                                        const char *name,
                                        CMPIStatus *rc)
{
    Broker::CmpiInstance *obj = 
        reinterpret_cast<Broker::CmpiInstance *>(inst->hdl);

    return obj->getProperty(name, rc);
}

CMPIData 
Broker::CmpiInstance::_driveGetPropertyAt(const CMPIInstance *inst, 
                                          unsigned int index, 
                                          CMPIString **name,
                                          CMPIStatus *rc)
{
    Broker::CmpiInstance *obj = 
        reinterpret_cast<Broker::CmpiInstance *>(inst->hdl);

    return obj->getPropertyAt(index, name, rc);
}

unsigned int 
Broker::CmpiInstance::_driveGetPropertyCount(const CMPIInstance *inst, 
                                             CMPIStatus *rc)
{
    Broker::CmpiInstance *obj = 
        reinterpret_cast<Broker::CmpiInstance *>(inst->hdl);

    return obj->getPropertyCount(rc);
}

CMPIStatus 
Broker::CmpiInstance::_driveSetProperty(const CMPIInstance *inst, 
                                        const char *name,
                                        const CMPIValue* value, 
                                        CMPIType type)
{
    Broker::CmpiInstance *obj = 
        reinterpret_cast<Broker::CmpiInstance *>(inst->hdl);

    return obj->setProperty(name, value, type);
}

CMPIObjectPath *
Broker::CmpiInstance::_driveGetObjectPath(const CMPIInstance *inst, 
                                          CMPIStatus *rc)
{
    Broker::CmpiInstance *obj = 
        reinterpret_cast<Broker::CmpiInstance *>(inst->hdl);

    return obj->getObjectPath(rc);
}

CMPIStatus 
Broker::CmpiInstance::_driveSetPropertyFilter(CMPIInstance *, // inst
                                              const char **,  // propertyList
                                              const char **)  // keys
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

CMPIStatus 
Broker::CmpiInstance::_driveSetObjectPath(CMPIInstance *inst, 
                                          const CMPIObjectPath *op)
{
    Broker::CmpiInstance *obj = 
        reinterpret_cast<Broker::CmpiInstance *>(inst->hdl);

    return obj->setObjectPath(op);
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
