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

#include "CmpiCpp.h"
#include "CmpiCppClient.h"

using namespace std;
using namespace CmpiCpp;

CmpiCppClient::CmpiCppClient(const CMPIBroker *, // broker
                             const string &)     // socketPath
{
}

CmpiCppClient::CmpiCppClient(const CMPIBroker *, // broker
                             const string &,     // url
                             const string &,     // user
                             const string &)     // pass
{
}

CmpiCppClient::~CmpiCppClient()
{
}

CmpiEnumeration 
CmpiCppClient::enumInstances(const CmpiContext &, // context
                             const CmpiObjectPath &, // path
                             const char **)          // properties
{
    throw CmpiStatus(CMPI_RC_ERR_FAILED, "Not implemented");
}

CmpiInstance 
CmpiCppClient::getInstance(const CmpiContext &, // context
                           const CmpiObjectPath &, // path
                           const char **)          // properties
{
    throw CmpiStatus(CMPI_RC_ERR_FAILED, "Not implemented");
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
