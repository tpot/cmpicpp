//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "cmpidt.h"
#include "cmpift.h"

#include "CmpiData.h"
#include "CmpiArray.h"
#include "CmpiStatus.h"
#include "CmpiInstance.h"
#include "CmpiObjectPath.h"
#include "CmpiEnumeration.h"

using namespace std;
using namespace CmpiCpp;

//
// Implementation of CmpiEnumeration class
//

CmpiEnumeration::CmpiEnumeration(const CMPIEnumeration *args)
    : _wasCloned(false), _data(const_cast<CMPIEnumeration *>(args))
{
}

CmpiEnumeration::CmpiEnumeration(const CmpiEnumeration &args)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    _data = args._data->ft->clone(args._data, &status);
    _wasCloned = true;

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiEnumeration::~CmpiEnumeration()
{
    if (_wasCloned)
        _data->ft->release(_data);
}

CmpiData 
CmpiEnumeration::getNext() const
{
    if (!_data)
        throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND);

    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIData result = _data->ft->getNext(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return CmpiData(&result);
}

bool 
CmpiEnumeration::hasNext() const
{
    if (!_data)
        return false;

    CMPIStatus status = { CMPI_RC_OK, NULL };

    bool result = _data->ft->hasNext(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return result;
}
    
CmpiArray 
CmpiEnumeration::toArray() const
{
    if (!_data)
        throw CmpiStatus(CMPI_RC_ERR_NOT_FOUND);        

    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIArray *result = _data->ft->toArray(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return CmpiArray(result);
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
