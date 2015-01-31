/*******************************************************************************
*  COPYRIGHT   : (C) 2006 Bombardier Transportation
********************************************************************************
*  PROJECT     : IPTrain
*
*  MODULE      : mdcom.h
*
*  ABSTRACT    : Public header file for MDCom class, part of IPTCom.
*
********************************************************************************
*  HISTORY     :
*	
* $Id: mdcom.h 4861 2010-09-14 16:03:58Z bloehr $
*
*  Internal (Bernd Loehr, 2010-08-16) 
* 			Old obsolete CVS history removed
*
*
*******************************************************************************/

#ifndef MDCOM_H
#define MDCOM_H


/*******************************************************************************
*  INCLUDES
*/

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
*  DEFINES
*/
#define MD_URILEN    101   /* Maximum size of a URI string excluding termination */

#define ECHO_COMID   110  /* comid used for echo */

/* Return codes from method MDComAPI_getMsg(C) and getMsg(C++) */
#define MD_QUEUE_EMPTY     0 /* Queue is currently empty */
#define MD_QUEUE_NOT_EMPTY 1 /* Data was collected from the queue */

/* Message types used for the msgType of the structure MSG_INFO */
#define MD_MSGTYPE_DATA     0 /* A data message and no reply from receiver is expected */
#define MD_MSGTYPE_REQUEST  1 /* A request message and a reply from receiver is expected */
#define MD_MSGTYPE_RESPONSE 2 /* Response message on a previous send request message */
#define MD_MSGTYPE_RESULT   3 /* Result of communication */

/* Message result/error codes used for the resultCode of the structure MSG_INFO */
#define MD_SEND_OK            0 /* Correct acknowledge received */
#define MD_RECEIVE_OK         0 /* Expected number received */
#define MD_NO_ACK_RECEIVED   -1 /* No Acknowledge received */
#define MD_RESP_NOT_RECEIVED -2 /* Responses not received */
#define MD_RESP_MISSING      -3 /* All responses not received */
#define MD_SEND_FAILED       -4 /* Sending failed */
#define MD_NO_LISTENER       -5 /* No listener */
#define MD_NO_BUF_AVAILABLE  -6 /* No buffer/memory available */
#define MD_WRONG_DATA        -7 /* Wrong data, e.g. the receiver couldn't interpret the data */

/*******************************************************************************
*  TYPEDEFS
*/
typedef UINT32 MD_QUEUE;

typedef struct
{
   UINT32 comId;                /* ComID */
   UINT16 msgType;              /* Message type, MD_MSGTYPE_* */
   void *pCallerRef;            /* Caller reference */
   UINT32 sessionId;            /* Session identification */
   UINT32 srcIpAddr;            /* Source IP address */
   int    resultCode;           /* Communication result code */
   int    noOfResponses;        /* Number of responses */
   UINT16 userStatus;           /* User status from response msg */
   UINT32 responseTimeout;      /* Timeout for receiving response msg after sending of a request msg */
   UINT32 topoCnt;              /* Topo count value of received messages */
   char   destURI[MD_URILEN+1]; /* Destination URI string */
   char   srcURI[MD_URILEN+1];  /* Source URI string */
} MSG_INFO;


/* Function pointer to application call-back function */
typedef void (*IPT_REC_FUNCPTR) (const MSG_INFO *pMsgInfo,
                                 const char     *pData,
                                 UINT32         dataLength);

/*******************************************************************************
*  GLOBAL FUNCTIONS
*/

DLL_DECL int MDCom_prepareInit(void);
DLL_DECL void MDCom_process(void);
DLL_DECL void MDCom_destroy(void);

#ifdef TARGET_SIMU            

DLL_DECL int MDComAPI_putDataMsgSim(UINT32          comId,
                                    const char      *pData,
                                    UINT32          dataLength, 
                                    MD_QUEUE        callerQueue,
                                    IPT_REC_FUNCPTR func,
                                    const void      *pCallerRef,
                                    UINT32          topoCnt,
                                    UINT32          destId,
                                    const char      *pDestURI,
                                    const char      *pSrcURI,
                                    const char      *pSimUri);

DLL_DECL int MDComAPI_putMsgQSim(UINT32  comId,
                                 const char *pData,
                                 UINT32     dataLength, 
                                 MD_QUEUE   callerQueue,
                                 const void *pCallerRef,
                                 UINT32     topoCnt,
                                 const char *pDestURI,
                                 const char *pSrcURI,
                                 const char *pSimUri);

DLL_DECL int MDComAPI_putReqMsgSim(UINT32    comId,
                                   const char *pData,
                                   UINT32     dataLength,
                                   UINT16     noOfResponses,  
                                   UINT32     responseTimeout,
                                   MD_QUEUE   callerQueue,
                                   IPT_REC_FUNCPTR func,
                                   const void *pCallerRef,
                                   UINT32     topoCnt,
                                   UINT32     destId,
                                   const char *pDestURI,
	                                const char *pSrcURI,
	                                const char *pSimUri);

DLL_DECL int MDComAPI_putRequestMsgQSim(UINT32  comId,
                                        const char *pData,
                                        UINT32     DataLength,
                                        UINT16     NoOfResponses,  
                                        UINT32     ResponseTimeout,
                                        MD_QUEUE   CallerQueue,
                                        const void *pCallerRef,
                                        UINT32     topoCnt,
                                        const char *pDestURI,
                                        const char *pSrcURI,
                                        const char *pSimUri);

DLL_DECL int MDComAPI_putMsgFSim(UINT32          comId,
                                 const char      *pData,
                                 UINT32          dataLength, 
                                 IPT_REC_FUNCPTR func,
                                 const void      *pCallerRef,
                                 UINT32          topoCnt,
                                 const char      *pDestURI,
                                 const char      *pSrcURI,
                                 const char      *pSimUri);

DLL_DECL int MDComAPI_putRequestMsgFSim(UINT32          comId,
                                        const char      *pData,
                                        UINT32          DataLength,
                                        UINT16          NoOfResponses,  
                                        UINT32          ResponseTimeout,
                                        IPT_REC_FUNCPTR func,
                                        const void      *pCallerRef,
                                        UINT32          topoCnt,
                                        const char      *pDestURI,
                                        const char      *pSrcURI,
                                        const char      *pSimUri);

DLL_DECL int MDComAPI_putRespMsgSim(UINT32     comId,
                                    UINT16     userStatus,
                                    const char *pData,
                                    UINT32     dataLength,
                                    UINT32     sessionID,                          
                                    MD_QUEUE   callerQueue,
                                    IPT_REC_FUNCPTR func,
                                    const void *pCallerRef,
                                    UINT32     topoCnt,
                                    UINT32     destIpAddr,
                                    UINT32     destId,
                                    const char *pDestURI,
	                                 const char *pSrcURI,
	                                 const char *pSimUri);

DLL_DECL int MDComAPI_putResponseMsgSim(UINT32     comId,
                                        UINT16     userStatus,
                                        const char *pData,
                                        UINT32     dataLength,
                                        UINT32     sessionID,                          
                                        UINT32     topoCnt,
                                        UINT32     destIpAddr,
                                        const char *pDestURI,
                                        const char *pSrcURI,
                                        const char *pSimUri);

DLL_DECL int MDComAPI_putResponseMsgQSim(UINT32     comId,
                                         UINT16     userStatus,
                                         const char *pData,
                                         UINT32     dataLength,
                                         UINT32     sessionID,                          
                                         MD_QUEUE   callerQueue,
                                         const void *pCallerRef,
                                         UINT32     topoCnt,
                                         UINT32     destIpAddr,
                                         const char *pDestURI,
                                         const char *pSrcURI,
                                         const char *pSimUri);

DLL_DECL int MDComAPI_putResponseMsgFSim(UINT32         comId,
                                UINT16          userStatus,
                                const char      *pData,
                                UINT32          dataLength,
                                UINT32          sessionID,                          
                                IPT_REC_FUNCPTR func,
                                const void      *pCallerRef,
                                UINT32          topoCnt,
                                UINT32          destIpAddr,
                                const char      *pDestURI,
                                const char      *pSrcURI,
                                const char      *pSimUri);
#endif
   
   
DLL_DECL int MDComAPI_putDataMsg(UINT32          comId,
                                 const char      *pData,
                                 UINT32          dataLength, 
                                 MD_QUEUE        callerQueue,
                                 IPT_REC_FUNCPTR func,
                                 const void      *pCallerRef,
                                 UINT32          topoCnt,
                                 UINT32          destId,
                                 const char      *pDestURI,
                                 const char      *pSrcURI);

DLL_DECL int MDComAPI_putMsgQ(UINT32     comId,
                              const char *pData,
                              UINT32     dataLength, 
                              MD_QUEUE   callerQueue,
                              const void *pCallerRef,
                              UINT32     topoCnt,
                              const char *pDestURI,
                              const char *pSrcURI);

DLL_DECL int MDComAPI_putReqMsg(UINT32     comId,          
                                const char *pData,         
                                UINT32     dataLength,     
                                UINT16     noOfResponses,  
                                UINT32     responseTimeout,
                              
                                MD_QUEUE   callerQueue,    
                                IPT_REC_FUNCPTR func,      
                              
                                const void *pCallerRef,    
                                UINT32     topoCnt,        
                                UINT32     destId, 
                                const char *pDestURI,      
                              
                                const char *pSrcURI);
                                       
DLL_DECL int MDComAPI_putRequestMsgQ(UINT32    comId,
                                     const char *pData,
                                     UINT32     DataLength,
                                     UINT16     NoOfResponses,  
                                     UINT32     ResponseTimeout,
                                     MD_QUEUE   CallerQueue,
                                     const void *pCallerRef,
                                     UINT32     topoCnt,
                                     const char *pDestURI,
                                     const char *pSrcURI);
#ifndef LINUX_MULTIPROC
DLL_DECL int MDComAPI_putMsgF(UINT32          comId,
                              const char      *pData,
                              UINT32          dataLength, 
                              IPT_REC_FUNCPTR func,
                              const void      *pCallerRef,
                              UINT32          topoCnt,
                              const char      *pDestURI,
                              const char      *pSrcURI);

DLL_DECL int MDComAPI_putRequestMsgF(UINT32          comId,
                                     const char      *pData,
                                     UINT32          DataLength,
                                     UINT16          NoOfResponses,  
                                     UINT32          ResponseTimeout,
                                     IPT_REC_FUNCPTR func,
                                     const void      *pCallerRef,
                                     UINT32          topoCnt,
                                     const char      *pDestURI,
                                     const char      *pSrcURI);
#endif
DLL_DECL int MDComAPI_putRespMsg(UINT32     comId,
                                 UINT16     userStatus,
                                 const char *pData,
                                 UINT32     dataLength,
                                 UINT32     sessionID,                             
                                 MD_QUEUE   callerQueue, 
                                 IPT_REC_FUNCPTR func,   
                                 const void *pCallerRef, 
                                 UINT32     topoCnt, 
                                 UINT32     destIpAddr,
                                 UINT32     destId,
                                 const char *pDestURI,
                                 const char *pSrcURI);

DLL_DECL int MDComAPI_putResponseMsg(UINT32     comId,
                                     UINT16     userStatus,
                                     const char *pData,
                                     UINT32     dataLength,
                                     UINT32     sessionID,                          
                                     UINT32     topoCnt,
                                     UINT32     destIpAddr,
                                     const char *pDestURI,
                                     const char *pSrcURI);

DLL_DECL int MDComAPI_putResponseMsgQ(UINT32     comId,
                                      UINT16     userStatus,
                                      const char *pData,
                                      UINT32     dataLength,
                                      UINT32     sessionID,                          
                                      MD_QUEUE   callerQueue,
                                      const void *pCallerRef,
                                      UINT32     topoCnt,
                                      UINT32     destIpAddr,
                                      const char *pDestURI,
                                      const char *pSrcURI);
#ifndef LINUX_MULTIPROC
DLL_DECL int MDComAPI_putResponseMsgF(UINT32            comId,
                                      UINT16          userStatus,
                                      const char      *pData,
                                      UINT32          dataLength,
                                      UINT32          sessionID,                          
                                      IPT_REC_FUNCPTR func,
                                      const void      *pCallerRef,
                                      UINT32          topoCnt,
                                      UINT32          destIpAddr,
                                      const char      *pDestURI,
                                      const char      *pSrcURI);
#endif
DLL_DECL MD_QUEUE MDComAPI_createQueue(int noOfMsg);
DLL_DECL MD_QUEUE MDComAPI_queueCreate(int noOfMsg,
                                       const char *name);
DLL_DECL int MDComAPI_destroyQueue(MD_QUEUE queue);
DLL_DECL int MDComAPI_removeQueue(MD_QUEUE queue, UINT8 allUse);
DLL_DECL int MDComAPI_comIdListener(MD_QUEUE        listenerQueueId,
                                    IPT_REC_FUNCPTR func,
                                    const void      *pCallerRef,
                                    const UINT32    comid[],
                                    const void      *pRedFuncRef,
                                    UINT32          destId,
                                    const char      *pDestUri);
DLL_DECL int MDComAPI_addComIdListenerQ(MD_QUEUE     queue,
                                        const void   *pCallerRef,
                                        const UINT32 comid[]);
DLL_DECL int MDComAPI_uriListener(MD_QUEUE        listenerQueueId,
                                  IPT_REC_FUNCPTR func,           
                                  const void      *pCallerRef,    
                                  UINT32          comId,          
                                  UINT32          destId,         
                                  const char      *pDestUri,      
                                  const void      *pRedFuncRef);   
DLL_DECL int MDComAPI_addUriListenerQ(MD_QUEUE   listenerQueueId,
                                      const void *pCallerRef,
                                      const char *pDestURI);
DLL_DECL int MDComAPI_addFrgComIdListenerQ(MD_QUEUE     listenerQueueId,
                                           const void   *pCallerRef,    
                                           const UINT32 comid[],        
                                           const void   *pRedFuncRef);
DLL_DECL int MDComAPI_addFrgUriListenerQ(MD_QUEUE    listenerQueueId,
                                         const void  *pCallerRef,    
                                         const char  *pDestURI,      
                                         const void  *pRedFuncRef);  
                                        
DLL_DECL void MDComAPI_removeListenerQ(MD_QUEUE queue);
DLL_DECL int MDComAPI_removeComIdListenerQ(MD_QUEUE queue,
                                           const void  *pCallerRef,
                                           const UINT32 comid[]);  
DLL_DECL int MDComAPI_removeUriListenerQ(MD_QUEUE queue,
                                         const void  *pCallerRef,
                                         const char  *pDestURI);

#ifdef TARGET_SIMU
DLL_DECL int MDComAPI_comIdListenerSim(MD_QUEUE        listenerQueueId,
                                       IPT_REC_FUNCPTR func,
                                       const void      *pCallerRef,
                                       const UINT32    comid[],
                                       const void      *pRedFuncRef,
                                       UINT32          destId,
                                       const char      *pDestUri,
                                       const char   *pSimUri);
DLL_DECL int MDComAPI_addComIdListenerQSim(MD_QUEUE     queue,
                                           const void   *pCallerRef,
                                           const UINT32 comid[],
                                           const char   *pSimUri);
DLL_DECL int MDComAPI_uriListenerSim(MD_QUEUE        listenerQueueId,
                                     IPT_REC_FUNCPTR func,           
                                     const void      *pCallerRef,    
                                     UINT32          comId,          
                                     UINT32          destId,         
                                     const char      *pDestUri,      
                                     const void      *pRedFuncRef,   
                                     const char      *pSimUri);
DLL_DECL int MDComAPI_addUriListenerQSim(MD_QUEUE   listenerQueueId,
                                         const void *pCallerRef,
                                         const char *pDestURI,
                                         const char *pSimUri);
DLL_DECL int MDComAPI_addFrgComIdListenerQSim(MD_QUEUE     listenerQueueId,
                                              const void   *pCallerRef,    
                                              const UINT32 comid[],        
                                              const void   *pRedFuncRef,
                                              const char *pSimUri);
DLL_DECL int MDComAPI_addFrgUriListenerQSim(MD_QUEUE    listenerQueueId,
                                            const void  *pCallerRef,    
                                            const char  *pDestURI,      
                                            const void  *pRedFuncRef,
                                            const char  *pSimUri);  
                                        
DLL_DECL void MDComAPI_removeListenerQSim(MD_QUEUE queue,
                                          const char *pSimUri);
DLL_DECL int MDComAPI_removeComIdListenerQSim(MD_QUEUE queue,
                                              const void  *pCallerRef,
                                              const UINT32 comid[],
                                              const char  *pSimUri);  
DLL_DECL int MDComAPI_removeUriListenerQSim(MD_QUEUE queue,
                                            const void  *pCallerRef,
                                            const char  *pDestURI,
                                            const char  *pSimUri);
#endif

#ifndef LINUX_MULTIPROC
DLL_DECL int MDComAPI_addComIdListenerF(IPT_REC_FUNCPTR func,
                                        const void      *pCallerRef,
                                        const UINT32    comid[]);
DLL_DECL int MDComAPI_addUriListenerF(IPT_REC_FUNCPTR func,
                                      const void      *pCallerRef,
                                      const char      *pDestURI);
DLL_DECL int MDComAPI_addFrgComIdListenerF(IPT_REC_FUNCPTR func,       
                                           const void      *pCallerRef,
                                           const UINT32    comid[],    
                                           const void      *pRedFuncRef);  
DLL_DECL int MDComAPI_addFrgUriListenerF(IPT_REC_FUNCPTR func,       
                                         const void      *pCallerRef,
                                         const char      *pDestURI,  
                                         const void      *pRedFuncRef);  
DLL_DECL void MDComAPI_removeListenerF(IPT_REC_FUNCPTR func);
DLL_DECL int MDComAPI_removeComIdListenerF(IPT_REC_FUNCPTR func,
                                           const void      *pCallerRef,
                                           const UINT32    comid[]);   
DLL_DECL int MDComAPI_removeUriListenerF(IPT_REC_FUNCPTR func,
                                         const void      *pCallerRef,
                                         const char      *pDestURI);  
#ifdef TARGET_SIMU
DLL_DECL int MDComAPI_addComIdListenerFSim(IPT_REC_FUNCPTR func,
                                           const void      *pCallerRef,
                                           const UINT32    comid[],
                                           const char      *pSimUri);
DLL_DECL int MDComAPI_addUriListenerFSim(IPT_REC_FUNCPTR func,
                                         const void      *pCallerRef,
                                         const char      *pDestURI,
                                         const char      *pSimUri);
DLL_DECL int MDComAPI_addFrgComIdListenerFSim(IPT_REC_FUNCPTR func,       
                                              const void      *pCallerRef,
                                              const UINT32    comid[],    
                                              const void      *pRedFuncRef,
                                              const char      *pSimUri);  
DLL_DECL int MDComAPI_addFrgUriListenerFSim(IPT_REC_FUNCPTR func,       
                                            const void      *pCallerRef,
                                            const char      *pDestURI,  
                                            const void      *pRedFuncRef,
                                            const char      *pSimUri);  
DLL_DECL void MDComAPI_removeListenerFSim(IPT_REC_FUNCPTR func,
                                          const char *pSimUri);
DLL_DECL int MDComAPI_removeComIdListenerFSim(IPT_REC_FUNCPTR func,
                                              const void   *pCallerRef,
                                              const UINT32 comid[],
                                              const char   *pSimUri);   
DLL_DECL int MDComAPI_removeUriListenerFSim(IPT_REC_FUNCPTR func,
                                            const void  *pCallerRef,
                                            const char  *pDestURI,
                                            const char  *pSimUri);  
#endif
#endif
DLL_DECL int MDComAPI_unblockFrgListener(const void *pRedFuncRef);
DLL_DECL int MDComAPI_blockFrgListener(const void *pRedFuncRef);
DLL_DECL int MDComAPI_getMsg(MD_QUEUE queue,     
                             MSG_INFO *pMsgInfo,       
                             char     **ppData,       
                             UINT32   *pDataLength,
                             int      timeOut);     
DLL_DECL int MDComAPI_freeBuf(char *pBuf);
   
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
   /* Message data queue class, mostly in-line code */
   class DLL_DECL MDQueue
   {
   public:
      static MDQueue *createQueue(int noOfMsg);       
      static MDQueue *queueCreate(int noOfMsg, const char *name);       
      int destroyQueue(void);       
      int removeQueue(UINT8 allUse);       
      int getMsg(MSG_INFO *pMsgInfo, char **ppData, UINT32 *pDataLength, int timeout) 
      { return MDComAPI_getMsg(this->queue, pMsgInfo, ppData, pDataLength, timeout); }
      int freeBuf(char *pBuf);
     
      MD_QUEUE queue;      /* Queue handle returned by C method */


   private:
   };


   /* Message data communication class */ 
   class DLL_DECL MDCom
   {
   public:
      static void prepareInit(void) { (void) MDCom_prepareInit(); }
      static void process(void) { MDCom_process(); }
      static void terminate(void) { }
      ~MDCom(void) { MDCom_destroy(); }
   };

   /* Message data communication class */ 
   class DLL_DECL MDComAPI
   {
   public:
      static int comIdListener(const MDQueue *pQueue,
                               IPT_REC_FUNCPTR func,
                               const void    *pCallerRef,
                               const UINT32  comid[],
                               const void   *pRedFuncRef,
                               UINT32          destId,
                               const char      *pDestURI);
      static int uriListener(const MDQueue *pQueue,
                             IPT_REC_FUNCPTR func,        
                             const void    *pCallerRef,   
                             const UINT32  comId,         
                             UINT32        destId,      
                             const char    *pDestURI,   
                             const void    *pRedFuncRef);
      static int addListener(const MDQueue *pQueue,
                             const void    *pCallerRef,
                             const UINT32  comid[]);
      static int addListener(const MDQueue *pQueue,
                             const void    *pCallerRef,
                             const char    *pDestURI);
      static int addListener(const MDQueue *pQueue,    
                             const void   *pCallerRef, 
                             const UINT32 comid[],     
                             const void   *pRedFuncRef);
      static int addListener(const MDQueue *pQueue,    
                             const void  *pCallerRef,  
                             const char  *pDestURI,    
                             const void   *pRedFuncRef);
      static void removeListener(const MDQueue *pQueue);
      static int removeListener(const MDQueue *pQueue,
                                const void    *pCallerRef,
                                const UINT32  comid[]);
      static int removeListener(const MDQueue *pQueue,
                                const void    *pCallerRef,
                                const char    *pDestURI);
#ifndef LINUX_MULTIPROC
      static int addListener(IPT_REC_FUNCPTR func,
                             const void      *pCallerRef,
                             const UINT32    comid[]);
      static int addListener(IPT_REC_FUNCPTR func,
                             const void      *pCallerRef,
                             const char      *pDestURI);
      static int addListener(IPT_REC_FUNCPTR func, 
                             const void      *pCallerRef,
                             const UINT32    comid[],    
                             const void   *pRedFuncRef);  
      static int addListener(IPT_REC_FUNCPTR func,       
                             const void      *pCallerRef,
                             const char      *pDestURI,  
                             const void   *pRedFuncRef);  
      static void removeListener(IPT_REC_FUNCPTR func);
      static int removeListener(IPT_REC_FUNCPTR func,
                                const void      *pCallerRef,
                                const UINT32    comid[]);
      static int removeListener(IPT_REC_FUNCPTR func,
                                const void      *pCallerRef,
                                const char      *pDestURI);
#endif
      static int unblockFrgListener(const void *pRedFuncRef);
      static int blockFrgListener(const void *pRedFuncRef);
      static int putDataMsg(UINT32          comId,
                            const char      *pData,
                            UINT32          dataLength, 
                            const MDQueue *pCallerQueue,
                            IPT_REC_FUNCPTR func,
                            const void      *pCallerRef,
                            UINT32          topoCnt,
                            UINT32          destId,
                            const char      *pDestURI,
                            const char      *pSrcURI);
      static int putMsg(UINT32     comId,
                        const char *pData,
                        UINT32     dataLength);
      static int putMsg(UINT32        comId,
                        const char    *pData,
                        UINT32        dataLength, 
                        const MDQueue *pCallerQueue,
                        const void    *pCallerRef);
      static int putMsg(UINT32        comId,
                        const char    *pData,
                        UINT32        dataLength, 
                        const MDQueue *pCallerQueue,
                        const void    *pCallerRef,
                        UINT32        topoCnt);
      static int putMsg(UINT32        comId,
                        const char    *pData,
                        UINT32        dataLength, 
                        const MDQueue *pCallerQueue,
                        const void    *pCallerRef,
                        UINT32        topoCnt,
                        const char    *pDestURI);
      static int putMsg(UINT32        comId,
                        const char    *pData,
                        UINT32        dataLength, 
                        const MDQueue *pCallerQueue,
                        const void    *pCallerRef,
                        UINT32        topoCnt,
                        const char    *pDestURI,
                        const char    *pSrcURI);
#ifndef LINUX_MULTIPROC
      static int putMsg(UINT32          comId,
                        const char      *pData,
                        UINT32          dataLength, 
                        IPT_REC_FUNCPTR func,
                        const void      *pCallerRef);
      static int putMsg(UINT32          comId,
                        const char      *pData,
                        UINT32          dataLength, 
                        IPT_REC_FUNCPTR func,
                        const void      *pCallerRef,
                        UINT32          topoCnt);
      static int putMsg(UINT32          comId,
                        const char      *pData,
                        UINT32          dataLength, 
                        IPT_REC_FUNCPTR func,
                        const void      *pCallerRef,
                        UINT32          topoCnt,
                        const char      *pDestURI);
      static int putMsg(UINT32          comId,
                        const char      *pData,
                        UINT32          dataLength, 
                        IPT_REC_FUNCPTR func,
                        const void      *pCallerRef,
                        UINT32          topoCnt,
                        const char      *pDestURI,
                        const char      *pSrcURI);
#endif
      static int putReqMsg(UINT32     comId,           
                           const char *pData,          
                           UINT32     dataLength,      
                           UINT16     noOfResponses,   
                           UINT32     responseTimeout,  
                           const MDQueue *pCallerQueue,
                           IPT_REC_FUNCPTR func,       
                           const void *pCallerRef,     
                           UINT32     topoCnt,         
                           UINT32     destId,          
                           const char *pDestURI,
                           const char *pSrcURI);        
                               
      static int putRequestMsg(UINT32        comId,
                               const char    *pData,
                               UINT32        dataLength,
                               const MDQueue *pCallerQueue,
                               const void    *pCallerRef);
      static int putRequestMsg(UINT32        comId,
                               const char    *pData,
                               UINT32        dataLength,
                               UINT16        noOfResponses,
                               UINT32        responseTimeout, 
                               const MDQueue *pCallerQueue,
                               const void    *pCallerRef);
      static int putRequestMsg(UINT32        comId,
                               const char    *pData,
                               UINT32        dataLength,
                               UINT16        noOfResponses,
                               UINT32        responseTimeout, 
                               const MDQueue *pCallerQueue,
                               const void    *pCallerRef,
                               UINT32        topoCnt);
      static int putRequestMsg(UINT32        comId,
                               const char    *pData,
                               UINT32        dataLength,
                               UINT16        noOfResponses,
                               UINT32        responseTimeout, 
                               const MDQueue *pCallerQueue,
                               const void    *pCallerRef,
                               UINT32        topoCnt,
                               const char    *pDestURI);
      static int putRequestMsg(UINT32        comId,
                               const char    *pData,
                               UINT32        dataLength,
                               UINT16        noOfResponses,
                               UINT32        responseTimeout, 
                               const MDQueue *pCallerQueue,
                               const void    *pCallerRef,
                               UINT32        topoCnt,
                               const char    *pDestURI,
                               const char    *pSrcURI);
#ifndef LINUX_MULTIPROC
      static int putRequestMsg(UINT32          comId,
                               const char      *pData,
                               UINT32          dataLength,
                               IPT_REC_FUNCPTR func,
                               const void      *pCallerRef);
      static int putRequestMsg(UINT32          comId,
                               const char      *pData,
                               UINT32          dataLength,
                               UINT16          noOfResponses,
                               UINT32          responseTimeout, 
                               IPT_REC_FUNCPTR func,
                               const void      *pCallerRef);
      static int putRequestMsg(UINT32          comId,
                               const char      *pData,
                               UINT32          dataLength,
                               UINT16          noOfResponses,
                               UINT32          responseTimeout, 
                               IPT_REC_FUNCPTR func,
                               const void      *pCallerRef,
                               UINT32          topoCnt);
      static int putRequestMsg(UINT32          comId,
                               const char      *pData,
                               UINT32          dataLength,
                               UINT16          noOfResponses,
                               UINT32          responseTimeout, 
                               IPT_REC_FUNCPTR func,
                               const void      *pCallerRef,
                               UINT32          topoCnt,
                               const char      *pDestURI);
      static int putRequestMsg(UINT32          comId,
                               const char      *pData,
                               UINT32          dataLength,
                               UINT16          noOfResponses,
                               UINT32          responseTimeout, 
                               IPT_REC_FUNCPTR func,
                               const void      *pCallerRef,
                               UINT32          topoCnt,
                               const char      *pDestURI,
                               const char      *pSrcURI);
#endif
      static int putRespMsg(UINT32     comId,      
                            UINT16     userStatus, 
                            const char *pData,     
                            UINT32     dataLength, 
                            UINT32     sessionID,  
                            const MDQueue *pCallerQueue,
                            IPT_REC_FUNCPTR func,  
                            const void *pCallerRef,
                            UINT32     topoCnt,    
                            UINT32     destIpAddr, 
                            UINT32     destId,     
                            const char *pDestURI,  
                            const char *pSrcURI);   
                          
      static int putResponseMsg(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                UINT32     topoCnt,
                                UINT32     destIpAddr);
      static int putResponseMsg(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                UINT32     topoCnt,
                                const char *pDestURI);
      static int putResponseMsg(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                UINT32     topoCnt,
                                UINT32     destIpAddr,
                                const char *pSrcURI);
      static int putResponseMsg(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                UINT32     topoCnt,
                                const char *pDestURI,
                                const char *pSrcURI);
  
      static int putResponseMsgQ(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                const MDQueue *pCallerQueue,
                                const void    *pCallerRef,
                                UINT32     topoCnt,
                                UINT32     destIpAddr);
      static int putResponseMsgQ(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                const MDQueue *pCallerQueue,
                                const void    *pCallerRef,
                                UINT32     topoCnt,
                                const char *pDestURI);
      static int putResponseMsgQ(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                const MDQueue *pCallerQueue,
                                const void    *pCallerRef,
                                UINT32     topoCnt,
                                UINT32     destIpAddr,
                                const char *pSrcURI);
      static int putResponseMsgQ(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                const MDQueue *pCallerQueue,
                                const void    *pCallerRef,
                                UINT32     topoCnt,
                                const char *pDestURI,
                                const char *pSrcURI);

#ifndef LINUX_MULTIPROC
      static int putResponseMsgF(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                IPT_REC_FUNCPTR func,
                                const void    *pCallerRef,
                                UINT32     topoCnt,
                                UINT32     destIpAddr);
      static int putResponseMsgF(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                IPT_REC_FUNCPTR func,
                                const void    *pCallerRef,
                                UINT32     topoCnt,
                                const char *pDestURI);
      static int putResponseMsgF(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                IPT_REC_FUNCPTR func,
                                const void    *pCallerRef,
                                UINT32     topoCnt,
                                UINT32     destIpAddr,
                                const char *pSrcURI);
      static int putResponseMsgF(UINT32     comId,
                                UINT16     userStatus,
                                const char *pData,
                                UINT32     dataLength,
                                UINT32     sessionID,                          
                                IPT_REC_FUNCPTR func,
                                const void    *pCallerRef,
                                UINT32     topoCnt,
                                const char *pDestURI,
                                const char *pSrcURI);
#endif
   };

   /* MDComAPIException class */ 
   class DLL_DECL MDComAPIException
   {
      public:
         MDComAPIException ( INT32 errorCode, const char* fileName, UINT32 lineNumber ) : a_errorCode(errorCode),a_fileName(fileName),a_lineNumber(lineNumber) { }
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
