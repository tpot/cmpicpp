//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "CmpiArgs.h"
#include "CmpiName.h"
#include "CmpiResult.h"
#include "CmpiStatus.h"
#include "CmpiContext.h"
#include "CmpiInstance.h"
#include "CmpiObjectPath.h"
#include "CmpiMethodProvider.h"

using namespace std;
using namespace CmpiCpp;

CmpiMethodProvider::CmpiMethodProvider()
{
    _methodMI.hdl = this;
    _methodMI.ft = &_methodMIFT;

    _methodMIFT.ftVersion = 200;
    _methodMIFT.miVersion = 0;
    _methodMIFT.miName = _name;

    _methodMIFT.cleanup = _driveCleanup;
    _methodMIFT.invokeMethod = _driveInvokeMethod;
}

CmpiMethodProvider::~CmpiMethodProvider()
{
}

CMPIMethodMI *
CmpiMethodProvider::getMethodMI()
{
    return &_methodMI;
}

CMPIStatus 
CmpiMethodProvider::_driveCleanup(CMPIMethodMI *mi, 
                                  const CMPIContext *context, 
                                  CMPIBoolean terminating)
{
    CmpiMethodProvider *p = reinterpret_cast<CmpiMethodProvider *>(mi->hdl);

    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        if (!terminating) {

            switch (p->unloadOK(context)) {
            case okToUnload:
                break;
            case doNotUnload:
                CMReturn(CMPI_RC_DO_NOT_UNLOAD);
            case neverUnload:
                CMReturn(CMPI_RC_NEVER_UNLOAD);
            }
        }

        if (p->decRefcount() == 0) {
            p->cleanup(context, terminating);
            delete p;
        }

    } catch (CmpiStatus &s) {
        CMSetStatusWithChars
            (p->getBroker(), &status, s.getRC(), s.getMsg().c_str());
    } catch (exception &x) {
        CMSetStatusWithChars
            (p->getBroker(), &status, CMPI_RC_ERR_FAILED, x.what());
    } catch (...) {
        CMSetStatusWithChars
            (p->getBroker(), &status, CMPI_RC_ERR_FAILED, "unknown exception");
    }

    return status;
}

CMPIStatus 
CmpiMethodProvider::_driveInvokeMethod(CMPIMethodMI *mi, 
                                       const CMPIContext *context, 
                                       const CMPIResult *result,
                                       const CMPIObjectPath *path, 
                                       const char *methodName,
                                       const CMPIArgs *in, 
                                       CMPIArgs *out)
{
    CmpiMethodProvider *p = reinterpret_cast<CmpiMethodProvider *>(mi->hdl);
    DeliverMethodResult handler(result, out);
    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->invokeMethod(CmpiContext(context), 
                        CmpiObjectPath(path), 
                        methodName, 
                        in,
                        handler);

    } catch (CmpiStatus &s) {
        CMSetStatusWithChars(p->getBroker(), &status, s.getRC(), 
                             s.getMsg().c_str());
    } catch (exception &x) {
        CMSetStatusWithChars
            (p->getBroker(), &status, CMPI_RC_ERR_FAILED, x.what());
    } catch (...) {
        CMSetStatusWithChars
            (p->getBroker(), &status, CMPI_RC_ERR_FAILED, "unknown exception");
    }

    return status;
}

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//