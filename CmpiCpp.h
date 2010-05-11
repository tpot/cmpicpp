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

#ifndef _CmpiCpp_h
#define _CmpiCpp_h

// Include CMPI C interface

extern "C" {
#include "cmpidt.h"
#include "cmpift.h"
}

// Basic data types

#include "CmpiStatus.h"
#include "CmpiName.h"
#include "CmpiArray.h"
#include "CmpiData.h"
#include "CmpiObjectPath.h"
#include "CmpiInstance.h"
#include "CmpiResult.h"
#include "CmpiContext.h"
#include "CmpiArgs.h"
#include "CmpiEnumeration.h"
#include "CmpiDateTime.h"
#include "CmpiBroker.h"

// Provider types

#include "CmpiInstanceProvider.h"
#include "CmpiAssociationProvider.h"
#include "CmpiMethodProvider.h"
#include "CmpiIndicationProvider.h"

#endif // _CmpiCpp_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
