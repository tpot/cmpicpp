//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "CmpiBrokerObjectPath.h"
#include "CmpiStatus.h"

using namespace CmpiCpp;

//
// Implementation of MyCMPIObjectPathBase
//

Broker::CmpiObjectPath::CmpiObjectPath()
{
    _objectpath.hdl = this;

    _objectpathFT.ftVersion = CMPICurrentVersion;
    _objectpathFT.release = _driveRelease;
    _objectpathFT.clone = _driveClone;
    _objectpathFT.setNameSpace = _driveSetNameSpace;
    _objectpathFT.getNameSpace = _driveGetNameSpace;
    _objectpathFT.setHostname = _driveSetHostname;
    _objectpathFT.getHostname = _driveGetHostname;
    _objectpathFT.setClassName = _driveSetClassName;
    _objectpathFT.getClassName = _driveGetClassName;
    _objectpathFT.addKey = _driveAddKey;
    _objectpathFT.getKey = _driveGetKey;
    _objectpathFT.getKeyAt = _driveGetKeyAt;
    _objectpathFT.getKeyCount = _driveGetKeyCount;
    _objectpathFT.setHostAndNameSpaceFromObjectPath = 
        _driveSetHostAndNameSpaceFromObjectPath;
    _objectpathFT.getClassQualifier = _driveGetClassQualifier;
    _objectpathFT.getPropertyQualifier = _driveGetPropertyQualifier;
    _objectpathFT.getParameterQualifier = _driveGetParameterQualifier;
    _objectpathFT.toString = _driveToString;

    _objectpath.ft = &_objectpathFT;
}

Broker::CmpiObjectPath::~CmpiObjectPath()
{
}

CMPIObjectPath *
Broker::CmpiObjectPath::toCMPI()
{
    return &_objectpath;
}

CMPIStatus 
Broker::CmpiObjectPath::_driveRelease(CMPIObjectPath *op)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->release();
}

CMPIObjectPath * 
Broker::CmpiObjectPath::_driveClone(const CMPIObjectPath *op, CMPIStatus *rc)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->clone(rc);
}

CMPIStatus 
Broker::CmpiObjectPath::_driveSetNameSpace(CMPIObjectPath *op, const char *ns)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->setNameSpace(ns);
}

CMPIString * 
Broker::CmpiObjectPath::_driveGetNameSpace(const CMPIObjectPath *op, 
                                           CMPIStatus *rc)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->getNameSpace(rc);
}

CMPIStatus 
Broker::CmpiObjectPath::_driveSetHostname(CMPIObjectPath *op, const char *hn)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->setHostname(hn);
}

CMPIString * 
Broker::CmpiObjectPath::_driveGetHostname(const CMPIObjectPath *op, 
                                          CMPIStatus *rc)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->getHostname(rc);
}

CMPIStatus 
Broker::CmpiObjectPath::_driveSetClassName(CMPIObjectPath *op, const char *cn)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->setClassName(cn);
}

CMPIString *
Broker::CmpiObjectPath::_driveGetClassName(const CMPIObjectPath *op, 
                                           CMPIStatus *rc)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->getClassName(rc);
}

CMPIStatus 
Broker::CmpiObjectPath::_driveAddKey(CMPIObjectPath *op, const char *name,
                                     const CMPIValue *value, CMPIType type)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->addKey(name, value, type);
}

CMPIData 
Broker::CmpiObjectPath::_driveGetKey(const CMPIObjectPath *op, const char *name,
                                     CMPIStatus *rc)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->getKey(name, rc);
}

CMPIData 
Broker::CmpiObjectPath::_driveGetKeyAt(const CMPIObjectPath *op, 
                                       unsigned int index, CMPIString **name,
                                       CMPIStatus *rc)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->getKeyAt(index, name, rc);
}

unsigned int 
Broker::CmpiObjectPath::_driveGetKeyCount(const CMPIObjectPath *op,
                                          CMPIStatus *rc)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->getKeyCount(rc);
}

CMPIStatus Broker::CmpiObjectPath::
_driveSetNameSpaceFromObjectPath(CMPIObjectPath *op,
                                 const CMPIObjectPath *src)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->setNamespaceFromObjectPath(src);
}

CMPIStatus Broker::CmpiObjectPath::
_driveSetHostAndNameSpaceFromObjectPath(CMPIObjectPath *op,
                                        const CMPIObjectPath *src)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->setHostAndNameSpaceFromObjectPath(src);
}
	
CMPIData 
Broker::CmpiObjectPath::_driveGetClassQualifier(const CMPIObjectPath *, // op
                                                const char *, // qName
                                                CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return nullData;
}

CMPIData 
Broker::CmpiObjectPath::_driveGetPropertyQualifier(const CMPIObjectPath *, // op
                                                   const char *, // pName
                                                   const char *, // qName
                                                   CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return nullData;
}

CMPIData 
Broker::CmpiObjectPath::_driveGetMethodQualifier(const CMPIObjectPath *, // op
                                                 const char *, // methodName
                                                 const char *, // qName
                                                 CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return nullData;
}

CMPIData 
Broker::CmpiObjectPath::_driveGetParameterQualifier(const CMPIObjectPath *,// op
                                                    const char *, // mName
                                                    const char *, // pName
                                                    const char *, // qName
                                                    CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return nullData;
}
	
CMPIString *
Broker::CmpiObjectPath::_driveToString(const CMPIObjectPath *op, CMPIStatus *rc)
{
    Broker::CmpiObjectPath *obj = 
        reinterpret_cast<Broker::CmpiObjectPath *>(op->hdl);

    return obj->toString(rc);
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
