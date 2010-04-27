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

#include "CmpiBrokerDateTime.h"

using namespace CmpiCpp;

Broker::CmpiDateTime::CmpiDateTime()
{
    _datetime.hdl = this;

    _datetimeFT.ftVersion = CMPICurrentVersion;
    _datetimeFT.release = _driveRelease;
    _datetimeFT.clone = _driveClone;
    _datetimeFT.getBinaryFormat = _driveGetBinaryFormat;
    _datetimeFT.getStringFormat = _driveGetStringFormat;
    _datetimeFT.isInterval = _driveIsInterval;

    _datetime.ft = &_datetimeFT;
}

Broker::CmpiDateTime::~CmpiDateTime()
{
}

CMPIDateTime *
Broker::CmpiDateTime::toCMPI()
{
    return &_datetime;
}

CMPIStatus 
Broker::CmpiDateTime::_driveRelease(CMPIDateTime *dt)
{
    Broker::CmpiDateTime *obj = 
      reinterpret_cast<Broker::CmpiDateTime *>(dt->hdl);

    return obj->release();
}

CMPIDateTime *
Broker::CmpiDateTime::_driveClone(const CMPIDateTime *dt, CMPIStatus *rc)
{
    Broker::CmpiDateTime *obj = 
      reinterpret_cast<Broker::CmpiDateTime *>(dt->hdl);

    return obj->clone(rc);
}

CMPIUint64 
Broker::CmpiDateTime::_driveGetBinaryFormat(const CMPIDateTime *dt,
					    CMPIStatus *rc)
{
    Broker::CmpiDateTime *obj = 
      reinterpret_cast<Broker::CmpiDateTime *>(dt->hdl);

    return obj->getBinaryFormat(rc);
}

CMPIString *
Broker::CmpiDateTime::_driveGetStringFormat(const CMPIDateTime *dt,
					    CMPIStatus *rc)
{
    Broker::CmpiDateTime *obj = 
      reinterpret_cast<Broker::CmpiDateTime *>(dt->hdl);

    return obj->getStringFormat(rc);
}

CMPIBoolean
Broker::CmpiDateTime::_driveIsInterval(const CMPIDateTime *dt,
				       CMPIStatus *rc)
{
    Broker::CmpiDateTime *obj = 
      reinterpret_cast<Broker::CmpiDateTime *>(dt->hdl);
    
    return obj->isInterval(rc);
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
