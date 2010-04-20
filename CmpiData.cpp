//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "CMPI/cmpidt.h"
#include "CMPI/cmpift.h"

#include "CmpiData.h"
#include "CmpiArray.h"
#include "CmpiStatus.h"
#include "CmpiInstance.h"
#include "CmpiDateTime.h"
#include "CmpiObjectPath.h"

#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace CmpiCpp;

const CMPIData CmpiData::nullData = {
    CMPI_null,
    CMPI_nullValue,
    { 0 }
};

// Copy the dynamically allocated parts of a CMPIData structure

static CMPIData clone(const CMPIData *v)
{
    CMPIData result = *v;

    // Simple types and null are copied by structure assignment

    if (result.type == CMPI_null || result.state == CMPI_nullValue)
        return result;

    if (result.type & (CMPI_SIMPLE | CMPI_REAL | CMPI_INTEGER) &&
        !(result.type & CMPI_ARRAY))
        return result;

    // Clone array value

    if (result.type & CMPI_ARRAY) {
        CMPIStatus status = { CMPI_RC_OK, NULL };

        result.value.array = v->value.array->ft->clone(v->value.array, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        return result;
    }

    // Clone string value

    if (result.type == CMPI_string) {
        CMPIStatus status = { CMPI_RC_OK, NULL };

        result.value.string = 
            v->value.string->ft->clone(v->value.string, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        return result;
    }

    // Clone chars value

    if (result.type == CMPI_chars) {
        result.value.chars = strdup(v->value.chars);
        return result;
    }

    // Clone reference value

    if (result.type == CMPI_ref) {
        CMPIStatus status = { CMPI_RC_OK, NULL };

        result.value.ref = v->value.ref->ft->clone(v->value.ref, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        return result;
    }

    // Clone instance value

    if (result.type == CMPI_instance) {
        CMPIStatus status = { CMPI_RC_OK, NULL };

        result.value.inst = v->value.inst->ft->clone(v->value.inst, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        return result;
    }

    // Clone datetime value

    if (result.type == CMPI_dateTime) {
        CMPIStatus status = { CMPI_RC_OK, NULL };

        result.value.dateTime = 
            v->value.dateTime->ft->clone(v->value.dateTime, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        return result;
    }

    // Unsupported/unimplemented type

    stringstream s;
    s << "Unsupported data type '" << CmpiData::typeToString(result.type) 
      << "' at " << __FILE__ << ":" << __LINE__;

    throw CmpiStatus(CMPI_RC_ERR_INVALID_DATA_TYPE, s.str());
}

// Free the dynamically allocated parts of a CMPIData structure

static void release(const CMPIData *v)
{ 
    // Null values don't need to be freed

    if (v->state == CMPI_nullValue || v->type == CMPI_null)
        return;

    // Free array value

    if (v->type & CMPI_ARRAY) {
        v->value.array->ft->release(v->value.array);
        return;
    }

    // Simple types don't need to be freed

    if (v->type & (CMPI_SIMPLE | CMPI_REAL | CMPI_INTEGER))
        return;

    // Free string value

    if (v->type == CMPI_string) {
        v->value.string->ft->release(v->value.string);
        return;
    }

    // Free char value

    if (v->type == CMPI_chars) {
        free(v->value.chars);
        return;
    }

    // Free reference value

    if (v->type == CMPI_ref) {
        v->value.ref->ft->release(v->value.ref);
        return;
    }

    // Free instance value

    if (v->type == CMPI_instance) {
        v->value.inst->ft->release(v->value.inst);
        return;
    }

    // Free datetime value

    if (v->type == CMPI_dateTime) {
        v->value.dateTime->ft->release(v->value.dateTime);
        return;
    }

    // Unsupported/unimplemented type

    stringstream s;
    s << "Unsupported data type '" << CmpiData::typeToString(v->type) 
      << "' at " << __FILE__ << ":" << __LINE__;

    throw CmpiStatus(CMPI_RC_ERR_INVALID_DATA_TYPE, s.str());
}

// Initialise null value

CmpiData::CmpiData() : _data(nullData)
{
}

// Initialise typed null value

CmpiData::CmpiData(CMPIType type) : _data(nullData)
{
    _data.type = type;
}

// Copy constructor

CmpiData::CmpiData(const CmpiData &v)
{
    _data = clone(&v._data);
}

// Construct from a CMPIData value

CmpiData::CmpiData(const CMPIData *v)
{
    _data = clone(v);
}

// Create path value

CmpiData::CmpiData(const CmpiObjectPath &v)
{
    CMPIObjectPath *ref = v.toCMPI();

    _data.type = CMPI_ref;
    _data.state = CMPI_goodValue;

    CMPIStatus status = { CMPI_RC_OK, NULL };
    _data.value.ref = ref->ft->clone(ref, &status);
    
    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiData::CmpiData(const CmpiInstance &v)
{
    CMPIInstance *inst = v.toCMPI();

    _data.type = CMPI_instance;
    _data.state = CMPI_goodValue;

    CMPIStatus status = { CMPI_RC_OK, NULL };
    _data.value.inst = inst->ft->clone(inst, &status);
    
    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiData::CmpiData(const CmpiArray &v)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    CMPIArray *array = v.toCMPI();

    _data.type = CMPI_ARRAY | array->ft->getSimpleType(array, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    _data.state = CMPI_goodValue;
    _data.value.array = array->ft->clone(array, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiData::CmpiData(const CmpiDateTime &v)
{
    CMPIDateTime *dt = v.toCMPI();

    _data.type = CMPI_dateTime;
    _data.state = CMPI_goodValue;

    CMPIStatus status = { CMPI_RC_OK, NULL };
    _data.value.dateTime = dt->ft->clone(dt, &status);
    
    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiData::~CmpiData()
{
    release(&_data);
}

CMPIType CmpiData::getType() const
{
    return _data.type & ~CMPI_ARRAY;
}

bool CmpiData::isNull() const
{
    return _data.state == CMPI_nullValue;
}

bool CmpiData::isArray() const
{
    return _data.type & CMPI_ARRAY;
}

CmpiData::operator CMPIUint8() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_uint8)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    return _data.value.uint8;
}

CmpiData::operator CMPISint8() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_sint8)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    return _data.value.sint8;
}

CmpiData::operator CMPIUint16() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_uint16)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    return _data.value.uint16;
}

CmpiData::operator CMPISint16() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_sint16)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    return _data.value.sint16;
}

CmpiData::operator CMPIUint32() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_uint32)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    return _data.value.uint32;
}

CmpiData::operator CMPISint32() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_sint32)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    return _data.value.sint32;
}

CmpiData::operator CMPIUint64() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_uint64)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    return _data.value.uint64;
}

CmpiData::operator CMPISint64() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_sint64)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    return _data.value.sint64;
}

CmpiData::operator CMPIReal32() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_real32)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    return _data.value.real32;
}

CmpiData::operator CMPIReal64() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_real64)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    return _data.value.real64;
}

CmpiData::operator bool() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_boolean)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    return _data.value.boolean;
}

CmpiData::operator string() const
{
    if (_data.type & CMPI_ARRAY || 
        (_data.type != CMPI_string && _data.type != CMPI_chars))
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    CMPIStatus status = { CMPI_RC_OK, NULL };
    
    string result;

    if (_data.type == CMPI_string) {

        result.assign(CMGetCharsPtr(_data.value.string, &status));

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

    } else
        result.assign(_data.value.chars);

    return result;
}

// For returning allocated objects (CmpiObjectPath, CmpiInstance,
// CmpiArray and CmpiDateTime) make sure we return a copy of the
// object and not a wrapper around a CMPIWhatever pointer.  The
// CMPIWhatever* constructor creates a wrapper, the CmpiWhatever&
// copy constructor creates a full copy.

CmpiData::operator CmpiObjectPath() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_ref)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    CmpiObjectPath tmp(_data.value.ref); // This is not a copy

    return CmpiObjectPath(tmp);          // This is a copy
}

CmpiData::operator CmpiInstance() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_instance)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    CmpiInstance tmp(_data.value.inst); // This is not a copy

    return CmpiInstance(tmp);           // This is a copy
}

CmpiData::operator CmpiArray() const
{
    if (!(_data.type & CMPI_ARRAY))
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    CmpiArray tmp(_data.value.array);  // This is not a copy

    return CmpiArray(tmp);             // This is a copy
}

CmpiData::operator CmpiDateTime() const
{
    if (_data.type & CMPI_ARRAY || _data.type != CMPI_dateTime)
        throw CmpiStatus(CMPI_RC_ERR_TYPE_MISMATCH);

    CmpiDateTime tmp(_data.value.dateTime); // This is not a copy

    return CmpiDateTime(tmp);              // This is a copy
}

bool CmpiData::operator==(const CmpiData &obj) const
{
    // Special case - CMPI_string and CMPI_chars that have the same
    // value are equal.

    if (_data.type == CMPI_chars && obj._data.type == CMPI_string) {
        CMPIStatus status = { CMPI_RC_OK, NULL };
        const char *tmp = CMGetCharsPtr(obj._data.value.string, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        return strcmp(_data.value.chars, tmp) == 0;
    }

    if (_data.type == CMPI_string && obj._data.type == CMPI_chars) {
        CMPIStatus status = { CMPI_RC_OK, NULL };
        const char *tmp = CMGetCharsPtr(_data.value.string, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        return strcmp(tmp, obj._data.value.chars) == 0;
    }

    // Type and state must be the same

    if (_data.type != obj._data.type)
        return false;

    if (_data.state != obj._data.state)
        return false;

    // Compare arrays

    if (_data.type & CMPI_ARRAY)
        return CMPIArrayCompare(_data.value.array, obj._data.value.array);

    // Compare non-array types

    switch (_data.type) {
    case CMPI_uint8:
        return _data.value.uint8 == obj._data.value.uint8;
    case CMPI_sint8:
        return _data.value.sint8 == obj._data.value.sint8;
    case CMPI_uint16:
        return _data.value.uint16 == obj._data.value.uint16;
    case CMPI_sint16:
        return _data.value.sint16 == obj._data.value.sint16;
    case CMPI_uint32:
        return _data.value.uint32 == obj._data.value.uint32;
    case CMPI_sint32:
        return _data.value.sint32 == obj._data.value.sint32;
    case CMPI_uint64:
        return _data.value.uint64 == obj._data.value.uint64;
    case CMPI_sint64:
        return _data.value.sint64 == obj._data.value.sint64;
    case CMPI_real32:
        return _data.value.real32 == obj._data.value.real32;
    case CMPI_real64:
        return _data.value.real64 == obj._data.value.real64;
    case CMPI_boolean:
        return _data.value.boolean == obj._data.value.boolean;
    case CMPI_string:
        return CMPIStringCompare(_data.value.string, obj._data.value.string);
    case CMPI_chars:
        return strcmp(_data.value.chars, obj._data.value.chars) == 0;
    case CMPI_ref:
        return CmpiObjectPath(_data.value.ref) == 
            CmpiObjectPath(obj._data.value.ref);
    case CMPI_instance:
        return CmpiInstance(_data.value.inst) == 
            CmpiInstance(obj._data.value.inst);
    case CMPI_dateTime:
        return CmpiDateTime(_data.value.dateTime) ==
            CmpiDateTime(obj._data.value.dateTime);
    case CMPI_null:
        return true;
    }

    // Unsupported/unimplemented type

    stringstream s;
    s << "Unsupported data type " << CmpiData::typeToString(_data.type) 
      << " at " << __FILE__ << ":" << __LINE__;

    throw CmpiStatus(CMPI_RC_ERR_INVALID_DATA_TYPE, s.str());    
}

bool CmpiData::operator!=(const CmpiData &obj) const
{
    return !(*this == obj);
}

CmpiData &CmpiData::operator=(const CmpiData &rhs)
{
    if (this == &rhs)
        return *this;

    release(&_data);
    _data = clone(&rhs._data);

    return *this;
}

string CmpiData::str() const
{
    stringstream s;

    if (_data.state != CMPI_goodValue)
        return "(null)";

    if (_data.type & CMPI_ARRAY) {
        CMPIArray *va = _data.value.array;
        CMPIStatus status = { CMPI_RC_OK, NULL };

        unsigned int len = va->ft->getSize(va, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        s << "[";

        for (unsigned int i = 0; i < len; i++) {
            CMPIData d = va->ft->getElementAt(va, i, &status);

            if (status.rc != CMPI_RC_OK)
                throw CmpiStatus(&status);

            s << CmpiData(&d);

            if (i < (len - 1))
                s << ", ";
        }

        s << "]";

        return s.str();
    }

    switch (_data.type) {
    case CMPI_uint8:
        s << (unsigned int)_data.value.uint8;
        break;
    case CMPI_sint8:
        s << (int)_data.value.sint8;
        break;
    case CMPI_uint16:
        s << _data.value.uint16;
        break;
    case CMPI_sint16:
        s << _data.value.sint16;
        break;
    case CMPI_uint32:
        s << _data.value.uint32;
        break;
    case CMPI_sint32:
        s << _data.value.sint32;
        break;
    case CMPI_uint64:
        s << _data.value.uint64;
        break;
    case CMPI_sint64:
        s << _data.value.sint64;
        break;
    case CMPI_real32:
        s << _data.value.real32;
        break;
    case CMPI_real64:
        s << _data.value.real64;
        break;
    case CMPI_boolean:
        s << (_data.value.boolean ? "TRUE" : "FALSE");
        break;
    case CMPI_string: {
        CMPIStatus status = { CMPI_RC_OK, NULL };

        s << CMGetCharsPtr(_data.value.string, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        break;
    }
    case CMPI_chars :
        s << _data.value.chars;
        break;
    case CMPI_ref: {
        CMPIStatus status = { CMPI_RC_OK, NULL };

        CMPIString *str =
            _data.value.ref->ft->toString(_data.value.ref, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        const char *chars = CMGetCharsPtr(str, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        s << chars;

        break;
    }
    case CMPI_dateTime: {
        CMPIStatus status = { CMPI_RC_OK, NULL };

        CMPIString *str = 
            _data.value.dateTime->ft->getStringFormat(_data.value.dateTime,
                                                      &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        const char *chars = CMGetCharsPtr(str, &status);

        if (status.rc != CMPI_RC_OK)
            throw CmpiStatus(&status);

        s << chars;

        break;        
    }
    default:
        s << "(unhandled type " << CmpiData::typeToString(_data.type) << ")";
        break;
    }
    
    return s.str();
}

ostream &CmpiCpp::operator<<(ostream &output, const CmpiData &data)
{
    output << data.str();
    return output;
}

CMPIData CmpiData::toCMPI() const
{
    return _data;
}

string CmpiData::typeToString(CMPIType type)
{
    stringstream s;

    switch (type & ~CMPI_ARRAY) {
    case CMPI_null:        s << "null";        break;
    case CMPI_boolean:     s << "boolean";     break;
    case CMPI_char16:      s << "char16";      break;
    case CMPI_real32:      s << "real32";      break;
    case CMPI_real64:      s << "real64";      break;
    case CMPI_uint8:       s << "uint8";       break;
    case CMPI_sint8:       s << "sint8";       break;
    case CMPI_uint16:      s << "uint16";      break;
    case CMPI_sint16:      s << "sint16";      break;
    case CMPI_uint32:      s << "uint32";      break;
    case CMPI_sint32:      s << "sint32";      break;
    case CMPI_uint64:      s << "uint64";      break;
    case CMPI_sint64:      s << "sint64";      break;
    case CMPI_instance:    s << "instance";    break;
    case CMPI_ref:         s << "ref";         break;
    case CMPI_args:        s << "args";        break;
    case CMPI_class:       s << "class";       break;
    case CMPI_filter:      s << "filter";      break;
    case CMPI_enumeration: s << "enumeration"; break;
    case CMPI_string:      s << "string";      break;
    case CMPI_chars:       s << "chars";       break;
    case CMPI_dateTime:    s << "datetime";    break;
    case CMPI_ptr:         s << "ptr";         break;
    case CMPI_charsptr:    s << "charsptr";    break;
    default:
        s << "unknown type [" << (int)type << "]";
        break;
    }

    if (type & CMPI_ARRAY)
        s << " array";

    return s.str();
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
