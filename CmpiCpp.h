//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
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
