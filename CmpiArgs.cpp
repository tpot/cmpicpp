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

#include "cmpidt.h"
#include "cmpift.h"

#include "CmpiArgs.h"
#include "CmpiStatus.h"
#include "CmpiBroker.h"

using namespace std;
using namespace CmpiCpp;

CmpiArgs::CmpiArgs(const CMPIArgs *args)
{
    _data = const_cast<CMPIArgs *>(args);
    _wasCloned = false;
}

CmpiArgs::CmpiArgs(const CmpiArgs &args)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    _data = args._data->ft->clone(args._data, &status);
    _wasCloned = true;

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiArgs::~CmpiArgs()
{
    // Don't check return value and throw an exception - it's a pretty
    // bad idea.

    if (_wasCloned)
        _data->ft->release(_data);
}

void 
CmpiArgs::addArg(const CmpiName &name, bool value)
{
    CMPIValue v;
    v.boolean = value;

    CMPIStatus status =
        _data->ft->addArg(_data, name.str().c_str(), &v, CMPI_boolean);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, CMPIUint8 value)
{
    CMPIValue v;
    v.uint8 = value;

    CMPIStatus status = 
        _data->ft->addArg(_data, name.str().c_str(), &v, CMPI_uint8);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, CMPISint8 value)
{
    CMPIValue v;
    v.sint8 = value;

    CMPIStatus status = 
        _data->ft->addArg(_data, name.str().c_str(), &v, CMPI_sint8);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, CMPIUint16 value)
{
    CMPIValue v;
    v.uint16 = value;

    CMPIStatus status =
        _data->ft->addArg(_data, name.str().c_str(), &v, CMPI_uint16);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, CMPISint16 value)
{
    CMPIValue v;
    v.sint16 = value;

    CMPIStatus status =
        _data->ft->addArg(_data, name.str().c_str(), &v, CMPI_sint16);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, CMPIUint32 value)
{
    CMPIValue v;
    v.uint32 = value;

    CMPIStatus status =
        _data->ft->addArg(_data, name.str().c_str(), &v, CMPI_uint32);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, CMPISint32 value)
{
    CMPIValue v;
    v.sint32 = value;

    CMPIStatus status = 
        _data->ft->addArg(_data, name.str().c_str(), &v, CMPI_sint32);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, CMPIUint64 value)
{
    CMPIValue v;
    v.uint64 = value;

    CMPIStatus status =
        _data->ft->addArg(_data, name.str().c_str(), &v, CMPI_uint64);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, CMPISint64 value)
{
    CMPIValue v;
    v.sint64 = value;

    CMPIStatus status =
        _data->ft->addArg(_data, name.str().c_str(), &v, CMPI_sint64);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, CMPIReal32 value)
{
    CMPIValue v;
    v.real32 = value;

    CMPIStatus status =
        _data->ft->addArg(_data, name.str().c_str(), &v, CMPI_real32);    
    
    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, CMPIReal64 value)
{
    CMPIValue v;
    v.real64 = value;

    CMPIStatus status =
        _data->ft->addArg(_data, name.str().c_str(), &v, CMPI_real64);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, const char *value)
{
    CMPIStatus status = 
        _data->ft->addArg(_data, name.c_str(), 
                          reinterpret_cast<const CMPIValue *>(value),
                          CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void 
CmpiArgs::addArg(const CmpiName &name, const string &value)
{
    CMPIStatus status = 
        _data->ft->addArg(_data, name.c_str(), 
                          reinterpret_cast<const CMPIValue *>(value.c_str()),
                          CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiData 
CmpiArgs::getArg(const string &name) const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIData d = _data->ft->getArg(_data, name.c_str(), &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return CmpiData(&d);    
}

pair<CmpiName,CmpiData> 
CmpiArgs::getArgAt(unsigned int index) const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIString *name;
    CMPIData d = _data->ft->getArgAt(_data, index, &name, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiName keyname(CMGetCharsPtr(name, &status));

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return make_pair(keyname, CmpiData(&d));
}

unsigned int 
CmpiArgs::getArgCount() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    unsigned int result = _data->ft->getArgCount(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return result;
}

CMPIArgs *
CmpiArgs::toCMPI() const
{
   return _data;
}

// Factory function

CmpiArgs 
CmpiCpp::makeCmpiArgs(const CmpiBroker &broker)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    const CMPIBroker *b = broker.toCMPI();

    CMPIArgs *args = b->eft->newArgs(b, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiArgs result(args);

    return result;
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
