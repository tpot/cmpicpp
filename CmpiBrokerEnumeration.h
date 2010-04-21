//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiBrokerEnumeration_h
#define _CmpiBrokerEnumeration_h

#include "cmpidt.h"
#include "cmpift.h"

namespace CmpiCpp {

    namespace Broker {

        class CmpiEnumeration {

        public:

            CmpiEnumeration();
            virtual ~CmpiEnumeration();

            CMPIEnumeration *toCMPI();

            virtual CMPIStatus release() = 0;

            virtual CMPIEnumeration *clone(CMPIStatus *rc) = 0;

            virtual CMPIData getNext(CMPIStatus *rc) = 0;

            virtual CMPIBoolean hasNext(CMPIStatus *rc) = 0;

            virtual CMPIArray *toArray(CMPIStatus *rc) = 0;

        private:

            // Prevent copying

            CmpiEnumeration(const CmpiEnumeration &);
            CmpiEnumeration &operator=(const CmpiEnumeration &);

            // CMPI function table and driver functions

            CMPIEnumeration _enumeration;
            CMPIEnumerationFT _enumerationFT;

            static CMPIStatus _driveRelease(CMPIEnumeration *en);

            static CMPIEnumeration *_driveClone(const CMPIEnumeration *en, 
                                                CMPIStatus *rc);

            static CMPIData _driveGetNext(const CMPIEnumeration *en,
                                          CMPIStatus *rc);

            static CMPIBoolean _driveHasNext(const CMPIEnumeration *en,
                                             CMPIStatus *rc);

            static CMPIArray *_driveToArray(const CMPIEnumeration *en,
                                            CMPIStatus *rc);
        };

    } // namespace Broker

} // namespace CmpiCpp

#endif // _CmpiBrokerEnumeration_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
