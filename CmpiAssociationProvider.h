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

#ifndef _CmpiAssociationProvider_h
#define _CmpiAssociationProvider_h

#include "cmpift.h"
#include "CmpiProvider.h"

namespace CmpiCpp {

    class CmpiInstanceResult;
    class CmpiObjectPathResult;

    class CmpiAssociationProvider : public virtual CmpiProvider {

    public:

        CmpiAssociationProvider();
        ~CmpiAssociationProvider();

        // Association provider interface

        virtual void 
        associators(const CmpiContext &context, 
                    const CmpiObjectPath &path, 
                    const CmpiName &assocClass, 
                    const CmpiName &resultClass,
                    const CmpiName &role, 
                    const CmpiName &resultRole, 
                    const char **properties,
                    CmpiInstanceResult &result) = 0;

        virtual void 
        associatorNames(const CmpiContext &context, 
                        const CmpiObjectPath &path, 
                        const CmpiName &assocClass, 
                        const CmpiName &resultClass,
                        const CmpiName &role, 
                        const CmpiName &resultRole,
                        CmpiObjectPathResult &result) = 0;

        virtual void 
        references(const CmpiContext &context, 
                   const CmpiObjectPath &path, 
                   const CmpiName &resultClass, 
                   const CmpiName &role,
                   const char **properties,
                   CmpiInstanceResult &result) = 0;

        virtual void 
        referenceNames(const CmpiContext &context, 
                       const CmpiObjectPath &path, 
                       const CmpiName &resultClass, 
                       const CmpiName &role,
                       CmpiObjectPathResult &result) = 0;

        // Return CMPI function table

        CMPIAssociationMI *getAssociationMI();

    private:

        // Static functions to drive C++ methods from C

        static CMPIStatus 
        _driveCleanup(CMPIAssociationMI *mi, 
                      const CMPIContext *context, 
                      CMPIBoolean terminating);

        static CMPIStatus
        _driveAssociators(CMPIAssociationMI *mi,
                          const CMPIContext *context, 
                          const CMPIResult *result,
                          const CMPIObjectPath *path, 
                          const char *assocClass, 
                          const char *resultClass,
                          const char *role, 
                          const char *resultRole, 
                          const char **properties);

        static CMPIStatus
        _driveAssociatorNames(CMPIAssociationMI *mi,
                              const CMPIContext *context, 
                              const CMPIResult *result,
                              const CMPIObjectPath *path, 
                              const char *assocClass, 
                              const char *resultClass,
                              const char *role, 
                              const char *resultRole);

        static CMPIStatus
        _driveReferences(CMPIAssociationMI *mi,
                         const CMPIContext *context, 
                         const CMPIResult *result,
                         const CMPIObjectPath *path, 
                         const char *resultClass, 
                         const char *role,
                         const char **properties);

        static CMPIStatus
        _driveReferenceNames(CMPIAssociationMI *mi,
                             const CMPIContext *context, 
                             const CMPIResult *result,
                             const CMPIObjectPath *path, 
                             const char *resultClass, 
                             const char *role);

        // MI function table

        CMPIAssociationMI _associationMI;
        CMPIAssociationMIFT _associationMIFT;
    };

} // namespace CmpiCpp

#endif // _CmpiAssociationProvider_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
