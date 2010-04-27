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

#include "CmpiBrokerContext.h"
#include "CmpiStatus.h"

using namespace CmpiCpp;

Broker::CmpiContext::CmpiContext()
{
    _context.hdl = (void *)this;

    _contextFT.ftVersion = CMPICurrentVersion;

    _contextFT.release = _driveRelease;
    _contextFT.clone = _driveClone;
    _contextFT.getEntry = _driveGetEntry;
    _contextFT.getEntryAt = _driveGetEntryAt;
    _contextFT.getEntryCount = _driveGetEntryCount;
    _contextFT.addEntry = _driveAddEntry;

    _context.ft = &_contextFT;
}

Broker::CmpiContext::~CmpiContext()
{
}

CMPIContext *
Broker::CmpiContext::toCMPI()
{
    return &_context;
}

CMPIStatus 
Broker::CmpiContext::_driveRelease(CMPIContext *ctx)
{
    Broker::CmpiContext *obj = 
        reinterpret_cast<Broker::CmpiContext *>(ctx->hdl);

    return obj->release();
}

CMPIContext *
Broker::CmpiContext::_driveClone(const CMPIContext *ctx, CMPIStatus *rc)
{
    Broker::CmpiContext *obj = 
        reinterpret_cast<Broker::CmpiContext *>(ctx->hdl);

    return obj->clone(rc);
}

CMPIData 
Broker::CmpiContext::_driveGetEntry(const CMPIContext *ctx, 
                                    const char *name, CMPIStatus *rc)
{
    Broker::CmpiContext *obj = 
        reinterpret_cast<Broker::CmpiContext *>(ctx->hdl);

    return obj->getEntry(name, rc);
}

CMPIData 
Broker::CmpiContext::_driveGetEntryAt(const CMPIContext *ctx, 
                                      unsigned int index, CMPIString **name,
                                      CMPIStatus *rc)
{
    Broker::CmpiContext *obj = 
        reinterpret_cast<Broker::CmpiContext *>(ctx->hdl);

    return obj->getEntryAt(index, name, rc);
}

unsigned int 
Broker::CmpiContext::_driveGetEntryCount(const CMPIContext *ctx, 
                                         CMPIStatus *rc)
{
    Broker::CmpiContext *obj = 
        reinterpret_cast<Broker::CmpiContext *>(ctx->hdl);

    return obj->getEntryCount(rc);
}

CMPIStatus 
Broker::CmpiContext::_driveAddEntry(const CMPIContext *ctx, 
                                    const char *name, const CMPIValue* value, 
                                    CMPIType type)
{
    Broker::CmpiContext *obj = 
        reinterpret_cast<Broker::CmpiContext *>(ctx->hdl);

    return obj->addEntry(name, value, type);
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
