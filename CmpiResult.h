//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#ifndef _CmpiResult_h
#define _CmpiResult_h

#include <string>
#include "CMPI/cmpidt.h"

namespace CmpiCpp {

    using namespace std;

    class CmpiData;
    class CmpiName;
    class CmpiInstance;
    class CmpiObjectPath;

    //
    // Response handler interfaces
    //

    class CmpiResult {

    public:

        CmpiResult() {};
        virtual ~CmpiResult() {};
    };

    class CmpiObjectPathResult : public CmpiResult {

    public:

        virtual void deliver(const CmpiObjectPath &data) = 0;
    };

    class CmpiInstanceResult : public CmpiResult {

    public:

        virtual void deliver(const CmpiInstance &data) = 0;
    };

    class CmpiMethodResult : public CmpiResult {

    public:

        // Deliver return value

        virtual void deliver(const CmpiData &value) = 0;
        virtual void deliver(CMPIUint8 value) = 0;
        virtual void deliver(CMPISint8 value) = 0;
        virtual void deliver(CMPIUint16 value) = 0;
        virtual void deliver(CMPISint16 value) = 0;
        virtual void deliver(CMPIUint32 value) = 0;
        virtual void deliver(CMPISint32 value) = 0;
        virtual void deliver(CMPIUint64 value) = 0;
        virtual void deliver(CMPISint64 value) = 0;
        virtual void deliver(CMPIReal32 value) = 0;
        virtual void deliver(CMPIReal64 value) = 0;
        virtual void deliver(bool value) = 0;
        virtual void deliver(const char *value) = 0;
        virtual void deliver(const string &value) = 0;
        virtual void deliver(const CmpiObjectPath &value) = 0;

        // Deliver output parameters

        virtual void deliver(const CmpiName &key, const CmpiData &value) = 0;
        virtual void deliver(const CmpiName &key, CMPIUint8 value) = 0;
        virtual void deliver(const CmpiName &key, CMPISint8 value) = 0;
        virtual void deliver(const CmpiName &key, CMPIUint16 value) = 0;
        virtual void deliver(const CmpiName &key, CMPISint16 value) = 0;
        virtual void deliver(const CmpiName &key, CMPIUint32 value) = 0;
        virtual void deliver(const CmpiName &key, CMPISint32 value) = 0;
        virtual void deliver(const CmpiName &key, CMPIUint64 value) = 0;
        virtual void deliver(const CmpiName &key, CMPISint64 value) = 0;
        virtual void deliver(const CmpiName &key, CMPIReal32 value) = 0;
        virtual void deliver(const CmpiName &key, CMPIReal64 value) = 0;
        virtual void deliver(const CmpiName &key, bool value) = 0;
        virtual void deliver(const CmpiName &key, const char *value) = 0;
        virtual void deliver(const CmpiName &key, const string &value) = 0;
        virtual void deliver(const CmpiName &key, const CmpiObjectPath &value) = 0;
    };

    //
    // Concrete result handlers that deliver through to a CMPI result
    // handler.
    //

    class DeliverObjectPathResult : public CmpiObjectPathResult {

    public:

        DeliverObjectPathResult(const CMPIResult *result);
        ~DeliverObjectPathResult();

        void deliver(const CmpiObjectPath &data);

    private:

        const CMPIResult *_result;
    };

    class DeliverInstanceResult : public CmpiInstanceResult {

    public:

        DeliverInstanceResult(const CMPIResult *result);
        ~DeliverInstanceResult();

        void deliver(const CmpiInstance &data);

        void setDeliverDone( bool done) { _deliverDone = done; };

    private:

        const CMPIResult *_result;
        bool _deliverDone;
    };

    class DeliverMethodResult : public CmpiMethodResult {

    public:

        DeliverMethodResult(const CMPIResult *result,
                            const CMPIArgs *out);
        ~DeliverMethodResult();

        // Deliver return value

        void deliver(const CmpiData &value);
        void deliver(CMPIUint8 value);
        void deliver(CMPISint8 value);
        void deliver(CMPIUint16 value);
        void deliver(CMPISint16 value);
        void deliver(CMPIUint32 value);
        void deliver(CMPISint32 value);
        void deliver(CMPIUint64 value);
        void deliver(CMPISint64 value);
        void deliver(CMPIReal32 value);
        void deliver(CMPIReal64 value);
        void deliver(bool value);
        void deliver(const char *value);
        void deliver(const string &value);
        void deliver(const CmpiObjectPath &value);

        // Deliver output parameters

        void deliver(const CmpiName &key, const CmpiData &value);
        void deliver(const CmpiName &key, CMPIUint8 value);
        void deliver(const CmpiName &key, CMPISint8 value);
        void deliver(const CmpiName &key, CMPIUint16 value);
        void deliver(const CmpiName &key, CMPISint16 value);
        void deliver(const CmpiName &key, CMPIUint32 value);
        void deliver(const CmpiName &key, CMPISint32 value);
        void deliver(const CmpiName &key, CMPIUint64 value);
        void deliver(const CmpiName &key, CMPISint64 value);
        void deliver(const CmpiName &key, CMPIReal32 value);
        void deliver(const CmpiName &key, CMPIReal64 value);
        void deliver(const CmpiName &key, bool value);
        void deliver(const CmpiName &key, const char *value);
        void deliver(const CmpiName &key, const string &value);
        void deliver(const CmpiName &key, const CmpiObjectPath &value);

    private:

        const CMPIResult *_result;
        const CMPIArgs *_out;
    };

} // namespace CmpiCpp

#endif // _CmpiResult_h

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
