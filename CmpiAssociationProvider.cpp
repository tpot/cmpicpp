//
// Copyright (C) 2007 by Hewlett-Packard Development Company L.P.
// HP Confidential - No photocopying
//
// Author: Tim Potter <tpot@hp.com>
//

#include "CmpiName.h"
#include "CmpiResult.h"
#include "CmpiStatus.h"
#include "CmpiContext.h"
#include "CmpiInstance.h"
#include "CmpiObjectPath.h"
#include "CmpiAssociationProvider.h"

using namespace std;
using namespace CmpiCpp;

CmpiAssociationProvider::CmpiAssociationProvider()
{
    _associationMI.hdl = this;
    _associationMI.ft = &_associationMIFT;

    _associationMIFT.ftVersion = 200;
    _associationMIFT.miVersion = 0;
    _associationMIFT.miName = _name;

    _associationMIFT.cleanup = _driveCleanup;
    _associationMIFT.associators = _driveAssociators;
    _associationMIFT.associatorNames = _driveAssociatorNames;
    _associationMIFT.references = _driveReferences;
    _associationMIFT.referenceNames = _driveReferenceNames;
}

CmpiAssociationProvider::~CmpiAssociationProvider()
{
}

CMPIAssociationMI *
CmpiAssociationProvider::getAssociationMI()
{
    return &_associationMI;
}

CMPIStatus 
CmpiAssociationProvider::_driveCleanup(CMPIAssociationMI *mi, 
                                       const CMPIContext *context, 
                                       CMPIBoolean terminating)
{
    CmpiAssociationProvider *p = 
        reinterpret_cast<CmpiAssociationProvider *>(mi->hdl);

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
CmpiAssociationProvider::_driveAssociators(CMPIAssociationMI *mi,
                                           const CMPIContext *context, 
                                           const CMPIResult *result,
                                           const CMPIObjectPath *path, 
                                           const char *assocClass, 
                                           const char *resultClass,
                                           const char *role, 
                                           const char *resultRole, 
                                           const char **properties)
{
    CmpiAssociationProvider *p = 
        reinterpret_cast<CmpiAssociationProvider *>(mi->hdl);

    DeliverInstanceResult handler(result);
    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->associators(CmpiContext(context), 
                       CmpiObjectPath(path), 
                       assocClass, 
                       resultClass, 
                       role, 
                       resultRole, 
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
CmpiAssociationProvider::_driveAssociatorNames(CMPIAssociationMI *mi,
                                               const CMPIContext *context, 
                                               const CMPIResult *result,
                                               const CMPIObjectPath *path, 
                                               const char *assocClass, 
                                               const char *resultClass,
                                               const char *role, 
                                               const char *resultRole)
{
    CmpiAssociationProvider *p = 
        reinterpret_cast<CmpiAssociationProvider *>(mi->hdl);

    DeliverObjectPathResult handler(result);
    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->associatorNames(CmpiContext(context), 
                           CmpiObjectPath(path), 
                           assocClass, 
                           resultClass, 
                           role, 
                           resultRole,
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
CmpiAssociationProvider::_driveReferences(CMPIAssociationMI *mi,
                                          const CMPIContext *context, 
                                          const CMPIResult *result,
                                          const CMPIObjectPath *path, 
                                          const char *resultClass, 
                                          const char *role,
                                          const char **properties)
{
    CmpiAssociationProvider *p = 
        reinterpret_cast<CmpiAssociationProvider *>(mi->hdl);

    DeliverInstanceResult handler(result);
    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->references(CmpiContext(context), 
                      CmpiObjectPath(path), 
                      resultClass, 
                      role, 
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
CmpiAssociationProvider::_driveReferenceNames(CMPIAssociationMI *mi,
                                              const CMPIContext *context, 
                                              const CMPIResult *result,
                                              const CMPIObjectPath *path, 
                                              const char *resultClass, 
                                              const char *role)
{
    CmpiAssociationProvider *p = 
        reinterpret_cast<CmpiAssociationProvider *>(mi->hdl);

    DeliverObjectPathResult handler(result);
    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->referenceNames(CmpiContext(context), 
                          CmpiObjectPath(path), 
                          resultClass, 
                          role,
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
