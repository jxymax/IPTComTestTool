/*******************************************************************************
*  COPYRIGHT   : (C) 2006 Bombardier Transportation
********************************************************************************
*  PROJECT     : IPTrain
*
*  MODULE      : pdcom.h
*
*  ABSTRACT    : Public header file for pdCom class, part of IPTCom.
*
********************************************************************************
*  HISTORY     :
*	
* $Id: pdcom.h 4861 2010-09-14 16:03:58Z bloehr $
*
*  Internal (Bernd Loehr, 2010-08-16) 
* 			Old obsolete CVS history removed
*
*
*******************************************************************************/

#ifndef PDCOM_H
#define PDCOM_H

/*******************************************************************************
*  INCLUDES
*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*  DEFINES
*/
#define PD_URILEN    255
typedef BYTE DataSet;     /* TODO Temp */

/* Return values for the parameter pInValid of the function PDComAPI_getWStatus*/
#define IPT_VALID 0                /* Data has been received and 
                                      the time-out has not expired */
#define IPT_INVALID_OLD 1          /* Data has been received but 
                                      the time-out has expired */
#define IPT_INVALID_NOT_RECEIVED 2 /* Data has never been received */

/*******************************************************************************
*  TYPEDEFS
*/
typedef UINT32 PD_HANDLE;

/*******************************************************************************
*  GLOBAL FUNCTIONS
*/
DLL_DECL PD_HANDLE PDComAPI_sub(UINT32 schedGrp, UINT32 comId, UINT32 filterId, const char *pSource, UINT32 destId, const char *pDest);
DLL_DECL PD_HANDLE PDComAPI_subscribe(UINT32 schedGrp, UINT32 comId, const char *source);
DLL_DECL PD_HANDLE PDComAPI_subscribeWfilter(UINT32 schedGrp, UINT32 comId, UINT32 filterId);
DLL_DECL int PDComAPI_renewSub(PD_HANDLE handle);
DLL_DECL PD_HANDLE PDComAPI_pub(UINT32 schedGrp, UINT32 comId, UINT32 destId, const char *dest);
DLL_DECL PD_HANDLE PDComAPI_publish(UINT32 schedGrp, UINT32 comId, const char *dest);
DLL_DECL PD_HANDLE PDComAPI_publishDef(UINT32 schedGrp, UINT32 comId, const char *dest);
DLL_DECL int PDComAPI_renewPub(PD_HANDLE handle);
DLL_DECL int PDComAPI_get(PD_HANDLE handle, BYTE *pBuffer, UINT16 bufferSize);
DLL_DECL int PDComAPI_getWStatus(PD_HANDLE handle, BYTE *pBuffer, UINT16 bufferSize, 
                        int  *pInValid);    
DLL_DECL void PDComAPI_put(PD_HANDLE handle, const BYTE *pBuffer);
DLL_DECL int PDComAPI_getStatistics(PD_HANDLE handle, BYTE *pBuffer, UINT16 *pBufferSize);
DLL_DECL void PDComAPI_unsubscribe(PD_HANDLE *pHandle);
DLL_DECL void PDComAPI_unpublish(PD_HANDLE *pHandle);
DLL_DECL void PDComAPI_sink(UINT32 schedGrp);
DLL_DECL void PDComAPI_source(UINT32 schedGrp);
DLL_DECL void PDComAPI_setRedundant(UINT32 leader);
DLL_DECL void PDComAPI_setRedundantId(UINT32 leader, UINT32 redId);

DLL_DECL int PDCom_prepareInit(void);
DLL_DECL void PDCom_process(void);
DLL_DECL void PDCom_destroy(void);

#ifdef TARGET_SIMU
DLL_DECL PD_HANDLE PDComAPI_pubSim(UINT32 schedGrp, UINT32 comId, UINT32 destId, const char *pDest, const char *pSimUri);
DLL_DECL PD_HANDLE PDComAPI_publishSim(UINT32 schedGrp, UINT32 comId, const char *pDest, const char *pSimUri);
DLL_DECL PD_HANDLE PDComAPI_publishDefSim(UINT32 schedGrp, UINT32 comId, const char *pDest, const char *pSimUri);
DLL_DECL PD_HANDLE PDComAPI_subSim(UINT32 schedGrp, UINT32 comId, UINT32 filterId, const char *pSource, UINT32 destId, const char *pDest, const char *pSimUri);

DLL_DECL PD_HANDLE PDComAPI_subscribeSim(UINT32 schedGrp, UINT32 comId, const char *pSource, const char *pSimUri);
DLL_DECL PD_HANDLE PDComAPI_subscribeWfilterSim(UINT32 schedGrp, UINT32 comId, UINT32 filterId, const char *pSimUri);
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/*******************************************************************************
*  CLASSES (C++)
*/
#ifdef IPTCOM_CM_COMPONENT
#include "tcms_co.h"
#endif
#include "iptcom.h"


/* Process data communication class */ 
class DLL_DECL PDCom
{
public:
   static void cycle(void) { PDCom_process(); }
   static void process(void) { PDCom_process(); }
   static void prepareInit(void) { (void) PDCom_prepareInit(); }
   static void terminate(void) { }
   ~PDCom(void) { PDCom_destroy(); }
};

/* Communication API class for PD, process data. */
class DLL_DECL PDComAPI
{
public:
   static PDComAPI *sub(UINT32 schedGrp, UINT32 comId, UINT32 filterId, char *src, UINT32 destId, char *dest);
   static PDComAPI *subscribe(UINT32 schedGrp, UINT32 comId, char *source);
   static PDComAPI *subscribeWfilter(UINT32 schedGrp, UINT32 comId, UINT32 filterId);
   static PDComAPI *pub(UINT32 schedGrp, UINT32 comId, UINT32 destId, char *dest);
   static PDComAPI *publish(UINT32 schedGrp, UINT32 comId, char *dest);
   static PDComAPI *publishDef(UINT32 schedGrp, UINT32 comId, char *dest);
   int renewSub(void);
   int renewPub(void);
   void put(DataSet *pBuffer);
   int get(DataSet *pBuffer, UINT16 bufferSize);
   int get(DataSet *pBuffer, UINT16 bufferSize, int *pInValid);
   int getStatistics(BYTE *pBuffer, UINT16 *pBufferSize);
   void unsubscribe(void);
   void unpublish(void);
   static void sink(UINT32 schedGrp) { PDComAPI_sink(schedGrp); }
   static void source(UINT32 schedGrp) { PDComAPI_source(schedGrp); }
   static void setRedundant(UINT32 leader) { PDComAPI_setRedundant(leader); }
   static void setRedundant(UINT32 leader, UINT32 redId) { PDComAPI_setRedundantId(leader, redId); }

private:
   PD_HANDLE handle;
};

/* PDComAPIException class */ 

class DLL_DECL PDComAPIException
{
   public:
      PDComAPIException ( INT32 errorCode, const char* fileName, UINT32 lineNumber ) : a_errorCode(errorCode),a_fileName(fileName),a_lineNumber(lineNumber) { }
      INT32 getErrorCode() const { return a_errorCode; }
      const char* getFileName() const { return a_fileName; }
      UINT32 getLineNumber() const { return a_lineNumber; }

   private:
      INT32 a_errorCode;
      const char *a_fileName;
      UINT32 a_lineNumber;
};

#endif

#endif
