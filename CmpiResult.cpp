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

#include "cmpift.h"

#include "CmpiData.h"
#include "CmpiName.h"
#include "CmpiResult.h"
#include "CmpiStatus.h"
#include "CmpiInstance.h"
#include "CmpiObjectPath.h"

using namespace std;
using namespace CmpiCpp;

//
// Implementation of DeliverObjectPathResult
//

DeliverObjectPathResult::DeliverObjectPathResult(const CMPIResult *result)
    : _result(result)
{
}

DeliverObjectPathResult::~DeliverObjectPathResult()
{
    _result->ft->returnDone(_result);
}

void 
DeliverObjectPathResult::deliver(const CmpiObjectPath &data)
{
    CMPIStatus status = _result->ft->returnObjectPath(_result, data.toCMPI());

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

//
// Implementation of DeliverInstanceResult
//

DeliverInstanceResult::DeliverInstanceResult(const CMPIResult *result)
    : _result(result)
{
   _deliverDone=true;
}

DeliverInstanceResult::~DeliverInstanceResult()
{
   if ( _deliverDone)
      _result->ft->returnDone(_result);
}

void 
DeliverInstanceResult::deliver(const CmpiInstance &data)
{
    CMPIStatus status = _result->ft->returnInstance(_result, data.toCMPI());

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

//
// Implementation of CmpiMethodResult
//

DeliverMethodResult::DeliverMethodResult(const CMPIResult *result,
                                         const CMPIArgs *out)
    : _result(result), _out(out)
{
}

DeliverMethodResult::~DeliverMethodResult()
{
    _result->ft->returnDone(_result);
}

// Deliver return value

void 
DeliverMethodResult::deliver(const CmpiData &value)
{
    CMPIData d = value.toCMPI();

    CMPIStatus status = _result->ft->returnData(_result, &d.value, d.type);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
DeliverMethodResult::deliver(CMPIUint8 value)
{
    CMPIData d;
    d.type = CMPI_uint8;
    d.state = CMPI_goodValue;
    d.value.uint8 = value;

    deliver(CmpiData(&d));
}

void 
DeliverMethodResult::deliver(CMPISint8 value)
{
    CMPIData d;
    d.type = CMPI_sint8;
    d.state = CMPI_goodValue;
    d.value.sint8 = value;

    deliver(CmpiData(&d));
}

void 
DeliverMethodResult::deliver(CMPIUint16 value)
{
    CMPIData d;
    d.type = CMPI_uint16;
    d.state = CMPI_goodValue;
    d.value.uint16 = value;

    deliver(CmpiData(&d));
}

void 
DeliverMethodResult::deliver(CMPISint16 value)
{
    CMPIData d;
    d.type = CMPI_sint16;
    d.state = CMPI_goodValue;
    d.value.sint16 = value;

    deliver(CmpiData(&d));
}

void 
DeliverMethodResult::deliver(CMPIUint32 value)
{
    CMPIData d;
    d.type = CMPI_uint32;
    d.state = CMPI_goodValue;
    d.value.uint32 = value;

    deliver(CmpiData(&d));
}

void 
DeliverMethodResult::deliver(CMPISint32 value)
{
    CMPIData d;
    d.type = CMPI_sint32;
    d.state = CMPI_goodValue;
    d.value.sint32 = value;

    deliver(CmpiData(&d));
}

void 
DeliverMethodResult::deliver(CMPIUint64 value)
{
    CMPIData d;
    d.type = CMPI_uint64;
    d.state = CMPI_goodValue;
    d.value.uint64 = value;

    deliver(CmpiData(&d));
}

void 
DeliverMethodResult::deliver(CMPISint64 value)
{
    CMPIData d;
    d.type = CMPI_sint64;
    d.state = CMPI_goodValue;
    d.value.sint64 = value;

    deliver(CmpiData(&d));
}

void 
DeliverMethodResult::deliver(CMPIReal32 value)
{
    CMPIData d;
    d.type = CMPI_real32;
    d.state = CMPI_goodValue;
    d.value.real32 = value;

    deliver(CmpiData(&d));
}

void 
DeliverMethodResult::deliver(CMPIReal64 value)
{
    CMPIData d;
    d.type = CMPI_real64;
    d.state = CMPI_goodValue;
    d.value.real64 = value;

    deliver(CmpiData(&d));
}

void 
DeliverMethodResult::deliver(bool value)
{
    CMPIData d;
    d.type = CMPI_boolean;
    d.state = CMPI_goodValue;
    d.value.boolean = value;

    deliver(CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const char *value)
{
    CMPIData d;
    d.type = CMPI_chars;
    d.state = CMPI_goodValue;
    d.value.chars = const_cast<char *>(value);

    deliver(CmpiData(&d));    
}

void 
DeliverMethodResult::deliver(const string &value)
{
    CMPIData d;
    d.type = CMPI_chars;
    d.state = CMPI_goodValue;
    d.value.chars = const_cast<char *>(value.c_str());

    deliver(CmpiData(&d));    
}

void 
DeliverMethodResult::deliver(const CmpiObjectPath &value)
{
    CMPIData d;
    d.type = CMPI_ref;
    d.state = CMPI_goodValue;
    d.value.ref = value.toCMPI();

    deliver(CmpiData(&d));    
}

// Deliver output parameters

void 
DeliverMethodResult::deliver(const CmpiName &key, const CmpiData &value)
{
    CMPIData d = value.toCMPI();

    CMPIStatus status =
        _out->ft->addArg(_out, key.str().c_str(), &d.value, d.type);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
DeliverMethodResult::deliver(const CmpiName &key, CMPIUint8 value)
{
    CMPIData d;
    d.type = CMPI_uint8;
    d.state = CMPI_goodValue;
    d.value.uint8 = value;

    deliver(key, CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const CmpiName &key, CMPISint8 value)
{
    CMPIData d;
    d.type = CMPI_sint8;
    d.state = CMPI_goodValue;
    d.value.sint8 = value;

    deliver(key, CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const CmpiName &key, CMPIUint16 value)
{
    CMPIData d;
    d.type = CMPI_uint16;
    d.state = CMPI_goodValue;
    d.value.uint16 = value;

    deliver(key,CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const CmpiName &key, CMPISint16 value)
{
    CMPIData d;
    d.type = CMPI_sint16;
    d.state = CMPI_goodValue;
    d.value.sint16 = value;

    deliver(key, CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const CmpiName &key, CMPIUint32 value)
{
    CMPIData d;
    d.type = CMPI_uint32;
    d.state = CMPI_goodValue;
    d.value.uint32 = value;

    deliver(key, CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const CmpiName &key, CMPISint32 value)
{
    CMPIData d;
    d.type = CMPI_sint32;
    d.state = CMPI_goodValue;
    d.value.sint32 = value;

    deliver(key, CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const CmpiName &key, CMPIUint64 value)
{
    CMPIData d;
    d.type = CMPI_uint64;
    d.state = CMPI_goodValue;
    d.value.uint64 = value;

    deliver(key, CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const CmpiName &key, CMPISint64 value)
{
    CMPIData d;
    d.type = CMPI_sint64;
    d.state = CMPI_goodValue;
    d.value.sint64 = value;

    deliver(key, CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const CmpiName &key, CMPIReal32 value)
{
    CMPIData d;
    d.type = CMPI_real32;
    d.state = CMPI_goodValue;
    d.value.real32 = value;

    deliver(key, CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const CmpiName &key, CMPIReal64 value)
{
    CMPIData d;
    d.type = CMPI_real64;
    d.state = CMPI_goodValue;
    d.value.real64 = value;

    deliver(key, CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const CmpiName &key, bool value)
{
    CMPIData d;
    d.type = CMPI_boolean;
    d.state = CMPI_goodValue;
    d.value.boolean = value;

    deliver(key, CmpiData(&d));
}

void 
DeliverMethodResult::deliver(const CmpiName &key, const char *value)
{
    CMPIStatus status =
        _out->ft->addArg(_out, key.str().c_str(), 
                         reinterpret_cast<const CMPIValue *>(value), 
                         CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
DeliverMethodResult::deliver(const CmpiName &key, const string &value)
{
    CMPIStatus status =
        _out->ft->addArg(_out, key.str().c_str(), 
                         reinterpret_cast<const CMPIValue *>(value.c_str()), 
                         CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
DeliverMethodResult::deliver(const CmpiName &key, const CmpiObjectPath &value)
{
    CMPIData d;
    d.type = CMPI_ref;
    d.state = CMPI_goodValue;
    d.value.ref = value.toCMPI();

    deliver(key, CmpiData(&d));    
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
