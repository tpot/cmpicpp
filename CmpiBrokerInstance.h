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

#ifndef _CmpiBrokerInstance_h
#define _CmpiBrokerInstance_h

#include <string>

#include "cmpidt.h"
#include "cmpift.h"

#include "CmpiBrokerObjectPath.h"

namespace CmpiCpp {

    namespace Broker {

        using namespace std;

        class CmpiInstance {

        public:

            CmpiInstance();
            virtual ~CmpiInstance();

            CMPIInstance *toCMPI();

            virtual CMPIStatus release() = 0;

            virtual CMPIInstance *clone(CMPIStatus *rc) = 0;

            virtual CMPIData getProperty(const char *name, CMPIStatus *rc) = 0;

            virtual CMPIData getPropertyAt(unsigned int index, 
                                           CMPIString **name,
                                           CMPIStatus *rc) = 0;

            virtual unsigned int getPropertyCount(CMPIStatus *rc) = 0;

            virtual CMPIStatus setProperty(const char *name, 
                                           const CMPIValue *value, 
                                           CMPIType type) = 0;

            virtual CMPIObjectPath *getObjectPath(CMPIStatus *rc) = 0;

            virtual CMPIStatus setObjectPath(const CMPIObjectPath *op) = 0;

        private:

            // Prevent copying

            CmpiInstance(const CmpiInstance &);
            CmpiInstance &operator=(const CmpiInstance &);

            // CMPI function table and driver functions

            CMPIInstance _instance;
            CMPIInstanceFT _instanceFT;

            static CMPIStatus _driveRelease(CMPIInstance *inst);

            static CMPIInstance* _driveClone(const CMPIInstance *inst, 
                                             CMPIStatus *rc);

            static CMPIData _driveGetProperty(const CMPIInstance *inst, 
                                              const char *name,
                                              CMPIStatus *rc);

            static CMPIData _driveGetPropertyAt(const CMPIInstance *inst, 
                                                unsigned int index, 
                                                CMPIString **name,
                                                CMPIStatus *rc);

            static unsigned int _driveGetPropertyCount
            (const CMPIInstance *inst, CMPIStatus *rc);

            static CMPIStatus _driveSetProperty(const CMPIInstance *inst, 
                                                const char *name,
                                                const CMPIValue* value, 
                                                CMPIType type);

            static CMPIObjectPath *_driveGetObjectPath
            (const CMPIInstance *inst, CMPIStatus *rc);

            static CMPIStatus _driveSetPropertyFilter
            (CMPIInstance *inst, const char **propertyList, const char **keys);

            static CMPIStatus _driveSetObjectPath(CMPIInstance *inst, 
                                                  const CMPIObjectPath *op);
        };

    } // namespace Broker

} // namespace CmpiCpp

#endif // _CmpiBrokerInstance_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
