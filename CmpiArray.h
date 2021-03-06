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

#ifndef _CmpiArray_h
#define _CmpiArray_h

#include <string>
#include "cmpidt.h"

namespace CmpiCpp {

    using namespace std;

    class CmpiData;
    class CmpiBroker;
    class CmpiObjectPath;

    class CmpiArray {

    public:

        // Constructors and destructor

        CmpiArray(CMPIArray *data);
        CmpiArray(const CmpiArray &va);
      
        ~CmpiArray();

        // Wrappers for CMPIArrayFT functions

        CMPICount getSize() const;

        CMPIType getSimpleType() const;
        CmpiData getElementAt(CMPICount ndx) const;

        string str() const;

        void setElementAt(CMPICount ndx, const CMPIData *value);
        void setElementAt(CMPICount ndx, const CmpiData &value);
        void setElementAt(CMPICount ndx, CMPIUint8 value);
        void setElementAt(CMPICount ndx, CMPISint8 value);
        void setElementAt(CMPICount ndx, CMPIUint16 value);
        void setElementAt(CMPICount ndx, CMPISint16 value);
        void setElementAt(CMPICount ndx, CMPIUint32 value);
        void setElementAt(CMPICount ndx, CMPISint32 value);
        void setElementAt(CMPICount ndx, CMPIUint64 value);
        void setElementAt(CMPICount ndx, CMPISint64 value);
        void setElementAt(CMPICount ndx, CMPIReal32 value);
        void setElementAt(CMPICount ndx, CMPIReal64 value);
        void setElementAt(CMPICount ndx, bool value);
        void setElementAt(CMPICount ndx, const char *value);
        void setElementAt(CMPICount ndx, const string &value);
        void setElementAt(CMPICount ndx, const CmpiObjectPath &value);

        // Overloaded operators

        bool operator==(const CmpiArray &obj) const;
        bool operator!=(const CmpiArray &obj) const;

        CmpiArray &operator=(const CmpiArray &rhs);

        // Return CMPI encoding of array

        CMPIArray *toCMPI() const;

    private:

        CMPIArray *_data;
        bool _wasCloned;        // Did we clone() this array?
        bool _isCopy;           // Is this a copy of the CMPIArray pointer?

        void _clone();          // Make a clone of the array for copy-on-write
    };

    // Helper functions

    ostream &operator<<(ostream &output, const CmpiArray &obj);

    CmpiArray makeCmpiArray(const CmpiBroker &broker, int maxsize,
                            CMPIType type);

    bool CMPIArrayCompare(const CMPIArray *a, const CMPIArray *b);

} // namespace CmpiCpp

#endif // _CmpiArray_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
