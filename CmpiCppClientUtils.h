//
// Copyright (C) 2009 by Hewlett-Packard Development Company L.P.
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

#ifndef _CmpiClientUtils_h
#define _CmpiClientUtils_h

#include "CmpiCpp.h"
#include "CmpiBrokerEnumeration.h"

#include <vector>

namespace CmpiCpp {

    using namespace std;

    // Adapter to convert a vector of CmpiInstances into a CmpiEnumeration

    class InstanceVectorEnumeration : public Broker::CmpiEnumeration {
    
    public:
    
        InstanceVectorEnumeration(const vector<CmpiInstance> &data);
        ~InstanceVectorEnumeration();

        CMPIStatus release();
        CMPIEnumeration *clone(CMPIStatus *rc);
        CMPIData getNext(CMPIStatus *rc);
        CMPIBoolean hasNext(CMPIStatus *rc);
        CMPIArray *toArray(CMPIStatus *rc);

    private:

        const vector<CmpiInstance> _data;
        vector<CmpiInstance>::const_iterator _iter;
    };

    // Adapter to convert a vector of CmpiObjectPaths into a CmpiEnumeration

    class ObjectPathVectorEnumeration : public Broker::CmpiEnumeration {
    
    public:
    
        ObjectPathVectorEnumeration(const vector<CmpiObjectPath> &data);
        ~ObjectPathVectorEnumeration();

        CMPIStatus release();
        CMPIEnumeration *clone(CMPIStatus *rc);
        CMPIData getNext(CMPIStatus *rc);
        CMPIBoolean hasNext(CMPIStatus *rc);
        CMPIArray *toArray(CMPIStatus *rc);

    private:

        const vector<CmpiObjectPath> _data;
        vector<CmpiObjectPath>::const_iterator _iter;
    };

} // namespace CmpiCpp

#endif // _CmpiClientUtils_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
