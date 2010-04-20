#ifndef _CmpiMBService_h
#define _CmpiMBService_h

#include "CmpiCpp.h"
#include "Logger.h"

#define SMX_CONTEXT_TAG "smxupcall"
#define SMX_EXECUTIVE_TAG "smxexecutive"

namespace CmpiCpp 
{
   using namespace std;

   class CmpiMBService 
   {

   public:

     CmpiMBService( const CMPIBroker *broker, Logger &log);
      virtual ~CmpiMBService();

      CmpiInstance getInstance( const CmpiContext &context,
                                const CmpiObjectPath &path,
                                const char **properties);

      CmpiEnumeration enumInstanceNames(const CmpiContext &context,
                                        const CmpiObjectPath &path);

      CmpiEnumeration enumInstances(const CmpiContext &context,
                                    const CmpiObjectPath &path,
                                    const char **properties);

      CmpiData invokeMethod( const CmpiContext &context,
                             const CmpiObjectPath &path,
                             const CmpiName &method,
                             const CmpiArgs &in,
                             CmpiArgs &out);

      CMPIStatus deliverIndication( const CmpiContext & context,
                                    const CmpiName & nameSpace,
                                    const CmpiInstance &indication);

      bool classPathIsA( const CmpiObjectPath &path,
		         const string &parentClassName);

      static bool isUpCall( const CmpiContext & context);


   protected:

      const CMPIBroker *_broker; 
      Logger _log;
   };
};

#endif
