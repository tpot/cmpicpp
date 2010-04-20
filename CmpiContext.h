//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiContext_h
#define _CmpiContext_h

#include "CMPI/cmpidt.h"

namespace CmpiCpp {

    class CmpiContext {

    public:

        CmpiContext(const CMPIContext *context);
        virtual ~CmpiContext();

        const CMPIContext *toCMPI() const;

    private:

        const CMPIContext *_data;
    };

} // namespace CmpiCpp

#endif // _CmpiContext_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
