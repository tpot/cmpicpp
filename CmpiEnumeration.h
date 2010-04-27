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

#ifndef _CmpiEnumeration_h
#define _CmpiEnumeration_h

namespace CmpiCpp {

    using namespace std;

    //
    // Wrap a CMPIEnumeration
    //

    class CmpiData;
    class CmpiArray;
    class CmpiInstance;
    class CmpiObjectPath;

    class CmpiEnumeration {

    public:

        // Constructors

        CmpiEnumeration(const CMPIEnumeration *args);
        CmpiEnumeration(const CmpiEnumeration &args);

        ~CmpiEnumeration();

        // Accessors

        CmpiData getNext() const;
        bool hasNext() const;
        CmpiArray toArray() const;

    private:

        bool _wasCloned;
        CMPIEnumeration *_data;

        const CmpiEnumeration &operator=(const CmpiEnumeration &rhs);
    };    

} // namespace CmpiCpp

#endif // _CmpiEnumeration_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
