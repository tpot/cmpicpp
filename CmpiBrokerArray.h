//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiBrokerArray_h
#define _CmpiBrokerArray_h

#include "cmpidt.h"
#include "cmpift.h"

namespace CmpiCpp {

    namespace Broker {

        class CmpiArray {    

        public:

            CmpiArray();
            virtual ~CmpiArray();

            CMPIArray *toCMPI();

            virtual CMPIStatus release() = 0;

            virtual CMPIArray *clone(CMPIStatus *rc) = 0;

            virtual CMPICount getSize(CMPIStatus *rc) = 0;

            virtual CMPIType getSimpleType(CMPIStatus *rc) = 0;

            virtual CMPIData getElementAt(CMPICount index, CMPIStatus *rc) = 0;

            virtual CMPIStatus setElementAt(CMPICount index, 
                                            const CMPIValue *value, 
                                            CMPIType type) = 0;

        private:

            // Prevent copying

            CmpiArray(const CmpiArray &);
            CmpiArray &operator=(const CmpiArray &);


            // CMPI fuction table and driver fucntions
        
            CMPIArray _array;
            CMPIArrayFT _arrayFT;

            static CMPIStatus _driveRelease(CMPIArray *ar);

            static CMPIArray *_driveClone(const CMPIArray *ar, CMPIStatus *rc);

            static CMPICount _driveGetSize(const CMPIArray *ar, CMPIStatus *rc);

            static CMPIType _driveGetSimpleType(const CMPIArray *ar, 
                                                CMPIStatus *rc);

            static CMPIData _driveGetElementAt(const CMPIArray *ar, 
                                               CMPICount index,
                                               CMPIStatus *rc);

            static CMPIStatus _driveSetElementAt(CMPIArray *ar, CMPICount index,
                                                 const CMPIValue *value, 
                                                 CMPIType type);
        };

    } // namespace Broker

} // namespace CmpiCpp

#endif // _CmpiBrokerArray_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
