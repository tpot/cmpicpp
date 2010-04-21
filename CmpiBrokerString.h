//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiBrokerString_h
#define _CmpiBrokerString_h

#include "cmpidt.h"
#include "cmpift.h"

namespace CmpiCpp {

    namespace Broker {

        class CmpiString {

        public:

            CmpiString();
            virtual ~CmpiString();

            CMPIString *toCMPI();

            virtual CMPIStatus release() = 0;

            virtual CMPIString *clone(CMPIStatus *rc) = 0;

            virtual char *getCharPtr(CMPIStatus *rc) = 0;

        private:

            // Prevent copying

            CmpiString(const CmpiString &);
            CmpiString &operator=(const CmpiString &);

            // CMPI function table and driver functions

            CMPIString _string;
            CMPIStringFT _stringFT;

            static CMPIStatus _driveRelease(CMPIString* st);

            static CMPIString* _driveClone(const CMPIString* st, 
                                           CMPIStatus* rc);

            static const char *_driveGetCharPtr(const CMPIString* st, CMPIStatus* rc);
        };

    } // namespace Broker

} // namespace CmpiCpp

#endif // _CmpiBrokerString_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
