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

#ifndef _CmpiBrokerObjectPath_h
#define _CmpiBrokerObjectPath_h

#include <string>

#include "cmpidt.h"
#include "cmpift.h"

namespace CmpiCpp {

    namespace Broker {

        using namespace std;

        class CmpiObjectPath {

        public:

            CmpiObjectPath();
            virtual ~CmpiObjectPath();

            CMPIObjectPath *toCMPI();        

            virtual CMPIStatus release() = 0;

            virtual CMPIObjectPath *clone(CMPIStatus *rc) = 0;

            virtual CMPIStatus setNameSpace(const char *ns) = 0;

            virtual CMPIString *getNameSpace(CMPIStatus *rc) = 0;

            virtual CMPIStatus setHostname(const char *hn) = 0;

            virtual CMPIString *getHostname(CMPIStatus *rc) = 0;

            virtual CMPIStatus setClassName(const char *cn) = 0;

            virtual CMPIString *getClassName(CMPIStatus *rc) = 0;

            virtual CMPIStatus 
            setHostAndNameSpaceFromObjectPath(const CMPIObjectPath *src) = 0;

            virtual CMPIStatus
            setNamespaceFromObjectPath(const CMPIObjectPath *src) = 0;

            virtual CMPIStatus addKey(const char *name, const CMPIValue* value,
                                      CMPIType type) = 0;

            virtual CMPIData getKey(const char *name, CMPIStatus *rc) = 0;

            virtual CMPIData getKeyAt(unsigned int index, CMPIString **name,
                                      CMPIStatus *rc) = 0;

            virtual unsigned int getKeyCount(CMPIStatus *rc) = 0;

            virtual CMPIString *toString(CMPIStatus *rc) = 0;

        private:

            // Prevent copying

            CmpiObjectPath(CmpiObjectPath &);
            CmpiObjectPath &operator=(const CmpiObjectPath &);

            // CMPI function table and driver functions

            CMPIObjectPath _objectpath;
            CMPIObjectPathFT _objectpathFT;

            static CMPIStatus _driveRelease(CMPIObjectPath* op);

            static CMPIObjectPath* _driveClone(const CMPIObjectPath* op, 
                                               CMPIStatus* rc);

            static CMPIStatus _driveSetNameSpace(CMPIObjectPath* op, 
                                                 const char *ns);

            static CMPIString* _driveGetNameSpace(const CMPIObjectPath* op, 
                                                  CMPIStatus* rc);

            static CMPIStatus _driveSetHostname(CMPIObjectPath* op, 
                                                const char *hn);

            static CMPIString* _driveGetHostname(const CMPIObjectPath* op, 
                                                 CMPIStatus* rc);

            static CMPIStatus _driveSetClassName(CMPIObjectPath* op, 
                                                 const char *cn);

            static CMPIString* _driveGetClassName(const CMPIObjectPath* op, 
                                                  CMPIStatus* rc);

            static CMPIStatus _driveAddKey(CMPIObjectPath* op, const char *name,
                                           const CMPIValue* value, 
                                           CMPIType type);

            static CMPIData _driveGetKey(const CMPIObjectPath* op, 
                                         const char *name, CMPIStatus* rc);

            static CMPIData _driveGetKeyAt(const CMPIObjectPath* op, 
                                           unsigned int index, 
                                           CMPIString** name, 
                                           CMPIStatus* rc);

            static unsigned int _driveGetKeyCount(const CMPIObjectPath* op, 
                                                  CMPIStatus* rc);

            static CMPIStatus _driveSetNameSpaceFromObjectPath
            (CMPIObjectPath* op, const CMPIObjectPath* src);

            static CMPIStatus _driveSetHostAndNameSpaceFromObjectPath
            (CMPIObjectPath* op, const CMPIObjectPath* src);
	
            static CMPIData _driveGetClassQualifier(const CMPIObjectPath* op, 
                                                    const char *qName, 
                                                    CMPIStatus *rc);

            static CMPIData _driveGetPropertyQualifier(const CMPIObjectPath* op,
                                                       const char *pName, 
                                                       const char *qName, 
                                                       CMPIStatus *rc);

            static CMPIData _driveGetMethodQualifier(const CMPIObjectPath* op, 
                                                     const char *methodName, 
                                                     const char *qName, 
                                                     CMPIStatus *rc);

            static CMPIData _driveGetParameterQualifier
            (const CMPIObjectPath* op, const char *mName, const char *pName, 
             const char *qName, CMPIStatus *rc);
	
            static CMPIString *_driveToString(const CMPIObjectPath* op, 
                                              CMPIStatus *rc);
        };

    } // namespace Broker

} // namespace CmpiCpp

#endif // _CmpiBrokerObjectPath_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
