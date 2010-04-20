//
// Copyright (C) 2009 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
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
