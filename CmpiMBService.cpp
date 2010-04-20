#include "CmpiMBService.h"
#include "CmpiCppClient.h"

using namespace CmpiCpp;

CmpiMBService::CmpiMBService( const CMPIBroker *broker, Logger &log)
  : _log(log)
{
   _broker = broker;
};

CmpiMBService::~CmpiMBService()
{

};

CmpiInstance CmpiMBService::getInstance( const CmpiContext &context,
                                         const CmpiObjectPath &path,
                                         const char **properties)
{
   _log.info("[upcall] getInstance(%s)", path.str().c_str());

   CmpiCppClient *client = makeCmpiCppClient(_broker);

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
     CMPIValue val;
     context.toCMPI()->ft->addEntry( context.toCMPI(), SMX_CONTEXT_TAG , &val, CMPI_uint8);
   
     CMPIInstance *ci = _broker->bft->getInstance( _broker, context.toCMPI(), cop, properties, &st);

     if (st.rc!=CMPI_RC_OK) {
       CmpiStatus s(&st);
       _log.info("[upcall] getInstance() exception: %s", s.str().c_str());
       throw s;
     }

     _log.info("[upcall] returned from getInstance()");
     return CmpiInstance( ci);
   }
};

CmpiEnumeration
CmpiMBService::enumInstanceNames(const CmpiContext &context,
				 const CmpiObjectPath &path)
{
   _log.info("[upcall] enumInstanceNames(%s)", path.str().c_str());

   CMPIEnumeration *en;

   CMPIStatus st = { CMPI_RC_OK, NULL };
   CMPIObjectPath * cop = path.toCMPI();
   CMPIValue val;
   context.toCMPI()->ft->addEntry( context.toCMPI(), SMX_CONTEXT_TAG, &val, CMPI_uint8);
   
   en = _broker->bft->enumInstanceNames(_broker, context.toCMPI(), cop, &st);
   
   if (st.rc != CMPI_RC_OK) {
     CmpiStatus s(&st);
     _log.info("[upcall] enumInstanceNames() exception: %s", s.str().c_str());
     throw s;
   }

   _log.info("[upcall] returned from enumInstanceNames()");
   return CmpiEnumeration(en);
};


CmpiEnumeration 
CmpiMBService::enumInstances(const CmpiContext &context,
                             const CmpiObjectPath &path,
                             const char **properties)
{
   _log.info("[upcall] enumInstances(%s)", path.str().c_str());

   CmpiCppClient *client = makeCmpiCppClient(_broker);

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
     CMPIValue val;
     context.toCMPI()->ft->addEntry( context.toCMPI(), SMX_CONTEXT_TAG, &val, CMPI_uint8);
   
     en = _broker->bft->enumInstances(_broker, context.toCMPI(), cop, properties, &st);
   
     if (st.rc != CMPI_RC_OK) {
       CmpiStatus s(&st);
       _log.info("[upcall] enuminstances() exception: %s", s.str().c_str());
       throw s;
     }

     _log.info("[upcall] returned from enumInstances()");
     return CmpiEnumeration(en);
   }
};


CmpiData 
CmpiMBService::invokeMethod( const CmpiContext &context,
                             const CmpiObjectPath &path,
                             const CmpiName &method,
                             const CmpiArgs &in,
                             CmpiArgs &out)
{
   // Calling CmpiObjectPath.str() allocates memory and causes a leak in the 
   // executive so avoid this.

   CMPIStatus cst = { CMPI_RC_OK, NULL };

   context.toCMPI()->ft->getEntry(context.toCMPI(), SMX_EXECUTIVE_TAG, &cst);

   if (cst.rc == CMPI_RC_OK)
      _log.info("[upcall] invokeMethod(path=BLOCKED, method=\"%s\")", method.c_str());
   else
      _log.info("[upcall] invokeMethod(path=%s, method=\"%s\")",
		path.str().c_str(), method.c_str());
   
   CMPIData data;

   CMPIStatus st = { CMPI_RC_OK, NULL };
   CMPIObjectPath * cop = path.toCMPI();
   CMPIValue val;
   context.toCMPI()->ft->addEntry( context.toCMPI(), SMX_CONTEXT_TAG , &val, CMPI_uint8);
     
   data = _broker->bft->invokeMethod( _broker, 
                                      context.toCMPI(), 
                                      cop, 
                                      method.str().c_str(),
                                      in.toCMPI(),
                                      out.toCMPI(),
                                      &st);
   
   if (st.rc != CMPI_RC_OK) {
     CmpiStatus s(&st);
     _log.info("[upcall] invokeMethod() exception: %s", s.str().c_str());
     throw s;
   }

   _log.info("[upcall] returned from invokeMethod()");

   CMPIData *dataPtr = &data;
   return CmpiData( dataPtr);
};

CMPIStatus 
CmpiMBService::deliverIndication( const CmpiContext & context,
                                  const CmpiName & nameSpace,
                                  const CmpiInstance &indication)
{
   _log.info("[upcall] deliverIndication(%s)", 
             indication.getPath().str().c_str());

   CMPIStatus st = _broker->bft->deliverIndication(_broker, 
                                                   context.toCMPI(), 
                                                   nameSpace.str().c_str(), 
                                                   indication.toCMPI());
   
   if (st.rc != CMPI_RC_OK) {
     CmpiStatus s(&st);
     _log.info("[upcall] deliverIndication() exception: %s", s.str().c_str());
     throw s;
   }

   _log.info("[upcall] returned from deliverIndication");

   return st;
};

bool CmpiMBService::classPathIsA( const CmpiObjectPath &path,
                                  const string &parentClassName)
{
   _log.info("classPathIsA(%s)", path.str().c_str());

   CMPIStatus st = { CMPI_RC_OK, NULL };
   CMPIObjectPath * cop = path.toCMPI();
   
   CMPIBoolean isa = CMClassPathIsA(_broker, cop, parentClassName.c_str(), &st);

   if (st.rc!=CMPI_RC_OK) {
     CmpiStatus s(&st);
     _log.info("classPathIsA() exception: %s", s.str().c_str());
     throw s;
   }

   _log.info("returned from classPathIsA()");
   return bool(isa);
};

bool CmpiMBService::isUpCall( const CmpiContext &context)
{
   CMPIStatus cst = { CMPI_RC_OK, NULL };
   context.toCMPI()->ft->getEntry( context.toCMPI(), SMX_CONTEXT_TAG, &cst);
   if ( cst.rc == CMPI_RC_OK)
      return true;
   else
      return false;
};
