//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiBrokerContext_h
#define _CmpiBrokerContext_h

#include "CMPI/cmpidt.h"
#include "CMPI/cmpift.h"

namespace CmpiCpp {

    namespace Broker {

        class CmpiContext {

        public:

            CmpiContext();
            virtual ~CmpiContext();
            
            CMPIContext *toCMPI();

            virtual CMPIStatus release() = 0;
            
            virtual CMPIContext *clone(CMPIStatus *rc) = 0;

            virtual CMPIData getEntry(const char *name, CMPIStatus *rc) = 0;

            virtual CMPIData getEntryAt(unsigned int index, CMPIString **name,
                                        CMPIStatus *rc) = 0;

            virtual unsigned int getEntryCount(CMPIStatus *rc) = 0;

            virtual CMPIStatus addEntry(const char *name, 
                                        const CMPIValue *value,
                                        CMPIType type) = 0;

        private:

            // Prevent copying
            
            CmpiContext(CmpiContext &);
            CmpiContext &operator=(CmpiContext &);

            // CMPI function table and driver functions

            CMPIContext _context;
            CMPIContextFT _contextFT;

            static CMPIStatus _driveRelease(CMPIContext *rslt);

            static CMPIContext *_driveClone(const CMPIContext *rslt, 
                                            CMPIStatus *rc);

            static CMPIData _driveGetEntry(const CMPIContext *ctx, 
                                           const char *name, CMPIStatus *rc);

            static CMPIData _driveGetEntryAt(const CMPIContext *ctx, 
                                             unsigned int index, 
                                             CMPIString **name,
                                             CMPIStatus *rc);

            static unsigned int _driveGetEntryCount(const CMPIContext *ctx, 
                                                     CMPIStatus *rc);

            static CMPIStatus _driveAddEntry(const CMPIContext *ctx, 
                                             const char *name, 
                                             const CMPIValue* value, 
                                             CMPIType type);
        };

    } // namespace Broker

} // namespace CmpiCpp

#endif // _CmpiBrokerContext_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
