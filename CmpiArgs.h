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

#ifndef _CmpiArgs_h
#define _CmpiArgs_h

#include <string>

#include "CmpiName.h"
#include "CmpiData.h"

namespace CmpiCpp {

    using namespace std;

    //
    // Wrap a CMPIArgs
    //

    class CmpiArgs {

    public:

        // Constructors

        CmpiArgs(const CMPIArgs *args);
        CmpiArgs(const CmpiArgs &args);

        virtual ~CmpiArgs();

        CMPIArgs *toCMPI() const;

        // Accessors

        void addArg(const CmpiName &name, bool value);
        void addArg(const CmpiName &name, CMPIUint8 value);
        void addArg(const CmpiName &name, CMPISint8 value);
        void addArg(const CmpiName &name, CMPIUint16 value);
        void addArg(const CmpiName &name, CMPISint16 value);
        void addArg(const CmpiName &name, CMPIUint32 value);
        void addArg(const CmpiName &name, CMPISint32 value);
        void addArg(const CmpiName &name, CMPIUint64 value);
        void addArg(const CmpiName &name, CMPISint64 value);
        void addArg(const CmpiName &name, CMPIReal32 value);
        void addArg(const CmpiName &name, CMPIReal64 value);
        void addArg(const CmpiName &name, const char *value);
        void addArg(const CmpiName &name, const string &value);
        // TODO: datetime, references, arrays, and arrays of references

        CmpiData getArg(const string &name) const;
        pair<CmpiName,CmpiData> getArgAt(unsigned int index) const;
        unsigned int getArgCount() const;

    private:

        CMPIArgs *_data;
        bool _wasCloned;
    };    

    // Factory function

    CmpiArgs makeCmpiArgs(const CMPIBroker *broker);

} // namespace CmpiCpp

#endif // _CmpiArgs_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
