//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiBrokerDateTime_h
#define _CmpiBrokerDateTime_h

#include "cmpidt.h"
#include "cmpift.h"

namespace CmpiCpp {

    namespace Broker {

        class CmpiDateTime {    

        public:

            CmpiDateTime();
            virtual ~CmpiDateTime();

            CMPIDateTime *toCMPI();

            virtual CMPIStatus release() = 0;

            virtual CMPIDateTime *clone(CMPIStatus *rc) = 0;

            virtual CMPIUint64 getBinaryFormat(CMPIStatus *rc) = 0;
            
            virtual CMPIString *getStringFormat(CMPIStatus *rc) = 0;

            virtual CMPIBoolean isInterval(CMPIStatus *rc) = 0;

        private:

            // Prevent copying

            CmpiDateTime(const CmpiDateTime &);
            CmpiDateTime &operator=(const CmpiDateTime &);


            // CMPI fuction table and driver fucntions
        
            CMPIDateTime _datetime;
            CMPIDateTimeFT _datetimeFT;

            static CMPIStatus _driveRelease(CMPIDateTime *dt);

            static CMPIDateTime *_driveClone(const CMPIDateTime *dt, 
					     CMPIStatus *rc);

            static CMPIUint64 _driveGetBinaryFormat(const CMPIDateTime *dt,
                                                CMPIStatus *rc);
            
            static CMPIString *_driveGetStringFormat(const CMPIDateTime *dt,
                                                     CMPIStatus *rc);

            static CMPIBoolean _driveIsInterval(const CMPIDateTime *dt,
                                                CMPIStatus *rc);
        };

    } // namespace Broker

} // namespace CmpiCpp

#endif // _CmpiBrokerDateTime_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
