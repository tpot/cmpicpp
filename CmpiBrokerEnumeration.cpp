//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "CmpiBrokerEnumeration.h"

using namespace CmpiCpp;

Broker::CmpiEnumeration::CmpiEnumeration()
{
    _enumeration.hdl = (void *)this;

    _enumerationFT.ftVersion = CMPICurrentVersion;
    _enumerationFT.release = _driveRelease;
    _enumerationFT.clone = _driveClone;
    _enumerationFT.getNext = _driveGetNext;
    _enumerationFT.hasNext = _driveHasNext;
    _enumerationFT.toArray = _driveToArray;

    _enumeration.ft = &_enumerationFT;
}

Broker::CmpiEnumeration::~CmpiEnumeration()
{
}

CMPIEnumeration *
Broker::CmpiEnumeration::toCMPI()
{
    return &_enumeration;
}

CMPIStatus 
Broker::CmpiEnumeration::_driveRelease(CMPIEnumeration *en)
{
    Broker::CmpiEnumeration *obj = 
      reinterpret_cast<Broker::CmpiEnumeration *>(en->hdl);
    
    return obj->release();
}

CMPIEnumeration *
Broker::CmpiEnumeration::_driveClone(const CMPIEnumeration *en, CMPIStatus *rc)
{
    Broker::CmpiEnumeration *obj = 
      reinterpret_cast<Broker::CmpiEnumeration *>(en->hdl);

    return obj->clone(rc);
}

CMPIData 
Broker::CmpiEnumeration::_driveGetNext(const CMPIEnumeration *en,
				       CMPIStatus *rc)
{
    Broker::CmpiEnumeration *obj = 
      reinterpret_cast<Broker::CmpiEnumeration *>(en->hdl);

    return obj->getNext(rc);
}

CMPIBoolean 
Broker::CmpiEnumeration::_driveHasNext(const CMPIEnumeration *en,
				       CMPIStatus *rc)
{
    Broker::CmpiEnumeration *obj = 
      reinterpret_cast<Broker::CmpiEnumeration *>(en->hdl);

    return obj->hasNext(rc);
}

CMPIArray *
Broker::CmpiEnumeration::_driveToArray(const CMPIEnumeration *en,
				       CMPIStatus *rc)
{
    Broker::CmpiEnumeration *obj = 
      reinterpret_cast<Broker::CmpiEnumeration *>(en->hdl);

    return obj->toArray(rc);
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
