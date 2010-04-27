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

#include "CmpiBrokerResult.h"
#include "CmpiStatus.h"

using namespace CmpiCpp;

Broker::CmpiResult::CmpiResult()
{
    _result.hdl = (void *)this;

    _resultFT.ftVersion = CMPICurrentVersion;

    _resultFT.release = _driveRelease;
    _resultFT.clone = _driveClone;
    _resultFT.returnData = _driveReturnData;
    _resultFT.returnInstance = _driveReturnInstance;
    _resultFT.returnObjectPath = _driveReturnObjectPath;
    _resultFT.returnDone = _driveReturnDone;

    _result.ft = &_resultFT;
}

Broker::CmpiResult::~CmpiResult()
{
}

CMPIResult *
Broker::CmpiResult::toCMPI()
{
    return &_result;
}

CMPIStatus 
Broker::CmpiResult::_driveRelease(CMPIResult *result)
{
    Broker::CmpiResult *obj = 
        reinterpret_cast<Broker::CmpiResult *>(result->hdl);

    return obj->release();
}

CMPIResult *
Broker::CmpiResult::_driveClone(const CMPIResult *r, CMPIStatus *rc)
{
    Broker::CmpiResult *obj = reinterpret_cast<Broker::CmpiResult *>(r->hdl);

    return obj->clone(rc);
}

CMPIStatus 
Broker::CmpiResult::_driveReturnData(const CMPIResult *result,
                                     const CMPIValue *value,
                                     CMPIType type)
{
    Broker::CmpiResult *obj = 
        reinterpret_cast<Broker::CmpiResult *>(result->hdl);

    return obj->returnData(value, type);
}

CMPIStatus 
Broker::CmpiResult::_driveReturnInstance(const CMPIResult *result,
                                         const CMPIInstance *inst)
{
    Broker::CmpiResult *obj = 
        reinterpret_cast<Broker::CmpiResult *>(result->hdl);

    return obj->returnInstance(inst);
}

CMPIStatus 
Broker::CmpiResult::_driveReturnObjectPath(const CMPIResult *result,
                                           const CMPIObjectPath *ref)
{
    Broker::CmpiResult *obj = 
        reinterpret_cast<Broker::CmpiResult *>(result->hdl);

    return obj->returnObjectPath(ref);
}

CMPIStatus 
Broker::CmpiResult::_driveReturnDone(const CMPIResult *r)
{
    Broker::CmpiResult *obj = reinterpret_cast<Broker::CmpiResult *>(r->hdl);

    return obj->returnDone();
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
