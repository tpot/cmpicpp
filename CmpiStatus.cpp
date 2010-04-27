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

#include <sstream>

#include "cmpimacs.h"
#include "CmpiStatus.h"

using namespace std;
using namespace CmpiCpp;

CmpiStatus::CmpiStatus()
    : _rc(CMPI_RC_OK)
{
}

CmpiStatus::CmpiStatus(const CMPIrc rc)
    : _rc(rc)
{
}

CmpiStatus::CmpiStatus(const CMPIrc rc, const string &msg)
    : _rc(rc), _msg(msg)
{
}

CmpiStatus::CmpiStatus(const CMPIStatus *status)
    : _rc(status->rc)
    
{
    if (status->msg)
        _msg.assign(CMGetCharsPtr(status->msg, NULL));
}

CmpiStatus::CmpiStatus(const CmpiStatus &status)
    : _rc(status.getRC()), _msg(status.getMsg())
{
}

CmpiStatus::~CmpiStatus()
{
}

CMPIrc CmpiStatus::getRC() const
{
    return _rc;
}

string CmpiStatus::getMsg() const
{
    return _msg;
}

CMPIStatus CmpiStatus::toCMPI(const CMPIBroker *broker) const
{
    CMPIStatus result;

    result.rc = _rc;
    result.msg = CMNewString(broker, _msg.c_str(), NULL);

    return result;
}

string CmpiStatus::str() const
{
    stringstream s;

    s << rcToString(_rc);

    if (!_msg.empty())
        s << ": " << _msg;

    return s.str();
}

bool CmpiStatus::operator==(const CmpiStatus &status) const
{
    return (status.getRC() == this->getRC() &&
            status.getMsg() == this->getMsg());
}

bool CmpiStatus::operator!=(const CmpiStatus &status) const
{
    return !(*this == status);
}

bool CmpiStatus::operator<(const CmpiStatus &status) const
{
    if (this->_rc < status._rc)
        return true;

    if (this->_msg < status._msg)
        return true;

    return false;
}

CmpiStatus &CmpiStatus::operator=(const CmpiStatus &rhs)
{
    if (this == &rhs) 
        return *this;

    this->_rc = rhs.getRC();
    this->_msg = rhs.getMsg();

    return *this;
}

string CmpiStatus::rcToString(CMPIrc rc)
{
    switch (rc) {
    case CMPI_RC_OK:
        return "CMPI_RC_OK";
    case CMPI_RC_ERR_FAILED:
        return "CMPI_RC_ERR_FAILED";
    case CMPI_RC_ERR_ACCESS_DENIED:
        return "CMPI_RC_ERR_ACCESS_DENIED";
    case CMPI_RC_ERR_INVALID_NAMESPACE:
        return "CMPI_RC_ERR_INVALID_NAMESPACE";
    case CMPI_RC_ERR_INVALID_PARAMETER:
        return "CMPI_RC_ERR_INVALID_PARAMETER";
    case CMPI_RC_ERR_INVALID_CLASS:
        return "CMPI_RC_ERR_INVALID_CLASS";
    case CMPI_RC_ERR_NOT_FOUND:
        return "CMPI_RC_ERR_NOT_FOUND";
    case CMPI_RC_ERR_NOT_SUPPORTED:
        return "CMPI_RC_ERR_NOT_SUPPORTED";
    case CMPI_RC_ERR_CLASS_HAS_CHILDREN:
        return "CMPI_RC_ERR_CLASS_HAS_CHILDREN";
    case CMPI_RC_ERR_CLASS_HAS_INSTANCES:
        return "CMPI_RC_ERR_CLASS_HAS_INSTANCES";
    case CMPI_RC_ERR_INVALID_SUPERCLASS:
        return "CMPI_RC_ERR_INVALID_SUPERCLASS";
    case CMPI_RC_ERR_ALREADY_EXISTS:
        return "CMPI_RC_ERR_ALREADY_EXISTS";
    case CMPI_RC_ERR_NO_SUCH_PROPERTY:
        return "CMPI_RC_ERR_NO_SUCH_PROPERTY";
    case CMPI_RC_ERR_TYPE_MISMATCH:
        return "CMPI_RC_ERR_TYPE_MISMATCH";
    case CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED:
        return "CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED";
    case CMPI_RC_ERR_INVALID_QUERY:
        return "CMPI_RC_ERR_INVALID_QUERY";
    case CMPI_RC_ERR_METHOD_NOT_AVAILABLE:
        return "CMPI_RC_ERR_METHOD_NOT_AVAILABLE";
    case CMPI_RC_ERR_METHOD_NOT_FOUND:
        return "CMPI_RC_ERR_METHOD_NOT_FOUND";
    case CMPI_RC_DO_NOT_UNLOAD:
        return "CMPI_RC_DO_NOT_UNLOAD";
    case CMPI_RC_NEVER_UNLOAD:
        return "CMPI_RC_NEVER_UNLOAD";
    case CMPI_RC_ERR_INVALID_HANDLE:
        return "CMPI_RC_ERR_INVALID_HANDLE";
    case CMPI_RC_ERR_INVALID_DATA_TYPE:
        return "CMPI_RC_ERR_INVALID_DATA_TYPE";
    case CMPI_RC_ERROR_SYSTEM:
        return "CMPI_RC_ERROR_SYSTEM";
    case CMPI_RC_ERROR:
        return "CMPI_RC_ERROR";
    }

    stringstream s;
    s << "Unknown CMPI error " << (int)rc;

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
