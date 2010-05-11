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

#include <algorithm>
#include <ctype.h>
#include <sstream>

#include "cmpift.h"

#include "CmpiData.h"
#include "CmpiName.h"
#include "CmpiStatus.h"
#include "CmpiBroker.h"
#include "CmpiObjectPath.h"

using namespace std;
using namespace CmpiCpp;

CmpiObjectPath::CmpiObjectPath(const CmpiObjectPath &path)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    _data = path._data->ft->clone(path._data, &status);
    _wasCloned = true;

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiObjectPath::CmpiObjectPath(const CMPIObjectPath *path)
{
    _data = const_cast<CMPIObjectPath *>(path);
    _wasCloned = false;
}

CmpiObjectPath::~CmpiObjectPath()
{
    // Don't check return value and throw an exception - it's a pretty
    // bad idea.

    if (_wasCloned)
        _data->ft->release(_data);
}

CmpiName CmpiObjectPath::getHost() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIString *s = _data->ft->getHostname(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiName result(CMGetCharsPtr(s, &status));

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return result;
}

void CmpiObjectPath::setHost(const CmpiName &host)
{
    CMPIStatus status = _data->ft->setHostname(_data, host.str().c_str());

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);    
}

CmpiName CmpiObjectPath::getNameSpace() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIString *s = _data->ft->getNameSpace(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiName result(CMGetCharsPtr(s, &status));

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return result;
}

void CmpiObjectPath::setNameSpace(const CmpiName &nameSpace)
{
    CMPIStatus status = _data->ft->setNameSpace(_data, nameSpace.str().c_str());

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiName CmpiObjectPath::getClassName() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIString *s = _data->ft->getClassName(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiName result(CMGetCharsPtr(s, &status));

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return result;
}

void CmpiObjectPath::setClassName(const CmpiName &className)
{
    CMPIStatus status = _data->ft->setClassName(_data, className.str().c_str());

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CMPIObjectPath *CmpiObjectPath::toCMPI() const
{
    return _data;
}

void CmpiObjectPath::addKey(const CmpiName &key, const CmpiData &value)
{
    CMPIData v = value.toCMPI();

    CMPIStatus status =
        _data->ft->addKey(_data, key.str().c_str(), &v.value, v.type);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, const CmpiObjectPath &value)
{
    CMPIValue v;
    v.ref = value.toCMPI();

    CMPIStatus status = 
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_ref);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, CMPIUint8 value)
{
    CMPIValue v;
    v.uint8 = value;

    CMPIStatus status = 
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_uint8);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, CMPISint8 value)
{
    CMPIValue v;
    v.sint8 = value;

    CMPIStatus status = 
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_sint8);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, CMPIUint16 value)
{
    CMPIValue v;
    v.uint16 = value;

    CMPIStatus status =
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_uint16);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, CMPISint16 value)
{
    CMPIValue v;
    v.sint16 = value;

    CMPIStatus status =
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_sint16);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, CMPIUint32 value)
{
    CMPIValue v;
    v.uint32 = value;

    CMPIStatus status =
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_uint32);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, CMPISint32 value)
{
    CMPIValue v;
    v.sint32 = value;

    CMPIStatus status = 
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_sint32);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, CMPIUint64 value)
{
    CMPIValue v;
    v.uint64 = value;

    CMPIStatus status =
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_uint64);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, CMPISint64 value)
{
    CMPIValue v;
    v.sint64 = value;

    CMPIStatus status =
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_sint64);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, CMPIReal32 value)
{
    CMPIValue v;
    v.real32 = value;

    CMPIStatus status =
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_real32);    
    
    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, CMPIReal64 value)
{
    CMPIValue v;
    v.real64 = value;

    CMPIStatus status =
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_real64);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, bool value)
{
    CMPIValue v;
    v.boolean = value;

    CMPIStatus status =
        _data->ft->addKey(_data, key.str().c_str(), &v, CMPI_boolean);    

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, const char *value)
{
    CMPIStatus status =
        _data->ft->addKey(_data, key.str().c_str(),
                          reinterpret_cast<const CMPIValue *>(value), 
                          CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, const string &value)
{
    CMPIStatus status =
        _data->ft->addKey(_data, key.str().c_str(), 
                          reinterpret_cast<const CMPIValue *>(value.c_str()),
                          CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiObjectPath::addKey(const CmpiName &key, const stringstream &value)
{
    // Calling addKey() of a stringstream instead of calling
    // stringstream.str() is an easy mistake to make and unfortunately
    // this is cast to a bool by the compiler.

    CMPIStatus status =
        _data->ft->addKey(
            _data, key.str().c_str(), 
            reinterpret_cast<const CMPIValue *>(value.str().c_str()),
            CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiData CmpiObjectPath::getKey(const CmpiName &key) const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIData d = _data->ft->getKey(_data, key.str().c_str(), &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return CmpiData(&d);
}

pair<CmpiName,CmpiData> CmpiObjectPath::getKeyAt(unsigned int ndx) const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    CMPIString *name;
    CMPIData d = _data->ft->getKeyAt(_data, ndx, &name, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiName keyname(CMGetCharsPtr(name, &status));

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return make_pair(keyname, CmpiData(&d));
}

unsigned int CmpiObjectPath::getKeyCount() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    unsigned int result = _data->ft->getKeyCount(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return result;
}

bool CmpiObjectPath::operator==(const CmpiObjectPath &obj) const
{
    // Compare classname, namespace and hostname

    if (getClassName() != obj.getClassName())
        return false;

    if (getNameSpace() != obj.getNameSpace())
        return false;

    if (getHost() != obj.getHost())
        return false;

    // Compare key counts

    if (getKeyCount() != obj.getKeyCount())
        return false;

    // Compare key values

    for (unsigned int a = 0; a < getKeyCount(); a++) {

        pair<CmpiName,CmpiData> aKey = getKeyAt(a);
        bool found = false;

        for (unsigned int b = 0; b < obj.getKeyCount(); b++) {
            pair<CmpiName,CmpiData> bKey = obj.getKeyAt(b);

            if (aKey == bKey) {
                found = true;
                break;
            }
        }

        if (!found)
            return false;
    }

    return true;
}

bool CmpiObjectPath::operator!=(const CmpiObjectPath &obj) const
{
    return !(*this == obj);
}

CmpiObjectPath &CmpiObjectPath::operator=(const CmpiObjectPath &rhs)
{
    if (this == &rhs)
        return *this;

    // Release lhs

    CMPIStatus status;

    if (_wasCloned) {

        status = _data->ft->release(_data);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);
    }

    // Assign rhs to lhs

    status.rc = CMPI_RC_OK;
    status.msg = NULL;

    _data = rhs._data->ft->clone(rhs._data, &status);
    _wasCloned = true;

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return *this;
}

string CmpiObjectPath::str() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    CMPIString *s = _data->ft->toString(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    string result(CMGetCharsPtr(s, &status));

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return result;
}

bool CmpiObjectPath::empty() const
{
    return getHost().empty() && getNameSpace().empty() && 
        getClassName().empty() && getKeyCount() == 0;
}

bool CmpiObjectPath::classPathIsA(const CmpiBroker &broker, const string &parentClassName) 
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIBoolean isa = CMClassPathIsA(broker.toCMPI(), _data, parentClassName.c_str(), &status);
        
    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return bool(isa);
}

ostream &CmpiCpp::operator<<(ostream &output, const CmpiObjectPath &obj)
{
    output << obj.str();
    return output;
}

CmpiObjectPath 
CmpiCpp::makeCmpiObjectPath(const CmpiBroker &broker,
                            const CmpiName &nameSpace,
                            const CmpiName &className)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    const CMPIBroker *b = broker.toCMPI();
    
    CMPIObjectPath *path = b->eft->newObjectPath
        (b, nameSpace.c_str(), className.c_str(), &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiObjectPath result(path);

    result.setHost("");

    return result;
}


CmpiObjectPath 
CmpiCpp::makeCmpiObjectPath(const CmpiBroker &broker,
                            const CmpiName &nameSpace,
                            const CmpiName &className,
                            const CmpiName &hostName)
{
    CmpiObjectPath result(makeCmpiObjectPath(broker, nameSpace, className));
 
    result.setHost(hostName);

    return result;
}


CmpiObjectPath 
CmpiCpp::makeCmpiObjectPath(const CmpiBroker &broker)
{
    return makeCmpiObjectPath(broker, "", "");
}



bool
CmpiCpp::CMPIStringCompare(const CMPIString *a, const CMPIString *b)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    string acpp(CMGetCharsPtr(a, &status));
        
    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    string bcpp(CMGetCharsPtr(b, &status));

    if (status.rc != CMPI_RC_OK) 
        throw CmpiStatus(&status);

    return acpp == bcpp;
}

bool 
CmpiCpp::CMPIObjectPathCompare(const CMPIObjectPath *aPath, 
                               const CMPIObjectPath *bPath)
{
    // Ugh - what a mess!

    bool result = false;
    CMPIString *a, *b;
    string acpp, bcpp;
    unsigned int aCount, bCount;

    // Compare classname

    a = aPath->ft->getClassName(aPath, NULL);
    b = bPath->ft->getClassName(bPath, NULL);

    acpp.assign(CMGetCharsPtr(a, NULL));
    bcpp.assign(CMGetCharsPtr(b, NULL));

    transform(acpp.begin(), acpp.end(), acpp.begin(), ::tolower);
    transform(bcpp.begin(), bcpp.end(), bcpp.begin(), ::tolower);

    if (acpp != bcpp)
        goto done;

    a->ft->release(a);
    b->ft->release(b);

    // Compare namespace

    a = aPath->ft->getNameSpace(aPath, NULL);
    b = bPath->ft->getNameSpace(bPath, NULL);

    acpp.assign(CMGetCharsPtr(a, NULL));
    bcpp.assign(CMGetCharsPtr(b, NULL));

    transform(acpp.begin(), acpp.end(), acpp.begin(), ::tolower);
    transform(bcpp.begin(), bcpp.end(), bcpp.begin(), ::tolower);

    if (acpp != bcpp)
        goto done;

    a->ft->release(a);
    b->ft->release(b);

    // Compare hostname

    a = aPath->ft->getHostname(aPath, NULL);
    b = bPath->ft->getHostname(bPath, NULL);
 
    acpp.assign(CMGetCharsPtr(a, NULL));
    bcpp.assign(CMGetCharsPtr(b, NULL));

    transform(acpp.begin(), acpp.end(), acpp.begin(), ::tolower);
    transform(bcpp.begin(), bcpp.end(), bcpp.begin(), ::tolower);

    if (acpp != bcpp)
        goto done;

    // Compare key counts

    aCount = aPath->ft->getKeyCount(aPath, NULL);
    bCount = bPath->ft->getKeyCount(bPath, NULL);

    if (aCount != bCount)
        goto done;

    for (unsigned int aNdx = 0; aNdx < aCount; aNdx++) {

        CMPIString *aName, *bName = NULL;
        CMPIData aValue, bValue;

        aValue = aPath->ft->getKeyAt(aPath, aNdx, &aName, NULL);

        bool found = false;

        for (unsigned int bNdx = 0; bNdx < bCount; bNdx++) {

            bValue = bPath->ft->getKeyAt(bPath, bNdx, &bName, NULL);

            acpp.assign(CMGetCharsPtr(aName, NULL));
            bcpp.assign(CMGetCharsPtr(bName, NULL));

            transform(acpp.begin(), acpp.end(), acpp.begin(), ::tolower);
            transform(bcpp.begin(), bcpp.end(), bcpp.begin(), ::tolower);

            if (acpp == bcpp && CmpiData(&aValue) == CmpiData(&bValue)) {
                found = true;
                goto done_ndx;
            }
        }

    done_ndx:

        aName->ft->release(aName);
        if (bName) bName->ft->release(bName);

        if (!found)
            goto done;
    }

    result = true;

 done:

    a->ft->release(a);
    b->ft->release(b);

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
