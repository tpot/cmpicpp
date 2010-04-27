//
// Copyright (C) 2009 by Hewlett-Packard Development Company L.P.
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

#include "CmpiCppClientUtils.h"

using namespace std;
using namespace CmpiCpp;

// Implementation of InstanceVectorEnumeration class

InstanceVectorEnumeration::
InstanceVectorEnumeration(const vector<CmpiInstance> &data)
    : _data(data), _iter(_data.begin())
{
}

InstanceVectorEnumeration::~InstanceVectorEnumeration()
{
}

CMPIStatus 
InstanceVectorEnumeration::release()
{
    delete this;

    CMPIStatus result = { CMPI_RC_OK, NULL };
    return result;
}

CMPIEnumeration *
InstanceVectorEnumeration::clone(CMPIStatus *rc)
{
    InstanceVectorEnumeration *result = new InstanceVectorEnumeration(_data);

    if (rc) {
        rc->rc = CMPI_RC_OK;
        rc->msg = NULL;
    }

    return result->toCMPI();
}

CMPIData 
InstanceVectorEnumeration::getNext(CMPIStatus *)
{
    CMPIData result;

    result.type = CMPI_instance;
    result.state = CMPI_goodValue;
    result.value.inst = _iter->toCMPI();

    _iter++;

    return result;
}

CMPIBoolean 
InstanceVectorEnumeration::hasNext(CMPIStatus *)
{
    return _iter != _data.end();
}

CMPIArray *
InstanceVectorEnumeration::toArray(CMPIStatus *rc)
{
    // Not implemented

    if (rc) {
        rc->rc = CMPI_RC_ERR_FAILED;
        rc->msg = NULL;
    }

    return NULL;
}

// Implementation of ObjectPathVectorEnumeration class

ObjectPathVectorEnumeration::
ObjectPathVectorEnumeration(const vector<CmpiObjectPath> &data)
    : _data(data), _iter(_data.begin())
{
}

ObjectPathVectorEnumeration::~ObjectPathVectorEnumeration()
{
}

CMPIStatus 
ObjectPathVectorEnumeration::release()
{
    delete this;

    CMPIStatus result = { CMPI_RC_OK, NULL };
    return result;
}

CMPIEnumeration *
ObjectPathVectorEnumeration::clone(CMPIStatus *rc)
{
    ObjectPathVectorEnumeration *result = 
        new ObjectPathVectorEnumeration(_data);

    if (rc) {
        rc->rc = CMPI_RC_OK;
        rc->msg = NULL;
    }

    return result->toCMPI();
}

CMPIData 
ObjectPathVectorEnumeration::getNext(CMPIStatus *)
{
    CMPIData result;

    result.type = CMPI_ref;
    result.state = CMPI_goodValue;
    result.value.ref = _iter->toCMPI();

    _iter++;

    return result;
}

CMPIBoolean 
ObjectPathVectorEnumeration::hasNext(CMPIStatus *)
{
    return _iter != _data.end();
}

CMPIArray *
ObjectPathVectorEnumeration::toArray(CMPIStatus *rc)
{
    // Not implemented

    if (rc) {
        rc->rc = CMPI_RC_ERR_FAILED;
        rc->msg = NULL;
    }

    return NULL;
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
