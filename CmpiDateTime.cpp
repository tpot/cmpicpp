//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "CmpiStatus.h"
#include "CmpiDateTime.h"

using namespace std;
using namespace CmpiCpp;

CmpiDateTime::CmpiDateTime(const CMPIDateTime *dt)
{
    _data = const_cast<CMPIDateTime *>(dt);
    _wasCloned = false;
}

CmpiDateTime::CmpiDateTime(const CmpiDateTime &va)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    _data = va._data->ft->clone(va._data, &status);
    _wasCloned = true;

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
}

CmpiDateTime::~CmpiDateTime()
{
    // Don't check return value and throw an exception - it's a pretty
    // bad idea.

    if (_wasCloned)
        _data->ft->release(_data);
}

bool 
CmpiDateTime::isInterval() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    bool result = _data->ft->isInterval(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return result;
}

uint64_t 
CmpiDateTime::getBinaryFormat() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    uint64_t result = _data->ft->getBinaryFormat(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return result;
}

time_t
CmpiDateTime::getTimeT() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    uint64_t u = _data->ft->getBinaryFormat(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return (time_t)(u / cmpiBinFormatMsecs);
}

string
CmpiDateTime::str() const
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    CMPIString *s = _data->ft->getStringFormat(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);
    
    string result(CMGetCharsPtr(s, &status));

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    return result;    
}

CMPIDateTime *
CmpiDateTime::toCMPI() const
{
    return _data;
}

CmpiDateTime &
CmpiDateTime::operator=(const CmpiDateTime &rhs)
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

bool CmpiDateTime::operator==(const CmpiDateTime &obj) const
{
    return isInterval() == obj.isInterval() &&
        getBinaryFormat() == obj.getBinaryFormat();
}

bool CmpiDateTime::operator!=(const CmpiDateTime &obj) const
{
    return !(*this == obj);
}

CmpiDateTime 
CmpiCpp::makeCmpiDateTime(const CMPIBroker *broker)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIDateTime *dt = broker->eft->newDateTime(broker, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiDateTime result(dt);

    return result;
}

CmpiDateTime 
CmpiCpp::makeCmpiDateTime(const CMPIBroker *broker, uint64_t binTime,
                          bool isInterval)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIDateTime *dt = 
        broker->eft->newDateTimeFromBinary(broker, binTime, isInterval, 
                                           &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiDateTime result(dt);

    return result;
}

CmpiDateTime 
CmpiCpp::makeCmpiDateTime(const CMPIBroker *broker, const string &utcTime)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIDateTime *dt = 
        broker->eft->newDateTimeFromChars(broker, utcTime.c_str(), &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiDateTime result(dt);

    return result;
}

CmpiDateTime
CmpiCpp::makeCmpiDateTime(const CMPIBroker *broker, time_t t)
{
    return makeCmpiDateTime(broker, (uint64_t)t * cmpiBinFormatMsecs, false);
}

CmpiDateTime 
CmpiCpp::makeCurrentDateTime(const CMPIBroker *broker)
{
    time_t now = time(NULL);

    return makeCmpiDateTime(broker, (uint64_t)now * cmpiBinFormatMsecs, false);
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