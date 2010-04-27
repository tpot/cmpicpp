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

#include "UnimplementedFT.h"

using namespace CmpiCpp::Broker;

//
// Implementation of UnimplementedBrokerFT class
//

CMPIContext *
UnimplementedBrokerFT::prepareAttachThread(const CMPIContext *) // context
{
    return NULL;
}

CMPIStatus 
UnimplementedBrokerFT::attachThread(const CMPIContext *) // context
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

CMPIStatus 
UnimplementedBrokerFT::detachThread(const CMPIContext *) // context
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

CMPIStatus 
UnimplementedBrokerFT::deliverIndication(const CMPIContext *, // context
                                         const char *,        // nameSpace
                                         const CMPIInstance *) // ind
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

CMPIEnumeration *
UnimplementedBrokerFT::enumInstanceNames(const CMPIContext *, // context
                                         const CMPIObjectPath *, // path
                                         CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIInstance *
UnimplementedBrokerFT::getInstance(const CMPIContext *,    // context
                                   const CMPIObjectPath *, // path
                                   const char **,          // properties
                                   CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIObjectPath *
UnimplementedBrokerFT::createInstance(const CMPIContext *,    // context
                                      const CMPIObjectPath *, // path
                                      const CMPIInstance *,   // inst
                                      CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIStatus 
UnimplementedBrokerFT::modifyInstance(const CMPIContext *,    // context
                                      const CMPIObjectPath *, // path
                                      const CMPIInstance *,   // inst
                                      const char **)          // properties
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

CMPIStatus 
UnimplementedBrokerFT::deleteInstance(const CMPIContext *,    // context
                                      const CMPIObjectPath *) // path
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

CMPIEnumeration *
UnimplementedBrokerFT::execQuery(const CMPIContext *,    // context
                                 const CMPIObjectPath *, // path
                                 const char *,           // query
                                 const char *,           // lang
                                 CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIEnumeration *
UnimplementedBrokerFT::enumInstances(const CMPIContext *,    // context
                                     const CMPIObjectPath *, // path
                                     const char **,          // properties
                                     CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}
    
CMPIEnumeration *
UnimplementedBrokerFT::associators(const CMPIContext *,    // context
                                   const CMPIObjectPath *, // path
                                   const char *,           // assocClass
                                   const char *,           // resultClass
                                   const char *,           // role
                                   const char *,           // resultRole
                                   const char **,          // properties
                                   CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIEnumeration *
UnimplementedBrokerFT::associatorNames(const CMPIContext *,    // context
                                       const CMPIObjectPath *, // path
                                       const char *,           // assocClass
                                       const char *,           // resultClass
                                       const char *,           // role
                                       const char *,           // resultRole
                                       CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}
    
CMPIEnumeration *
UnimplementedBrokerFT::references(const CMPIContext *,    // context
                                  const CMPIObjectPath *, // path
                                  const char *,           // resultClass
                                  const char *,           // role
                                  const char **,          // properties
                                  CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}
    
CMPIEnumeration *
UnimplementedBrokerFT::referenceNames(const CMPIContext *,    // context
                                      const CMPIObjectPath *, // path
                                      const char *,           // resultClass
                                      const char *,           // role
                                      CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIData 
UnimplementedBrokerFT::invokeMethod(const CMPIContext *,    // context
                                    const CMPIObjectPath *, // path
                                    const char *,           // method
                                    const CMPIArgs *,       // in
                                    CMPIArgs *,             // out
                                    CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    CMPIData result;

    result.type = CMPI_null;
    result.state = CMPI_nullValue;

    return result;
}
    
CMPIStatus 
UnimplementedBrokerFT::setProperty(const CMPIContext *,    // context
                                   const CMPIObjectPath *, // path
                                   const char *,           // name
                                   const CMPIValue *,      // value
                                   CMPIType)               // type
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}
    
CMPIData 
UnimplementedBrokerFT::getProperty(const CMPIContext *,    // context
                                   const CMPIObjectPath *, // path
                                   const char *,           // name
                                   CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    CMPIData result;

    result.type = CMPI_null;
    result.state = CMPI_nullValue;

    return result;    
}

//
// Implementation of UnimplementedBrokerEncFT class
//

CMPIInstance *
UnimplementedBrokerEncFT::newInstance(const CMPIObjectPath *, // op
                                      CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIObjectPath *
UnimplementedBrokerEncFT::newObjectPath(const char *, // ns
                                        const char *, // cn
                                        CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIArgs *
UnimplementedBrokerEncFT::newArgs(CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIString *
UnimplementedBrokerEncFT::newString(const char *, // data
                                    CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIArray *
UnimplementedBrokerEncFT::newArray(CMPICount,    // max
                                   CMPIType,     // type
                                   CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIDateTime *
UnimplementedBrokerEncFT::newDateTime(CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIDateTime *
UnimplementedBrokerEncFT::newDateTimeFromBinary(CMPIUint64,   // binTime
                                                bool,         // interval
                                                CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIDateTime *
UnimplementedBrokerEncFT::newDateTimeFromChars(const char *, // utcTime
                                               CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}
            
CMPISelectExp *
UnimplementedBrokerEncFT::newSelectExp(const char *, // query
                                       const char *, // lang
                                       CMPIArray **, // projection
                                       CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIBoolean 
UnimplementedBrokerEncFT::classPathIsA(const CMPIObjectPath *, // op
                                       const char *,           // type
                                       CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return false;
}

CMPIString *
UnimplementedBrokerEncFT::toString(const void *, // object
                                   CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIBoolean 
UnimplementedBrokerEncFT::isOfType(const void *, // object
                                   const char *, // type
                                   CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return false;
}

CMPIString *
UnimplementedBrokerEncFT::getType(const void *, // object
                                  CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIString *
UnimplementedBrokerEncFT::getMessage(const char *, // msgId
                                     const char *, // defMsg
                                     CMPIStatus *rc)
{
    if (rc) {
        rc->rc = CMPI_RC_ERR_NOT_SUPPORTED;
        rc->msg = NULL;
    }

    return NULL;
}

CMPIStatus 
UnimplementedBrokerEncFT::logMessage(int,                // severity
                                     const char *,       // id
                                     const char *,       // text
                                     const CMPIString *) // string
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

CMPIStatus 
UnimplementedBrokerEncFT::trace(int,          // level
                                const char *, // component
                                const char *, // text
                                const CMPIString *) // string
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
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
