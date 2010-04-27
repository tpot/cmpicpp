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

#include "CmpiBrokerArray.h"
#include "CmpiStatus.h"

using namespace CmpiCpp;

Broker::CmpiArray::CmpiArray()
{
    _array.hdl = this;

    _arrayFT.ftVersion = CMPICurrentVersion;
    _arrayFT.release = _driveRelease;
    _arrayFT.clone = _driveClone;
    _arrayFT.getSize = _driveGetSize;
    _arrayFT.getSimpleType = _driveGetSimpleType;
    _arrayFT.getElementAt = _driveGetElementAt;
    _arrayFT.setElementAt = _driveSetElementAt;

    _array.ft = &_arrayFT;
}

Broker::CmpiArray::~CmpiArray()
{
}

CMPIArray *
Broker::CmpiArray::toCMPI()
{
    return &_array;
}

CMPIStatus 
Broker::CmpiArray::_driveRelease(CMPIArray *ar)
{
    Broker::CmpiArray *obj = reinterpret_cast<Broker::CmpiArray *>(ar->hdl);

    return obj->release();
}

CMPIArray *
Broker::CmpiArray::_driveClone(const CMPIArray *ar, CMPIStatus *rc)
{
    Broker::CmpiArray *obj = reinterpret_cast<Broker::CmpiArray *>(ar->hdl);

    return obj->clone(rc);
}

CMPICount 
Broker::CmpiArray::_driveGetSize(const CMPIArray *ar, CMPIStatus *rc)
{
    Broker::CmpiArray *obj = reinterpret_cast<Broker::CmpiArray *>(ar->hdl);

    return obj->getSize(rc);
}

CMPIType 
Broker::CmpiArray::_driveGetSimpleType(const CMPIArray *ar, CMPIStatus *rc)
{
    Broker::CmpiArray *obj = reinterpret_cast<Broker::CmpiArray *>(ar->hdl);

    return obj->getSimpleType(rc);
}

CMPIData 
Broker::CmpiArray::_driveGetElementAt(const CMPIArray *ar, CMPICount index,
                                      CMPIStatus *rc)
{
    Broker::CmpiArray *obj = reinterpret_cast<Broker::CmpiArray *>(ar->hdl);

    return obj->getElementAt(index, rc);
}

CMPIStatus 
Broker::CmpiArray::_driveSetElementAt(CMPIArray *ar, CMPICount index,
                                      const CMPIValue *value, CMPIType type)
{
    Broker::CmpiArray *obj = reinterpret_cast<Broker::CmpiArray *>(ar->hdl);

    return obj->setElementAt(index, value, type);
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
