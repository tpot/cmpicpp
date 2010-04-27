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
