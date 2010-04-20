//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "cmpift.h"

#include "CmpiData.h"
#include "CmpiArray.h"
#include "CmpiStatus.h"
#include "CmpiObjectPath.h"

#include <sstream>

using namespace CmpiCpp;

CmpiArray::CmpiArray(CMPIArray *va)
{
    _data = va;
    _wasCloned = false;
    _isCopy = false;
}

CmpiArray::CmpiArray(const CmpiArray &va)
{
    _data = va._data;
    _wasCloned = false;
    _isCopy = true;

    // We can't keep a copy of something that has been cloned already
    // as it may be released at any time.

    if (va._wasCloned)
        _clone();
}

CmpiArray::~CmpiArray()
{
    // Don't check return value and throw an exception - it's a pretty
    // bad idea.

    if (_wasCloned)
        _data->ft->release(_data);
}

void CmpiArray::_clone()
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    _data = _data->ft->clone(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
    
    _isCopy = false;
    _wasCloned = true;
}

CMPICount CmpiArray::getSize() const
{ 
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPICount result = _data->ft->getSize(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);    

    return result;
}

CMPIType CmpiArray::getSimpleType() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIType result = _data->ft->getSimpleType(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);    

    return result;
}

CmpiData CmpiArray::getElementAt(CMPICount ndx) const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIData result = _data->ft->getElementAt(_data, ndx, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);    

    return CmpiData(&result);
}

string CmpiArray::str() const
{
    stringstream s;

    s << "[";

    CMPICount len = getSize();

    for (unsigned int i = 0; i < len; i++) {
        CMPIStatus status = { CMPI_RC_OK, NULL };
        CMPIData d = _data->ft->getElementAt(_data, i, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        s << CmpiData(&d);

        if (i < (len - 1))
            s << ", ";
    }

    s << "]";

    return s.str();

}

void CmpiArray::setElementAt(CMPICount ndx, const CMPIData *d)
{
    if (_isCopy)
        _clone();

    CMPIStatus status = _data->ft->setElementAt(_data, ndx, &d->value, d->type);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

void CmpiArray::setElementAt(CMPICount ndx, const CmpiData &value)
{
    CMPIData d = value.toCMPI();

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, CMPIUint8 value)
{
    CMPIData d;
    
    d.type = CMPI_uint8;
    d.state = CMPI_goodValue;
    d.value.uint8 = value;

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, CMPISint8 value)
{
    CMPIData d;
    
    d.type = CMPI_sint8;
    d.state = CMPI_goodValue;
    d.value.sint8 = value;

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, CMPIUint16 value)
{
    CMPIData d;
    
    d.type = CMPI_uint16;
    d.state = CMPI_goodValue;
    d.value.uint16 = value;

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, CMPISint16 value)
{
    CMPIData d;
    
    d.type = CMPI_sint16;
    d.state = CMPI_goodValue;
    d.value.sint16 = value;

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, CMPIUint32 value)
{
    CMPIData d;
    
    d.type = CMPI_uint32;
    d.state = CMPI_goodValue;
    d.value.uint32 = value;

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, CMPISint32 value)
{
    CMPIData d;
    
    d.type = CMPI_sint32;
    d.state = CMPI_goodValue;
    d.value.sint32 = value;

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, CMPIUint64 value)
{
    CMPIData d;
    
    d.type = CMPI_uint64;
    d.state = CMPI_goodValue;
    d.value.uint64 = value;

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, CMPISint64 value)
{
    CMPIData d;
    
    d.type = CMPI_sint64;
    d.state = CMPI_goodValue;
    d.value.sint64 = value;

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, CMPIReal32 value)
{
    CMPIData d;
    
    d.type = CMPI_real32;
    d.state = CMPI_goodValue;
    d.value.real32 = value;

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, CMPIReal64 value)
{
    CMPIData d;
    
    d.type = CMPI_real64;
    d.state = CMPI_goodValue;
    d.value.real64 = value;

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, bool value)
{
    CMPIData d;

    d.type = CMPI_boolean;
    d.state = CMPI_goodValue;
    d.value.boolean = value;

    setElementAt(ndx, &d);
}

void CmpiArray::setElementAt(CMPICount ndx, const char *value)
{
    if (_isCopy)
        _clone();    

    CMPIStatus status = _data->ft->setElementAt
        (_data, ndx, 
         reinterpret_cast<const CMPIValue *>(value),
         CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);    
}

void CmpiArray::setElementAt(CMPICount ndx, const string &value)
{
    if (_isCopy)
        _clone();

    CMPIStatus status = _data->ft->setElementAt
        (_data, ndx, 
         reinterpret_cast<const CMPIValue *>(value.c_str()),
         CMPI_chars);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);    
}

void CmpiArray::setElementAt(CMPICount ndx, const CmpiObjectPath &value)
{
    CMPIData d;
    CMPIObjectPath *path = value.toCMPI();

    d.type = CMPI_ref;
    d.state = CMPI_goodValue;

    CMPIStatus status = { CMPI_RC_OK, NULL };

    d.value.ref = path->ft->clone(path, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    setElementAt(ndx, &d);
}

bool CmpiArray::operator==(const CmpiArray &obj) const
{
    return CMPIArrayCompare(_data, obj._data);
}

bool CmpiArray::operator!=(const CmpiArray &obj) const
{
    return !(*this == obj);
}

CmpiArray &CmpiArray::operator=(const CmpiArray &rhs)
{
    if (this == &rhs)
        return *this;

    CMPIStatus status;

    if (_wasCloned) {

        status = _data->ft->release(_data);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);
    }

    status.rc = CMPI_RC_OK;
    status.msg = NULL;

    _data = rhs._data->ft->clone(rhs._data, &status);
    _wasCloned = true;

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return *this;
}

CMPIArray *CmpiArray::toCMPI() const
{
    return _data;
}

ostream &CmpiCpp::operator<<(ostream &output, const CmpiArray &obj)
{
    output << obj.str();
    return output;
}

CmpiArray CmpiCpp::makeCmpiArray(const CMPIBroker *broker, int maxSize, 
                                 CMPIType type)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    if (type == CMPI_string)
        type = CMPI_chars;

    CMPIArray *array = broker->eft->newArray(broker, maxSize, type, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);    

    CmpiArray result(array);

    return result;
}


bool CmpiCpp::CMPIArrayCompare(const CMPIArray *a, const CMPIArray *b)
{
    if (a->ft->getSimpleType(a, NULL) !=
        b->ft->getSimpleType(b, NULL))
        return false;

    if (a->ft->getSize(a, NULL) != 
        b->ft->getSize(b, NULL))
        return false;

    for (CMPICount i = 0; i < a->ft->getSize(a, NULL); i++) {
        CMPIData elt1 = a->ft->getElementAt(a, i, NULL);
        CMPIData elt2 = b->ft->getElementAt(b, i, NULL);

        if (CmpiData(&elt1) != CmpiData(&elt2))
            return false;
    }

    return true;
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
