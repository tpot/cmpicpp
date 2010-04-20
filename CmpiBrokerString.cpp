//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "CmpiBrokerString.h"
#include "CmpiStatus.h"

using namespace CmpiCpp;

Broker::CmpiString::CmpiString()
{
    _string.hdl = (void *)this;

    _stringFT.ftVersion = CMPICurrentVersion;
    _stringFT.release = _driveRelease;
    _stringFT.clone = _driveClone;
    _stringFT.getCharPtr = _driveGetCharPtr;

    _string.ft = &_stringFT;
}

Broker::CmpiString::~CmpiString()
{
}

CMPIString *
Broker::CmpiString::toCMPI()
{
    return &_string;
}

CMPIStatus 
Broker::CmpiString::_driveRelease(CMPIString *st)
{
    Broker::CmpiString *obj = reinterpret_cast<Broker::CmpiString *>(st->hdl);
    
    return obj->release();
}

CMPIString *
Broker::CmpiString::_driveClone(const CMPIString *st, CMPIStatus *rc)
{
    Broker::CmpiString *obj = reinterpret_cast<Broker::CmpiString *>(st->hdl);

    return obj->clone(rc);
}

char *
Broker::CmpiString::_driveGetCharPtr(const CMPIString *st, CMPIStatus *rc)
{
    Broker::CmpiString *obj = reinterpret_cast<Broker::CmpiString *>(st->hdl);

    return obj->getCharPtr(rc);
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
