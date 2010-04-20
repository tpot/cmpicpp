//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiProvider_h
#define _CmpiProvider_h

#include <string>
#include <pthread.h>
#include "platform.h"

#include "CMPI/cmpidt.h"

namespace CmpiCpp {

    using namespace std;

    class CmpiName;
    class CmpiArray;
    class CmpiContext;
    class CmpiInstance;
    class CmpiObjectPath;
    class CmpiDateTime;

    class CmpiProvider {

    public:

        // Constructors

        CmpiProvider();
        virtual ~CmpiProvider();

        // Handle provider unload requests

        enum unloadBehaviour {
            okToUnload,         // CMPI_RC_OK, default
            doNotUnload,        // CMPI_RC_DO_NOT_UNLOAD
            neverUnload,        // CMPI_RC_NEVER_UNLOAD
        };

        virtual enum unloadBehaviour unloadOK(const CmpiContext &context) = 0;
        virtual void cleanup(const CmpiContext &context, bool terminating) = 0;

        // Reference counting

        int incRefcount();
        int decRefcount();
        int getRefcount() const;

        virtual const CMPIBroker *getBroker() = 0;

        const char *getName() const;
        void setName(const char *name);

    protected:

        const char *_name;

    private:

        int _refcount;
        pthread_mutex_t _refcount_lock;
    };    

} // namespace CmpiCpp

#endif // _CmpiProvider_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
