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

#include "CmpiName.h"
#include "CmpiResult.h"
#include "CmpiStatus.h"
#include "CmpiContext.h"
#include "CmpiInstance.h"
#include "CmpiObjectPath.h"
#include "CmpiInstanceProvider.h"

using namespace std;
using namespace CmpiCpp;

CmpiInstanceProvider::CmpiInstanceProvider()
{
    _instanceMI.hdl = this;
    _instanceMI.ft = &_instanceMIFT;

    _instanceMIFT.ftVersion = 200;
    _instanceMIFT.miVersion = 0;
    _instanceMIFT.miName = _name;

    _instanceMIFT.cleanup = _driveCleanup;
    _instanceMIFT.enumerateInstanceNames = _driveEnumInstanceNames;
    _instanceMIFT.enumerateInstances = _driveEnumInstances;
    _instanceMIFT.getInstance = _driveGetInstance;
    _instanceMIFT.createInstance = _driveCreateInstance;
    _instanceMIFT.modifyInstance = _driveModifyInstance;
    _instanceMIFT.deleteInstance = _driveDeleteInstance;
    _instanceMIFT.execQuery = _driveExecQuery;
}

CmpiInstanceProvider::~CmpiInstanceProvider()
{
}

CMPIInstanceMI *
CmpiInstanceProvider::getInstanceMI()
{
    return &_instanceMI;
}

void 
CmpiInstanceProvider::createInstance(const CmpiContext &,    // context 
                                     const CmpiObjectPath &, // path 
                                     const CmpiInstance &,   // inst
                                     CmpiObjectPathResult &) // result
{
    throw CmpiStatus(CMPI_RC_ERR_NOT_SUPPORTED);
}

void 
CmpiInstanceProvider::modifyInstance(const CmpiContext &,    // context
                                     const CmpiObjectPath &, // path
                                     const CmpiInstance &,   // inst
                                     const char **)          // properties
{
    throw CmpiStatus(CMPI_RC_ERR_NOT_SUPPORTED);
}

void 
CmpiInstanceProvider::deleteInstance(const CmpiContext &,    // context
                                     const CmpiObjectPath &) // path
{
    throw CmpiStatus(CMPI_RC_ERR_NOT_SUPPORTED);
}

void 
CmpiInstanceProvider::execQuery(const CmpiContext &,    // context
                                const CmpiObjectPath &, // path
                                const string &,         // language
                                const string &,         // query
                                CmpiObjectPathResult &) // result
{
    throw CmpiStatus(CMPI_RC_ERR_NOT_SUPPORTED);
}

CMPIStatus 
CmpiInstanceProvider::_driveCleanup(CMPIInstanceMI *mi, 
                                    const CMPIContext *context, 
                                    CMPIBoolean terminating)
{
    CmpiInstanceProvider *p = 
        reinterpret_cast<CmpiInstanceProvider *>(mi->hdl);

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
CmpiInstanceProvider::_driveEnumInstanceNames(CMPIInstanceMI *mi, 
                                              const CMPIContext *context, 
                                              const CMPIResult *result, 
                                              const CMPIObjectPath *path)
{
    CmpiInstanceProvider *p = 
        reinterpret_cast<CmpiInstanceProvider *>(mi->hdl);

    DeliverObjectPathResult handler(result);
    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->enumInstanceNames(CmpiContext(context), 
                             CmpiObjectPath(path),
                             handler);

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
CmpiInstanceProvider::_driveEnumInstances(CMPIInstanceMI *mi, 
                                          const CMPIContext *context, 
                                          const CMPIResult *result, 
                                          const CMPIObjectPath *path, 
                                          const char **properties)
{
    CmpiInstanceProvider *p = 
        reinterpret_cast<CmpiInstanceProvider *>(mi->hdl);

    DeliverInstanceResult handler(result);
    CMPIStatus status = { CMPI_RC_OK, NULL };
    
    try {

        p->enumInstances(CmpiContext(context), 
                         CmpiObjectPath(path), 
                         properties,
                         handler);

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
CmpiInstanceProvider::_driveGetInstance(CMPIInstanceMI *mi, 
                                        const CMPIContext *context, 
                                        const CMPIResult *result, 
                                        const CMPIObjectPath *path, 
                                        const char **properties)
{
    CmpiInstanceProvider *p = 
        reinterpret_cast<CmpiInstanceProvider *>(mi->hdl);

    DeliverInstanceResult handler(result);
    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->getInstance(CmpiContext(context), 
                       CmpiObjectPath(path), 
                       properties,
                       handler);

    } catch (CmpiStatus &s) {
        CMSetStatusWithChars
            (p->getBroker(), &status, s.getRC(), s.getMsg().c_str());
            handler.setDeliverDone( false);
    } catch (exception &x) {
        CMSetStatusWithChars
            (p->getBroker(), &status, CMPI_RC_ERR_FAILED, x.what());
             handler.setDeliverDone( false);
    } catch (...) {
        CMSetStatusWithChars
            (p->getBroker(), &status, CMPI_RC_ERR_FAILED, "unknown exception");
             handler.setDeliverDone( false);
    }

    return status;
}

CMPIStatus 
CmpiInstanceProvider::_driveCreateInstance(CMPIInstanceMI *mi, 
                                           const CMPIContext *context, 
                                           const CMPIResult *result, 
                                           const CMPIObjectPath *path, 
                                           const CMPIInstance *instance)
{
    CmpiInstanceProvider *p = 
        reinterpret_cast<CmpiInstanceProvider *>(mi->hdl);

    DeliverObjectPathResult handler(result);
    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {
        
        p->createInstance(CmpiContext(context), 
                          CmpiObjectPath(path), 
                          CmpiInstance(instance),
                          handler);

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
CmpiInstanceProvider::_driveModifyInstance(CMPIInstanceMI *mi, 
                                           const CMPIContext *context, 
                                           const CMPIResult *, // result
                                           const CMPIObjectPath *path, 
                                           const CMPIInstance *instance, 
                                           const char **properties)
{
    CmpiInstanceProvider *p = 
        reinterpret_cast<CmpiInstanceProvider *>(mi->hdl);

    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->modifyInstance(CmpiContext(context), 
                          CmpiObjectPath(path), 
                          CmpiInstance(instance), 
                          properties);

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
CmpiInstanceProvider::_driveDeleteInstance(CMPIInstanceMI *mi, 
                                           const CMPIContext *context, 
                                           const CMPIResult *, // result
                                           const CMPIObjectPath *path)
{
    CmpiInstanceProvider *p = 
        reinterpret_cast<CmpiInstanceProvider *>(mi->hdl);

    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->deleteInstance(CmpiContext(context), 
                          CmpiObjectPath(path));

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
CmpiInstanceProvider::_driveExecQuery(CMPIInstanceMI *mi, 
                                      const CMPIContext *context, 
                                      const CMPIResult *result, 
                                      const CMPIObjectPath *path, 
                                      const char *language,
                                      const char *query)
{
    CmpiInstanceProvider *p = 
        reinterpret_cast<CmpiInstanceProvider *>(mi->hdl);

    DeliverObjectPathResult handler(result);
    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->execQuery(CmpiContext(context), 
                     CmpiObjectPath(path), 
                     language, 
                     query,
                     handler);

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

//
// Local variables:
// mode: c++
// c-indentation-style: stroustrup
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: nil
// End:
//
