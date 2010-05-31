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

#include "CmpiStatus.h"
#include "CmpiContext.h"
#include "CmpiBroker.h"
#include "CmpiObjectPath.h"
#include "CmpiIndicationProvider.h"

using namespace std;
using namespace CmpiCpp;

CmpiIndicationProvider::CmpiIndicationProvider()
{
    _indicationMI.hdl = this;
    _indicationMI.ft = &_indicationMIFT;

    _indicationMIFT.ftVersion = 200;
    _indicationMIFT.miVersion = 0;
    _indicationMIFT.miName = _name;

    _indicationMIFT.cleanup = _driveCleanup;
    _indicationMIFT.authorizeFilter = _driveAuthorizeFilter;
    _indicationMIFT.mustPoll = _driveMustPoll;
    _indicationMIFT.activateFilter = _driveActivateFilter;
    _indicationMIFT.deActivateFilter = _driveDeActivateFilter;
    _indicationMIFT.enableIndications = _driveEnableIndications;
    _indicationMIFT.disableIndications = _driveDisableIndications;
}

CmpiIndicationProvider::~CmpiIndicationProvider()
{
}

CMPIIndicationMI *
CmpiIndicationProvider::getIndicationMI()
{
    return &_indicationMI;
}

CMPIStatus 
CmpiIndicationProvider::_driveCleanup(CMPIIndicationMI *mi, 
                                      const CMPIContext *context, 
                                      CMPIBoolean terminating)
{
    CmpiIndicationProvider *p = 
        reinterpret_cast<CmpiIndicationProvider *>(mi->hdl);

    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        if (!terminating) {

            switch (p->unloadOK(context)) {
            case okToUnload:
                break;
            case doNotUnloadNow:
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
            (p->getBroker().toCMPI(), &status, s.getRC(), s.getMsg().c_str());
    } catch (exception &x) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, x.what());
    } catch (...) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, "unknown exception");
    }

    return status;
}
	
CMPIStatus
CmpiIndicationProvider::_driveAuthorizeFilter(CMPIIndicationMI *mi, 
                                              const CMPIContext *context, 
                                              const CMPISelectExp *filter,
                                              const char *className, 
                                              const CMPIObjectPath *path,
                                              const char *user)
{
    CmpiIndicationProvider *p = 
        reinterpret_cast<CmpiIndicationProvider *>(mi->hdl);

    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {
        p->authorizeFilter(CmpiContext(context), 
                           filter, 
                           className?string(className):string(),
                           CmpiObjectPath(path), 
                           user?string(user):string());

    } catch (CmpiStatus &s) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, s.getRC(), s.getMsg().c_str());
    } catch (exception &x) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, x.what());
    } catch (...) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, "unknown exception");
    }

    return status;

}

CMPIStatus 
CmpiIndicationProvider::_driveMustPoll(CMPIIndicationMI *mi, 
                                       const CMPIContext *context, 
                                       const CMPISelectExp *filter, 
                                       const char *className, 
                                       const CMPIObjectPath *path)
{
    CmpiIndicationProvider *p = 
        reinterpret_cast<CmpiIndicationProvider *>(mi->hdl);

    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->mustPoll( CmpiContext(context), 
                     filter, 
                     className?string(className):string(), 
                     path);

    } catch (CmpiStatus &s) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, s.getRC(), s.getMsg().c_str());
    } catch (exception &x) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, x.what());
    } catch (...) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, "unknown exception");
    }

    return status;
}

CMPIStatus 
CmpiIndicationProvider::_driveActivateFilter(CMPIIndicationMI *mi, 
                                             const CMPIContext *context, 
                                             const CMPISelectExp *filter,
                                             const char *className, 
                                             const CMPIObjectPath *path, 
                                             CMPIBoolean first)
{
    CmpiIndicationProvider *p = 
        reinterpret_cast<CmpiIndicationProvider *>(mi->hdl);

    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->activateFilter( CmpiContext(context), 
                           filter, 
                           className?string(className):string(), 
                           path, 
                           first);

    } catch (CmpiStatus &s) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, s.getRC(), s.getMsg().c_str());
    } catch (exception &x) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, x.what());
    } catch (...) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, "unknown exception");
    }

    return status;
}

CMPIStatus 
CmpiIndicationProvider::_driveDeActivateFilter(CMPIIndicationMI *mi, 
                                               const CMPIContext *context, 
                                               const CMPISelectExp *filter, 
                                               const char *className, 
                                               const CMPIObjectPath *path, 
                                               CMPIBoolean last)
{
    CmpiIndicationProvider *p = 
        reinterpret_cast<CmpiIndicationProvider *>(mi->hdl);

    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->deactivateFilter(CmpiContext(context), 
                            filter, 
                            className?string(className):string(), 
                            path, 
                            last);

    } catch (CmpiStatus &s) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, s.getRC(), s.getMsg().c_str());
    } catch (exception &x) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, x.what());
    } catch (...) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, "unknown exception");
    }

    return status;
}

CMPIStatus
CmpiIndicationProvider::_driveEnableIndications(CMPIIndicationMI *mi, 
                                                const CMPIContext *context)
{
    CmpiIndicationProvider *p = 
        reinterpret_cast<CmpiIndicationProvider *>(mi->hdl);

    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->enableIndications(context);

    } catch (CmpiStatus &s) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, s.getRC(), s.getMsg().c_str());
    } catch (exception &x) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, x.what());
    } catch (...) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, "unknown exception");
    }

    return status;
}

CMPIStatus
CmpiIndicationProvider::_driveDisableIndications(CMPIIndicationMI *mi, 
                                           const CMPIContext *context)
{
    CmpiIndicationProvider *p = 
        reinterpret_cast<CmpiIndicationProvider *>(mi->hdl);

    CMPIStatus status = { CMPI_RC_OK, NULL };

    try {

        p->disableIndications(context);

    } catch (CmpiStatus &s) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, s.getRC(), s.getMsg().c_str());
    } catch (exception &x) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, x.what());
    } catch (...) {
        CMSetStatusWithChars
            (p->getBroker().toCMPI(), &status, CMPI_RC_ERR_FAILED, "unknown exception");
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
