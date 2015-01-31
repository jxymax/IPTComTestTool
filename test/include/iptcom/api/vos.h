/*******************************************************************************
*  COPYRIGHT      : (c) 2006 Bombardier Transportation
********************************************************************************
*  PROJECT        : IPTrain
*
*  MODULE         : vos.h
*
*  ABSTRACT       : Virtual operating system (VOS) definitions
*
********************************************************************************
*  HISTORY     :
*	
* $Id: vos.h 5396 2012-02-10 17:24:11Z bloehr $
*
*  CR-3326 (Bernd Loehr, 2012-02-10)
*           Improvement for 3rd party use / Darwin port added.
*
*  CR-685 (Gerhard Weiss, 2010-08-24)
*           Add interlock mechanism during termination, ensuring no Memory is
*           freed before all threads are terminated.
*
*  Internal (Bernd Loehr, 2010-08-16) 
* 			Old obsolete CVS history removed
*
*
*******************************************************************************/
#ifndef VOS_H
#define VOS_H

/*******************************************************************************
* INCLUDES */

/* Windows XP */
#if defined(WIN32)

/* Mac OS X (BSD) */
#elif defined(DARWIN)
#include <semaphore.h>
#include <pthread.h>

/* LINUX */
#elif defined(LINUX)
#include <semaphore.h>
#include <pthread.h>

/* VXWORKS */
#elif defined(VXWORKS)

/* INTEGRITY */
#elif defined(__INTEGRITY)

#endif


#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* DEFINES */
   

/* Windows XP */
#if defined(WIN32)
#define IPTVOS_MAX_MAILSLOT_NAME 80
#define THREAD_METHOD static  /* Threds functions in Windows must be declared static */

/* LINUX */
#elif defined(LINUX) || defined(DARWIN)
#define FAR
#define THREAD_METHOD

/* VXWORKS */
#elif defined(VXWORKS)
#define FAR
#define THREAD_METHOD

/* INTEGRITY */
#elif defined(__INTEGRITY)
#define FAR
#define THREAD_METHOD
#endif

/* Trace output mask used together with setting iptDebugMask and in call of
   IPTVosGetPrintMask and IPTVosSetPrintMask.*/
#define IPT_VOS         0x0001               /* Vos         */
#define IPT_NETDRIVER   0x0002               /* Netdriver   */
#define IPT_PD          0x0004               /* PD          */
#define IPT_MD          0x0008               /* MD          */
#define IPT_CONFIG      0x0010               /* Configuration */
#define IPT_OTHER       0x0020               /* Other       */
#define IPT_WARN        0x4000               /* Warning     */
#define IPT_ERR         0x8000               /* Error       */
#define IPT_ALL         0xffff               /* Show everything */

/* Debug printout, warning and error macros */
   
#define IPTVosPrint0(cat, fmt)                      IPTVosPrint(cat,fmt,0,0,0,0,0,0,0)
#define IPTVosPrint1(cat, fmt, a)                   IPTVosPrint(cat,fmt,a,0,0,0,0,0,0)
#define IPTVosPrint2(cat, fmt, a, b)                IPTVosPrint(cat,fmt,a,b,0,0,0,0,0)
#define IPTVosPrint3(cat, fmt, a, b, c)             IPTVosPrint(cat,fmt,a,b,c,0,0,0,0)
#define IPTVosPrint4(cat, fmt, a, b, c, d)          IPTVosPrint(cat,fmt,a,b,c,d,0,0,0)
#define IPTVosPrint5(cat, fmt, a, b, c, d, e)       IPTVosPrint(cat,fmt,a,b,c,d,e,0,0)
#define IPTVosPrint6(cat, fmt, a, b, c, d, e, f)    IPTVosPrint(cat,fmt,a,b,c,d,e,f,0)
#define IPTVosPrint7(cat, fmt, a, b, c, d, e, f, g) IPTVosPrint(cat,fmt,a,b,c,d,e,f,g)
	
#define IPTVosRawPrint0(cat, fmt)                      IPTVosRawPrint(cat,fmt,0,0,0,0,0,0,0)
#define IPTVosRawPrint1(cat, fmt, a)                   IPTVosRawPrint(cat,fmt,a,0,0,0,0,0,0)
#define IPTVosRawPrint2(cat, fmt, a, b)                IPTVosRawPrint(cat,fmt,a,b,0,0,0,0,0)
#define IPTVosRawPrint3(cat, fmt, a, b, c)             IPTVosRawPrint(cat,fmt,a,b,c,0,0,0,0)
#define IPTVosRawPrint4(cat, fmt, a, b, c, d)          IPTVosRawPrint(cat,fmt,a,b,c,d,0,0,0)
#define IPTVosRawPrint5(cat, fmt, a, b, c, d, e)       IPTVosRawPrint(cat,fmt,a,b,c,d,e,0,0)
#define IPTVosRawPrint6(cat, fmt, a, b, c, d, e, f)    IPTVosRawPrint(cat,fmt,a,b,c,d,e,f,0)
#define IPTVosRawPrint7(cat, fmt, a, b, c, d, e, f, g) IPTVosRawPrint(cat,fmt,a,b,c,d,e,f,g)

#define DBG_POSITION (char *) (char *) __FILE__, (UINT16) __LINE__

/* used to select the information shown note prefix INF_ must be 4 chars */
#define INF_DATETIME    0x0008              /* show date and time        */
#define INF_CATEGORY    0x0004              /* show category             */
#define INF_LINE        0x0002              /* show line number          */
#define INF_FILE        0x0001              /* show file name            */
#define INF_ALL         0xffff              /* show all                  */

/* the extra parameter filters the amount of printouts (higer value more info */
#define IPTVosPrint(cat, fmt, p1, p2, p3, p4, p5, p6, p7) \
if(cat & iptDebugMask) \
   IPTVosDPrint(0, DBG_POSITION,(cat),(fmt),(int)(p1),(int)(p2),(int)(p3),(int)(p4),(int)(p5),(int)(p6),(int)(p7))

#define IPTVosRawPrint(cat, fmt, p1, p2, p3, p4, p5, p6, p7) \
if(cat & iptDebugMask) \
   IPTVosDPrint(1, DBG_POSITION,(cat),(fmt),(int)(p1),(int)(p2),(int)(p3),(int)(p4),(int)(p5),(int)(p6),(int)(p7))

/*******************************************************************************
* TYPEDEFS */
/* Windows XP */
#if defined(WIN32)

#define HANDLE void *

typedef HANDLE IPT_SEM;          /* Semaphore definition */
typedef void *VOS_THREAD_ID;     /* Thread identity      */
/* VOS_STARTER_TYPE is found below defined section */
typedef void ( __cdecl *IPT_THREAD_ROUTINE) (void *pArg);

typedef struct iptqueuetype
{
   wchar_t mailSlotName[IPTVOS_MAX_MAILSLOT_NAME];
   HANDLE hMailSlot;       /* Mailslot handle */
   HANDLE hFile;           /* File handle */
   int maxNoMsg;           /* Maximum no of messages size  */
   int noOfItemsInQueue;   /* Number of items in the queue */
} IPT_QUEUE_TYPE, *IPT_QUEUE;

/* LINUX */
#elif defined(LINUX) || defined(DARWIN)

#ifdef LINUX_MULTIPROC
typedef int IPT_SEM;

#else
typedef struct 
{
   pthread_mutex_t   mutex;
   pthread_cond_t    condition;
   int         semCount;   
} IPT_SEM;                       /* Semaphore definition */
#endif

typedef int IPT_QUEUE;
typedef pthread_t VOS_THREAD_ID; /* Thread identity      */
typedef void (*IPT_THREAD_ROUTINE) (void *pArg);

/* VXWORKS */
#elif defined(VXWORKS)
typedef void *IPT_SEM;           /* Semaphore definition */
typedef void *IPT_QUEUE;         /* Queue definition */
typedef int  VOS_THREAD_ID;      /* Thread identity      */
typedef void (*IPT_THREAD_ROUTINE) (void *pArg);

/* INTEGRITY */
#elif defined(__INTEGRITY)
typedef void* IPT_SEM;           /* Semaphore definition */
typedef void *IPT_QUEUE;         /* Queue definition */
typedef int  VOS_THREAD_ID;      /* Thread identity      */
typedef void (*IPT_THREAD_ROUTINE) (void *pArg);
#endif

typedef enum {IPT_SEM_EMPTY, IPT_SEM_FULL} IPT_SEM_STATE;


/*******************************************************************************
* GLOBALS */

DLL_DECL extern UINT16 iptDebugMask;                     /* Debug categorys  */

/*******************************************************************************
* GLOBAL FUNCTIONS */

/* Trace functions */
DLL_DECL UINT16 IPTVosGetPrintMask(void);
DLL_DECL void IPTVosSetPrintMask(UINT16 newPrintMask);
DLL_DECL UINT16 IPTVosGetInfoMask(void);
DLL_DECL void IPTVosSetInfoMask(UINT16 newInfoMask);
DLL_DECL int IPTVosGetLogFileSize(void);
DLL_DECL void IPTVosSetLogFileSize(int size);

/* Console */
DLL_DECL void IPTVosDPrint(int DebugSettingsOveride, char* pFileId, UINT16 lineNr,UINT16 category, 
						const char *fmt, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);
DLL_DECL void IPTVosDFile(	char* pFileName);

/* Memory */
DLL_DECL BYTE *IPTVosMalloc(UINT32 size);
/*lint -sem(IPTVosFree, custodial(1))*/
DLL_DECL int IPTVosFree(const BYTE *p);
DLL_DECL UINT32 IPTVosMemAllocCnt(void);
DLL_DECL void IPTVosMemShow(void);
DLL_DECL int IPTVosMemIsPtr(BYTE *p);

/* Semaphores */
DLL_DECL int  IPTVosCreateSem(IPT_SEM *hSem, IPT_SEM_STATE InitialState);
DLL_DECL void IPTVosDestroySem(IPT_SEM *hSem);
DLL_DECL int  IPTVosGetSem(IPT_SEM *hSem, int timeOutInMs);
DLL_DECL void IPTVosPutSem(IPT_SEM *hSem);


/* Queues */
DLL_DECL int IPTVosCreateMsgQueue(IPT_QUEUE *pQueueID, int maxNoMsg,int maxLength); 
DLL_DECL int IPTVosDestroyMsgQueue(IPT_QUEUE *pQueueID);
DLL_DECL int IPTVosSendMsgQueue(IPT_QUEUE *pQueueID,char *msg,unsigned int size); 
DLL_DECL int IPTVosReceiveMsgQueue(IPT_QUEUE *pQueueID, char *pMsg, unsigned int size,int timeout);


/* Threads */
DLL_DECL VOS_THREAD_ID IPTVosThreadSpawn(char *pName, int Policy, int Priority, int StackSize, 
                    IPT_THREAD_ROUTINE TheFunction, void *pArguments);
DLL_DECL void IPTVosRegisterCyclicThread(void (*pFunc)(void), char *pName, int interval,
                                int policy, int priority, int stackSize);
DLL_DECL void IPTVosThreadTerminate(void);    
DLL_DECL void IPTVosThreadDone(void);
    
DLL_DECL void IPTVosTaskDelay(int DelayInMs);

DLL_DECL unsigned long IPVosGetSecTimer(void);
DLL_DECL UINT32 IPTVosGetMilliSecTimer(void);
DLL_DECL UINT32 IPTVosGetMicroSecTimer(void);
DLL_DECL UINT32 IPTVosGetUniqueNumber(void);

#ifdef __cplusplus
}
#endif

#endif /* VOS_H */
