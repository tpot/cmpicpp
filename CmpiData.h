//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiData_h
#define _CmpiData_h

#include <string>
#include "cmpidt.h"

namespace CmpiCpp {

    using namespace std;

    class CmpiArray;
    class CmpiInstance;
    class CmpiDateTime;
    class CmpiObjectPath;

    class CmpiData {

    public:

        // Constructors

        CmpiData();
        CmpiData(CMPIType type);
        CmpiData(const CMPIData *data);
        CmpiData(const CmpiData &data);
        CmpiData(const CmpiObjectPath &data);
        CmpiData(const CmpiInstance &data);
        CmpiData(const CmpiArray &data);
        CmpiData(const CmpiDateTime &data);

        ~CmpiData();

        // Accessors

        CMPIType getType() const;
        bool isNull() const;
        bool isArray() const;
        string str() const;

        operator CMPIUint8() const;
        operator CMPISint8() const;
        operator CMPIUint16() const;
        operator CMPISint16() const;
        operator CMPIUint32() const;
        operator CMPISint32() const;
        operator CMPIUint64() const;
        operator CMPISint64() const;
        operator CMPIReal32() const;
        operator CMPIReal64() const;
        operator bool() const;
        operator string() const;
        operator CmpiObjectPath() const;
        operator CmpiInstance() const;
        operator CmpiArray() const;
        operator CmpiDateTime() const;

        // Operators

        bool operator==(const CmpiData &obj) const;
        bool operator!=(const CmpiData &obj) const;
        CmpiData &operator=(const CmpiData &obj);

        // Convert to CMPI

        CMPIData toCMPI() const;

        // Static methods

        static const CMPIData nullData;
        static string typeToString(CMPIType type);

    private:

        CMPIData _data;
    };

    // Stream output

    ostream &operator<<(ostream &output, const CmpiData &obj);

} // namespace CmpiCpp

#endif // _CmpiData_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
