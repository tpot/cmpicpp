//
// Copyright (C) 2010 by Hewlett-Packard Development Company L.P.
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

#include "CmpiArgs.h"
#include "CmpiData.h"
#include "CmpiName.h"
#include "CmpiArray.h"
#include "CmpiBroker.h"
#include "CmpiStatus.h"
#include "CmpiContext.h"
#include "CmpiDateTime.h"
#include "CmpiInstance.h"
#include "CmpiObjectPath.h"
#include "CmpiEnumeration.h"

#include "CmpiCppClient.h"

using namespace std;
using namespace CmpiCpp;

//
// Implementation of CmpBroker class
//

CmpiBroker::CmpiBroker(const CMPIBroker *arg)
    : _data(const_cast<CMPIBroker *>(arg))
{
}

CmpiBroker::CmpiBroker(const CmpiBroker &arg)
    : _data(arg._data)
{
}

CmpiBroker::~CmpiBroker()
{
}

const CMPIBroker *
CmpiBroker::toCMPI() const
{
    return _data;
}

const CmpiBroker &
CmpiBroker::operator=(const CmpiBroker &rhs)
{
    if (this == &rhs)
        return *this;

    _data = rhs._data;

    return *this;
}

// Broker EncFT functions

CmpiInstance 
CmpiBroker::getInstance(const CmpiContext &context,
                        const CmpiObjectPath &path,
                        const char **properties)
{
   CmpiCppClient *client = makeCmpiCppClient(_data);

   if (client != NULL) {

     try {
       CmpiInstance result(client->getInstance(context, path, properties));
       delete client;
       return result;
     } catch (...) {
       delete client;
       throw;
     }

   } else {

     CMPIStatus st = { CMPI_RC_OK, NULL };
     CMPIObjectPath * cop = path.toCMPI();
   
     CMPIInstance *ci = _data->bft->getInstance( _data, context.toCMPI(), cop, properties, &st);

     if (st.rc!=CMPI_RC_OK) {
       CmpiStatus s(&st);
       throw s;
     }

     return CmpiInstance( ci);
   }
}

CmpiEnumeration 
CmpiBroker::enumInstanceNames(const CmpiContext &context,
                              const CmpiObjectPath &path)
{
   CMPIEnumeration *en;

   CMPIStatus st = { CMPI_RC_OK, NULL };
   CMPIObjectPath * cop = path.toCMPI();
   
   en = _data->bft->enumInstanceNames(_data, context.toCMPI(), cop, &st);
   
   if (st.rc != CMPI_RC_OK) {
     CmpiStatus s(&st);
     throw s;
   }

   return CmpiEnumeration(en);
}

CmpiEnumeration 
CmpiBroker::enumInstances(const CmpiContext &context,
                          const CmpiObjectPath &path,
                          const char **properties)
{
   CmpiCppClient *client = makeCmpiCppClient(_data);

   if (client != NULL) {

     try {
       CmpiEnumeration result(client->enumInstances(context, path, properties));
       delete client;
       return result;
     } catch (...) {
       delete client;
       throw;
     }

   } else {

     CMPIEnumeration *en;

     CMPIStatus st = { CMPI_RC_OK, NULL };
     CMPIObjectPath * cop = path.toCMPI();
   
     en = _data->bft->enumInstances(_data, context.toCMPI(), cop, properties, &st);
   
     if (st.rc != CMPI_RC_OK) {
       CmpiStatus s(&st);
       throw s;
     }

     return CmpiEnumeration(en);
   }
}

CmpiData 
CmpiBroker::invokeMethod(const CmpiContext &context,
                         const CmpiObjectPath &path,
                         const CmpiName &method,
                         const CmpiArgs &in,
                         CmpiArgs &out)
{
   CMPIData data;

   CMPIStatus st = { CMPI_RC_OK, NULL };
   CMPIObjectPath * cop = path.toCMPI();
     
   data = _data->bft->invokeMethod( _data, 
                                      context.toCMPI(), 
                                      cop, 
                                      method.str().c_str(),
                                      in.toCMPI(),
                                      out.toCMPI(),
                                      &st);
   
   if (st.rc != CMPI_RC_OK) {
     CmpiStatus s(&st);
     throw s;
   }

   CMPIData *dataPtr = &data;
   return CmpiData( dataPtr);
}

CMPIStatus 
CmpiBroker::deliverIndication(const CmpiContext & context,
                              const CmpiName & nameSpace,
                              const CmpiInstance &indication)
{
   CMPIStatus st = _data->bft->deliverIndication(_data, 
                                                   context.toCMPI(), 
                                                   nameSpace.str().c_str(), 
                                                   indication.toCMPI());
   
   if (st.rc != CMPI_RC_OK) {
     CmpiStatus s(&st);
     throw s;
   }

   return st;
}

bool 
CmpiBroker::classPathIsA(const CmpiObjectPath &path,
                         const string &parentClassName)
{
   CMPIStatus st = { CMPI_RC_OK, NULL };
   CMPIObjectPath * cop = path.toCMPI();
   
   CMPIBoolean isa = CMClassPathIsA(_data, cop, parentClassName.c_str(), &st);

   if (st.rc!=CMPI_RC_OK) {
     CmpiStatus s(&st);
     throw s;
   }

   return bool(isa);
}

// Factory functions

CmpiDateTime 
CmpiBroker::makeCmpiDateTime()
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIDateTime *dt = _data->eft->newDateTime(_data, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiDateTime result(dt);

    return result;
}

CmpiDateTime 
CmpiBroker::makeCmpiDateTime(time_t t)
{
    return makeCmpiDateTime((uint64_t)t * cmpiBinFormatMsecs, false);
}

CmpiDateTime 
CmpiBroker::makeCmpiDateTime(const string &utcTime)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIDateTime *dt = 
        _data->eft->newDateTimeFromChars(_data, utcTime.c_str(), &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiDateTime result(dt);

    return result;
}

CmpiDateTime 
CmpiBroker::makeCmpiDateTime(uint64_t binTime, bool isInterval)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIDateTime *dt = 
        _data->eft->newDateTimeFromBinary(_data, binTime, isInterval, 
                                           &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiDateTime result(dt);

    return result;
}

CmpiDateTime 
CmpiBroker::makeCurrentDateTime()
{
    time_t now = time(NULL);

    return makeCmpiDateTime((uint64_t)now * cmpiBinFormatMsecs, false);
}

CmpiArray 
CmpiBroker::makeCmpiArray(int maxSize, CMPIType type)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    if (type == CMPI_string)
        type = CMPI_chars;

    CMPIArray *array = _data->eft->newArray(_data, maxSize, type, &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);    

    CmpiArray result(array);

    return result;
}

CmpiObjectPath 
CmpiBroker::makeCmpiObjectPath(const CmpiName &nameSpace, const CmpiName &className)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };

    CMPIObjectPath *path = _data->eft->newObjectPath
        (_data, nameSpace.c_str(), className.c_str(), &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);

    CmpiObjectPath result(path);

    result.setHost("");

    return result;
}

CmpiObjectPath
CmpiBroker::makeCmpiObjectPath(const CmpiName &nameSpace,
                               const CmpiName &className,
                               const CmpiName &hostName)
{
    CmpiObjectPath result(makeCmpiObjectPath(nameSpace, className));
 
    result.setHost(hostName);

    return result;
}

CmpiInstance
CmpiBroker::makeCmpiInstance(const CmpiObjectPath &path)
{
    CMPIStatus status = { CMPI_RC_OK, NULL };
    
    CMPIInstance *inst = 
        _data->eft->newInstance(_data, path.toCMPI(), &status);

    if (status.rc != CMPI_RC_OK)
        throw CmpiStatus(&status);   

    return CmpiInstance(inst);
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
