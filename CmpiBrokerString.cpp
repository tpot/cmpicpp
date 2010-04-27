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

const char *
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
