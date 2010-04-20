//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "cmpift.h"

#include "CmpiStatus.h"
#include "CmpiContext.h"

using namespace CmpiCpp;

// Note that both the Pegasus and SFCB implementations of CMPIContext
// don't implement the clone() operation but rather return a no-op or
// CMPI_RC_ERR_NOT_SUPPORTED.  In this case just copying the
// CMPIContext pointer around will work but may give us trouble with a
// CIMOM that does not work this way.

CmpiContext::CmpiContext(const CMPIContext *context)
    : _data(context)
{
}

CmpiContext::~CmpiContext()
{
}

const CMPIContext *
CmpiContext::toCMPI() const
{
    return _data;
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
