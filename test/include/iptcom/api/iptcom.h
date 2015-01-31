/*******************************************************************************
*  COPYRIGHT   : (C) 2006-2010 Bombardier Transportation
********************************************************************************
*  PROJECT     : IPTrain
*
*  MODULE      : iptcom.h
*
*  ABSTRACT    : Public header file for IPTCom class
*
********************************************************************************
*  HISTORY     :
*	
* $Id: iptcom.h 5455 2012-04-12 07:14:19Z gweiss $
*
*  CR-1356 (Bernd Loehr, 2010-10-08)
* 			Additional function iptConfigAddDatasetExt to define dataset
*			dependent un/marshalling.
*
*  CR-62 (Bernd Loehr, 2010-08-25)
* 			Additional function IPTCom_handleEvent() to renew all MC
* 			memberships after link down/up event.
*			Defines for events added.
*
*******************************************************************************/

#ifndef IPTCOM_H
#define IPTCOM_H


/*******************************************************************************
*  INCLUDES
*/
#if defined(O_CSS)
 #include <rts_api.h>
 #ifndef VXWORKS
  #define VXWORKS
 #endif
 #define FILE OS_IO_FILE
#else
   #include <stdio.h>
#endif

#include "ipt.h"     /* Common type definitions for IPT */
#include "mdcom.h"
#include "pdcom.h"


#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
*  DEFINES
*/
/* IPTCom version information */
#define IPT_VERSION			3
#define IPT_RELEASE			12
#define IPT_UPDATE			1
#define IPT_EVOLUTION      0

/* IPTCom status information returned from IPTCom_getStatus */
#define IPTCOM_RUN                0
#define IPTCOM_TDC_NOT_CONFIGURED 1
#define IPTCOM_NOT_INITIATED      2

/* IPTCom event selectors for IPTCom_handleEvent */
#define IPTCOM_EVENT_NONE         0		/* pArg is ignored	*/
#define IPTCOM_EVENT_LINK_UP      1		/* pArg is ignored	*/

/* Default file name for XML configuration file.
   Used in C++ implementations and for CSS */
#define IPT_XML_CONFIG_FILENAME  "ipt_config.xml"

/* Default file name for TDC host simulation file */
#define IPT_TDC_SIM_HOST_FILENAME  "tdchosts"

/* Maximum size of file name and path */
#define IPT_SIZE_OF_FILEPATH 255

/* Default com-parameter-id */
#define IPT_DEF_COMPAR_PD_ID     1     /* Default com-parameter-id for PD */
#define IPT_DEF_COMPAR_MD_ID     2     /* Default com-parameter-id for MD */

#define IPT_INVALID_ZERO         0     /* Zero value if invalid */
#define IPT_INVALID_KEEP         1     /* Keep value if invalid */

#define MAX_FORMAT_LEVEL         5     /* Max levels in dataset formatting (for recursion) */

/* Time-out values */
#define IPT_NO_WAIT       0
#define IPT_WAIT_FOREVER -1

/* Default memory pool size */
#define IPTCOM_MEMORY_DEFAULT 0x400000
   
/* Datatypes for id in configuration dataset formatting table */
#define IPT_BOOLEAN1    -1       /* Kept for backward compatibility, replaced by  IPT_BOOLEAN8 */
#define IPT_BOOLEAN8    -1
#define IPT_CHAR8       -2
#define IPT_UNICODE16   -3
#define IPT_INT8        -4
#define IPT_INT16       -5
#define IPT_INT32       -6
#define IPT_UINT8       -7
#define IPT_UINT16      -8
#define IPT_UINT32      -9
#define IPT_REAL32      -10
#define IPT_STRING      -11
#define IPT_ARRAY       -12
#define IPT_RECORD      -13
#define IPT_INT64       -14
#define IPT_UINT64      -15
#define IPT_TIMEDATE48  -16
#define IPT_MAX_TYPE    -16
   
#define IPT_VAR_SIZE          0        /* Size to indicate variable size */

#define IPT_DS_NOT_PREPARED   0  /* Dataset not prepared */
#define IPT_DS_FIX_SIZE       1  /* Dataset calculated, fix size */
#define IPT_DS_VAR_SIZE       2  /* Dataset calculated, variable size */

/* Error code: type definitions */
#define TYPE_WARNING    0x40000000
#define TYPE_ERROR      0x80000000
#define TYPE_EXCEPTION  0xc0000000

/* Error code: IPTCom function definitions */
#define ERR_IPTVCOM     0x00030000
#define IPTCOM_COINST	0
#define IPTCOM_COID		3
#define ERR_TDCCOM      0x00040000

/* Error code: global/local definitions */
#define ERR_LOCAL       0x00008000

#define isException(res)  ((res & TYPE_EXCEPTION) == TYPE_EXCEPTION)

/* Error codes */
#define IPT_OK                             0  /* General OK value */
#define IPT_ERROR                         (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x65)  /* General error value */

#define IPT_NOT_FOUND                     (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x66)  /* Item was not found */
#define IPT_ILLEGAL_SIZE                  (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x67)  /* Illegal size */
#define IPT_FCS_ERROR                     (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x68)  /* Frame Check Sequence error */
#define IPT_MEM_ERROR                     (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x69)  /* Out of memory */
#define IPT_PARSE_ERROR                   (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x6A)  /* Error during parsing of XML file */
#define IPT_MARSHALL_ERROR                (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x6B)  /* Error during marshalling */
#define IPT_MARSHALL_MAX_LEVEL            (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x6C)  /* Reached max level of recursion during marshalling */
#define IPT_MARSHALL_UNKNOWN_DATASETID    (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x6D)  /* Dataset ID unknown */
#define IPT_MARSHALL_TOO_BIG              (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x6E)  /* Attempt to write outside boundary */
#define IPT_ENDIAN_ALIGNMENT_ERROR        (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x6F)  /* This device does not work as expected concerning alignment or endian */
#define IPT_TAB_ERR_INIT                  (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x70)  /* Table not initialized */
#define IPT_TAB_ERR_NOT_FOUND             (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x71)  /* Item was not found */
#define IPT_TAB_ERR_ILLEGAL_SIZE          (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x72)  /* Illegal size */
#define IPT_TAB_ERR_EXISTS                (TYPE_ERROR     | ERR_IPTVCOM | ERR_LOCAL | 0x73)  /* Item alreade exists with different parameters*/
#define IPT_SEM_ERR                       (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x74)  /* Semaphore error */
#define IPT_MEM_ILL_RETURN                (TYPE_ERROR     | ERR_IPTVCOM | ERR_LOCAL | 0x75)  /* Return of memory not previously allocated */
#define IPT_QUEUE_ERR                     (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x76)  /* Queue error */
#define IPT_QUEUE_IN_USE                  (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x77)  /* Attempt to destroy a queue in use */
#define IPT_TDC_NOT_READY                 (TYPE_WARNING   | ERR_IPTVCOM | ERR_LOCAL | 0x78)  /* TDC is waiting for configuration from IPTDir */
#define IPT_ERR_NO_IPADDR                 (TYPE_ERROR     | ERR_IPTVCOM | ERR_LOCAL | 0x79)  /* Own IP address not found */
#define IPT_ERR_NO_ETH_IF                 (TYPE_WARNING   | ERR_IPTVCOM | ERR_LOCAL | 0x80)  /* Ethernet interface not initiated */

#define IPT_INVALID_PAR                   (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0xC9)  /* Invalid parameters */
#define IPT_INVALID_COMPAR                (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0xCA)  /* Invalid communication parameters */
#define IPT_INVALID_DATA                  (TYPE_WARNING   | ERR_IPTVCOM | ERR_LOCAL | 0xCB)  /* Invalid application data, e.g. no data */
#define IPT_MD_NOT_INIT                   (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0xCC)  /* MD communication not initiated */
#define IPT_WRONG_TOPO_CNT                (TYPE_ERROR     | ERR_IPTVCOM | ERR_LOCAL | 0xCD)  /* Current topo counter not equal to application topo counter*/

/* Net driver error codes */
#define IPT_ERR_INIT_DRIVER_FAILED        (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x12D)  /* Method call to init driver failed */
#define IPT_ERR_EXIT_DRIVER_FAILED        (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x12E)  /* Method call to exit driver failed */
#define IPT_ERR_DRIVER_ALREADY_STARTED    (TYPE_WARNING   | ERR_IPTVCOM | ERR_LOCAL | 0x12F)  /* Driver is already open */
#define IPT_ERR_DRIVER_ALREADY_CLOSED     (TYPE_WARNING   | ERR_IPTVCOM | ERR_LOCAL | 0x130)  /* Driver is already closed */
#define IPT_ERR_MD_SOCKET_CREATE_FAILED   (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x131)  /* Could not create MD socket */
#define IPT_ERR_MD_SOCKET_BIND_FAILED     (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x132)  /* Could not bind MD socket */
#define IPT_ERR_PD_SOCKET_CREATE_FAILED   (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x133)  /* Could not create PD socket */
#define IPT_ERR_PD_SOCKET_BIND_FAILED     (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x134)  /* Could not bind PD socket */
#define IPT_ERR_SEM_CREATE_FAILED         (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x135)  /* Could not create semaphore */
#define IPT_ERR_PD_SOCKOPT_FAILED         (TYPE_ERROR     | ERR_IPTVCOM | ERR_LOCAL | 0x136)  /* SetSockOpt for PD socket failed */
#define IPT_ERR_MD_SOCKOPT_FAILED         (TYPE_ERROR     | ERR_IPTVCOM | ERR_LOCAL | 0x137)  /* SetSockOpt for MD socket failed */
#define IPT_ERR_MD_SENDTO_FAILED          (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x138)  /* Sendto on MD socket failed */
#define IPT_ERR_SNMP_SENDTO_FAILED        (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x139)  /* Sendto on SNMP socket failed */
#define IPT_ERR_PD_SENDTO_FAILED          (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x140)  /* Sendto on PD socket failed */
#define IPT_ERR_SNMP_SOCKET_CREATE_FAILED (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x141)  /* Could not create SNMP socket */
#define IPT_ERR_SNMP_SOCKET_BIND_FAILED   (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x142)  /* Could not bind SNMP socket */

/* Simulation error codes */
#define IPT_SIM_ERR_PCAP_IFOPEN           (TYPE_EXCEPTION | ERR_IPTVCOM | ERR_LOCAL | 0x300)  /* PCap could not access/open interface */   

/* Statistics definitions */
#define IPT_STAT_STRING_LEN   255  /* Max no of characters in an octet string */
#define IPT_STAT_OID_LEN      30   /* Max no of parts in an OID including room for a stopper */
#define IPT_STAT_OID_STOPPER  0xffffffff  /* OID array stopper */
#define MAX_OID_NAME          30   /* Maximum length of OID name */

/* Access types for statistic structure IPT_OID_DATA */
#define IPTCOM_STAT_DATA_STRUCT    1

#define IPTCOM_STAT_DATA_PTR_R     2
#define IPTCOM_STAT_FUNC_NOKEY_R   3
#define IPTCOM_STAT_FUNC_KEY_R     4

#define IPTCOM_STAT_DATA_PTR_W     5
#define IPTCOM_STAT_FUNC_NOKEY_W   6
#define IPTCOM_STAT_FUNC_KEY_W     7

#define IPTCOM_STAT_DATA_PTR_RW    8 
#define IPTCOM_STAT_FUNC_NOKEY_RW  9 
#define IPTCOM_STAT_FUNC_KEY_RW   10

/* Statistics Data types for statistic structure IPT_OID_DATA */
#define IPT_STAT_TYPE_NULL         0
#define IPT_STAT_TYPE_INTEGER      1
#define IPT_STAT_TYPE_OCTET_STRING 2
#define IPT_STAT_TYPE_OID          3
#define IPT_STAT_TYPE_IPADDRESS    4
#define IPT_STAT_TYPE_COUNTER      5
#define IPT_STAT_TYPE_TIMETICKS    6

/* SNMP and OID definitions */
#define IPT_OID_ENTERPRISE_DIG  18910
#define IPT_OID_ENTERPRISE_NAME "Bombardier"
#define IPT_OID_BTROOT_DIG      3
#define IPT_OID_BTROOT_NAME     "btProduct"
#define IPT_OID_BTPRODUCT_DIG   1
#define IPT_OID_BTPRODUCT_NAME  "onBoard"
#define IPT_OID_ONBOARD_DIG     5
#define IPT_OID_ONBOARD_NAME    "COM"
#define IPT_OID_COM_DIG         1
#define IPT_OID_COM_NAME        "IPTCom"

#define IPT_START_OID         {1, 3, 6, 1, 4, 1, 18910}

#define MAX_IPTCOM_OID (IPT_STAT_OID_LEN*3) 


/*******************************************************************************
*  TYPEDEFS
*/

/* Config Exchange parameters */
typedef struct
{
   char *pSourceURI; /* Pointer to source URI string.
                        NULL or zero length string if not used.
                        NOTE THIS IS NOT A MD RECEIVE PARAMETER, IT IS A SEND
                        PARAMETER. It is placed in this structure only for
                        compability reason. 
                        The source URI is used in the MD header of sent
                        messages */
} IPT_MD_REC_PAR;

typedef struct
{
   char *pDestinationURI; /* Pointer to destination URI string.
                             NULL or zero length string if not used */
} IPT_MD_SEND_PAR;

typedef struct
{
   UINT32 timeoutValue;      /* Timeout value in ms, before considering received
                                process data invalid */
   UINT32 validityBehaviour; /* Behaviour when received process data is invalid
                                0 = set data to zero != 0 keep data */
   char *pSourceURI;         /* Pointer to source filter URI string.
                                NULL or zero length string if not used */
} IPT_PD_REC_PAR;

typedef struct
{
   char *pDestinationURI;  /* Pointer to destination URI string.
                              NULL or zero length string if not used */
   UINT32 cycleTime;       /* Cycle time in ms */
   UINT32 redundant;       /* Redundant function ID. 0 = No redundancy */
} IPT_PD_SEND_PAR;

typedef struct
{
   UINT32 comId;              /* Com ID */
   UINT32 datasetId;          /* Dataset ID */
   UINT32 comParId;           /* Communication parameter ID */
   IPT_MD_REC_PAR mdRecPar;   /* Message data receive parameters */
   IPT_MD_SEND_PAR mdSendPar; /* Message data send parameters */
   IPT_PD_REC_PAR pdRecPar;   /* Process data receive parameters */
   IPT_PD_SEND_PAR pdSendPar; /* Process data receive parameters */
} IPT_CONFIG_EXCHG_PAR;

typedef struct
{
   UINT32 ackTimeOut;      /* Acknowledge time-out in ms */
   UINT32 responseTimeOut; /* Response time-out in ms */
   char *pDestinationURI;  /* Pointer to destination URI string.
                              NULL or zero length string if not used  */
   char *pSourceURI;       /* Pointer to source URI string.
                              NULL or zero length string if not used
                              The source URI is used in the MD header of sent
                              messages */
} IPT_MD_SEND_PAR_EXT;

typedef struct
{
   UINT32 comId;                  /* Com ID */
   UINT32 datasetId;              /* Dataset ID */
   UINT32 comParId;               /* Communication parameter ID */
   IPT_MD_SEND_PAR_EXT mdSendPar; /* Message data send parameters */
   IPT_PD_REC_PAR pdRecPar;       /* Process data receive parameters */
   IPT_PD_SEND_PAR pdSendPar;     /* Process data receive parameters */
} IPT_CONFIG_EXCHG_PAR_EXT;

/* Config dataset formatting table */
struct iptDatasetFormat
{
   INT32 id;      /* Data type (IPT_UINT32 etc, <0) or Dataset number (>0) */
   UINT32 size;   /* Number of items, or IPT_VAR_SIZE */
};
typedef struct iptDatasetFormat IPT_DATASET_FORMAT;

/* Config dataset parameters */
typedef struct
{
   UINT32 datasetId;            /* Dataset ID */
   UINT32 size;                 /* Size of dataset if fixed, 0 if variable.
                                   Calculated by IPTCom. */
   UINT16 alignment;            /* Memory alignment for this dataset (size of
                                   largest data in the dataset). 
                                   Calculated by IPTCom. */
   UINT16 nLines;               /* No of lines in format table below */
   UINT16 prepared;             /* Set TRUE when size and alignment have been
                                   calculated by IPTCom */
   UINT16 varSize;              /* Set TRUE if size is variable 
                                   Calculated by IPTCom. */
   IPT_DATASET_FORMAT *pFormat; /* Pointer to formatting table
                                   Calculated by IPTCom. */
} IPT_CONFIG_DATASET;

/* Extended config dataset parameters */
typedef struct
{
   UINT32 datasetId;            /* Dataset ID */
   UINT16 nLines;               /* No of entries in format table */
   UINT8  disableMarshalling;   /* Set to TRUE if dataset will be marshalled
   											outside of IPTCom */
   UINT8  reserved1;            /* Must be zero */
   UINT32 reserved2;            /* Must be zero */
} IPT_CONFIG_DATASET_EXT;

/* Config communication parameters */
typedef struct
{
   UINT32 comParId;      /* Communication parameter ID */
   UINT8  qos;           /* quality of service */
   UINT8  ttl;           /* time to live */
} IPT_CONFIG_COM_PAR;


/* XML parser declarations */
#define MAX_SRC_FILTER 8      /* Max number of PD receive source filters per comid */
#define MAX_URI_LEN    101    /* Max length of a URI string */
#define MAX_TOKLEN (MAX_SRC_FILTER*(MAX_URI_LEN+1))  /* Max length of token string */
#define MAX_TAGLEN 132        /* Max length of tag string */

/* Tokens 
TOK_OPEN       "<" character
TOK_CLOSE      ">" character
TOK_OPEN_END   "</" characters. Open for an end tag.
TOK_CLOSE_EMPTY   "/> characters. Close for an empty element.
TOK_ID         "Identifier". Identifiers are character sequences limited
by whitespace characters or special characters ("<>/=").
Identifiers in quotes (") may contain whitespace and special characters. 
The id is put in tokenValue.
TOK_EQUAL      "=" character
TOK_EOF        End of file
TOK_START_TAG  TOK_OPEN + TOK_ID
TOK_END_TAG    TOK_OPEN_END + TOK_ID + TOK_CLOSE
*/
enum {TOK_OPEN = 0, TOK_CLOSE, TOK_OPEN_END, TOK_CLOSE_EMPTY, TOK_EQUAL, TOK_ID,
      TOK_EOF, TOK_START_TAG, TOK_END_TAG, TOK_ATTRIBUTE};

typedef struct
{
   FILE *infile;
   char tokenValue[MAX_TOKLEN];
   int tagDepth;
   int tagDepthSeek;
   char tokenTag[MAX_TAGLEN+1];
} XML_LOCAL;


/* Statistics types */

/* Statistic data structure */
typedef struct
{
   UINT32 oid[IPT_STAT_OID_LEN]; /* OID array, IPT_STAT_OID_STOPPER last */
   UINT32 type;                  /* Data type, IPT_STAT_* */
   union
   {
      INT32 integer;
      char octetString[IPT_STAT_STRING_LEN + 1];
      UINT32 ipAddress;
      UINT32 counter;
      UINT32 timeTicks;
   } value;
} IPT_STAT_DATA;

/* Function pointer to read function without key, i.e access type IPTCOM_STAT_FUNC_NOKEY_R */
typedef int (*IPT_STAT_NOKEY_R_FUNCPTR) (
   IPT_STAT_DATA *pStatData); /* IN/OUT Pointer to statistic data structure */

/* Function pointer to write function without key i.e access type IPTCOM_STAT_FUNC_NOKEY_W */
typedef int (*IPT_STAT_NOKEY_W_FUNCPTR) (
   IPT_STAT_DATA *pStatData); /* IN/OUT Pointer to statistic data structure */

/* Function pointer to read/write function without key i.e access type IPTCOM_STAT_FUNC_NOKEY_RW */
typedef int (*IPT_STAT_NOKEY_RW_FUNCPTR) (
   IPT_STAT_DATA *pStatData, /* IN/OUT Pointer to statistic data structure */
   int writeFlag);           /* IN Write flag 0 = read else write */

/* Function pointer to read function with key(s) i.e access type IPTCOM_STAT_FUNC_KEY_R */
typedef int (*IPT_STAT_KEY_R_FUNCPTR) (
   IPT_STAT_DATA *pStatData, /* IN/OUT Pointer to statistic data structure */
   UINT32 ind,               /* IN index of statistic data structure OID array */
   UINT32 oidDig);           /* IN OID digit */

/* Function pointer to write function with key(s) i.e access type IPTCOM_STAT_FUNC_KEY_W */
typedef int (*IPT_STAT_KEY_W_FUNCPTR) (
   IPT_STAT_DATA *pStatData, /* IN/OUT Pointer to statistic data structure */
   UINT32 ind,               /* IN index of statistic data structure OID array */
   UINT32 oidDig);           /* IN OID digit */

/* Function pointer to read function with key(s) i.e access type IPTCOM_STAT_FUNC_KEY_RW */
typedef int (*IPT_STAT_KEY_RW_FUNCPTR) (
   IPT_STAT_DATA *pStatData, /* IN/OUT Pointer to statistic data structure */
   UINT32 ind,               /* IN index of statistic data structure OID array */
   UINT32 oidDig,            /* IN OID digit */
   int writeFlag);           /* IN Write flag 0 = read else write */


typedef struct iptOidData
{
   UINT32 oidDig;
   char name[MAX_OID_NAME];
   int size;
   union
   {
     struct iptOidData *pNext;             /* Pointer to next OID data structure */
     INT32 *pInteger;                      /* Pointer to integer data */
     char  *pOctetString;                  /* Pointer to string data */
     UINT32 *pIpAddress;                   /* Pointer to IP address data */
     UINT32 *pCounter;                     /* Pointer to counter data */
     UINT32 *pTimeTicks;                   /* Pointer to time ticks data */
     IPT_STAT_NOKEY_R_FUNCPTR  pRfunc;     /* Pointer to read data function without key */
     IPT_STAT_NOKEY_W_FUNCPTR  pWfunc;     /* Pointer to write data function without key */
     IPT_STAT_NOKEY_RW_FUNCPTR pRWfunc;    /* Pointer to read/write data function without key */
     IPT_STAT_KEY_R_FUNCPTR    pRKeyfunc;  /* Pointer to read data function with key(s) */
     IPT_STAT_KEY_W_FUNCPTR    pWKeyfunc;  /* Pointer to write data function with key(s) */
     IPT_STAT_KEY_RW_FUNCPTR   pRWKeyfunc; /* Pointer to read/write data function with key(s) */
   } ptr;
   int accessType;
   int dataType;
} IPT_OID_DATA;

typedef struct
{
   UINT32 oidDig;
   char name[MAX_OID_NAME];
} IPT_OID_DEF;


/*******************************************************************************
*  GLOBAL FUNCTIONS
*/
DLL_DECL int IPTCom_prepareInit(int startupMode, const char *pXMLPath);
DLL_DECL int IPTCom_addConfig(const char *pXMLPath);
DLL_DECL int IPTCom_getStatus(void);
DLL_DECL void IPTCom_terminate(int remainingTime);
DLL_DECL void IPTCom_destroy(void);
DLL_DECL void IPTCom_process(void);
DLL_DECL void IPTCom_disableMarshalling(int disable);
DLL_DECL void IPTCom_enableIPTDirEmulation(const char *pHostPath);
DLL_DECL int IPTCom_isIPTDirEmulated(void);
DLL_DECL int IPTCom_handleEvent(UINT32 selector, void* pArg);
#ifdef LINUX_MULTIPROC
int IPTCom_MPattach(void);
int IPTCom_MPdetach(void);
#endif

DLL_DECL const char *IPTCom_getErrorString(int errorNumber);
DLL_DECL UINT32 IPTCom_getVersion(void);

#ifdef TARGET_SIMU
DLL_DECL int IPTCom_SimOpenInterface(char *ifIP);
DLL_DECL int IPTCom_SimRegisterSimulatedInterface(char *pCardIpAddr, char *pIpAddr);
DLL_DECL int IPTCom_SimUnRegisterSimulatedInterface(char *pIpAddr);
DLL_DECL int IPTCom_SimAddDefaultGateway(char *pCardRef,	char *pIpAddr);
#endif

/* Utility functions */
DLL_DECL int IPTCom_getUriHostPart(UINT32 ipAddr, char *pUri, UINT8 *pTopoCnt);
DLL_DECL int IPTCom_getAddrByName(const char *pUri, UINT32 *pIpAddr, UINT8 *pTopoCnt);
DLL_DECL int IPTCom_getAddrByNameExt(const char *pUri, UINT32 *pIpAddr, int *pFrg, UINT8  *pTopoCnt);
DLL_DECL int IPTCom_getOwnIds(char *pDevId, char *pCarId, char *pCstId);
DLL_DECL UINT32 IPTCom_getOwnIpAddr(void);
DLL_DECL int iptMarshall(UINT32 comId, const unsigned char *pSrc, unsigned char *pDst, UINT32 *pDstSize);
DLL_DECL int iptMarshallDS(UINT32 datasetId, const unsigned char *pSrc, unsigned char *pDst, UINT32 *pDstSize);
DLL_DECL int iptUnmarshall(UINT32 comId, unsigned char *pSrc, unsigned char *pDst, UINT32 *pDstSize);
DLL_DECL int iptUnmarshallDS(UINT32 datasetId, unsigned char *pSrc, unsigned char *pDst, UINT32 *pDstSize);
DLL_DECL int iptCalcDatasetSize(UINT32 datasetId, BYTE *pSrc, UINT32 *pSize);

/* Configuration functions */
DLL_DECL int iptConfigAddExchgPar(const IPT_CONFIG_EXCHG_PAR *pExchgPar);
DLL_DECL int iptConfigAddExchgParExt(const IPT_CONFIG_EXCHG_PAR_EXT *pExchgPar);
DLL_DECL int iptConfigAddPdSrcFilterPar(const UINT32 comId, const UINT32 filterId, const char *pSourceURI);
DLL_DECL int iptConfigAddDestIdPar(const UINT32 comId, const UINT32 destId, const char *pDestURI);
DLL_DECL int iptConfigAddDataset(IPT_CONFIG_DATASET *pDataset, const IPT_DATASET_FORMAT *pDatasetFormat);
DLL_DECL int iptConfigAddDatasetId(UINT32 datasetId, UINT16 nLines, const IPT_DATASET_FORMAT *pDatasetFormat);
DLL_DECL int iptConfigAddDatasetExt(const IPT_CONFIG_DATASET_EXT *pDataset, const IPT_DATASET_FORMAT *pDatasetFormat);
DLL_DECL int iptConfigAddComPar(const IPT_CONFIG_COM_PAR *pComPar);
DLL_DECL int iptConfigGetDatasetId(UINT32 comId, UINT32 *pdatasetId);

/* XML parser functions */
DLL_DECL int iptXmlOpen(XML_LOCAL *pLoc, const char *file);
DLL_DECL int iptXmlClose(XML_LOCAL *pLoc);
DLL_DECL int iptXmlSeekStartTagAny(XML_LOCAL *pLoc, char *tag, int maxlen);
DLL_DECL int iptXmlSeekStartTag(XML_LOCAL *pLoc, const char *tag);
DLL_DECL void iptXmlEnter(XML_LOCAL *pLoc);
DLL_DECL void iptXmlLeave(XML_LOCAL *pLoc);
DLL_DECL int iptXmlGetAttribute(XML_LOCAL *pLoc, char *attribute, int *pValueInt, char *value);

/* Statistics functions */
DLL_DECL int IPTCom_statGet(const char *pRequest, char *pResponse, UINT32 length);
DLL_DECL int IPTCom_statGetNext(const char *pRequest, char *pResponse, UINT32 length);
DLL_DECL int IPTCom_statSet(const char *pRequest, char *pResponse, UINT32 length);
#ifndef LINUX_MULTIPROC
DLL_DECL int iptStatAddSubAgent(UINT32 len, IPT_OID_DEF oidDef[], IPT_OID_DATA *pStatStruct,  UINT32 size);
#endif

/* Topo counter function. ONLY to be used by the TDC */
DLL_DECL int IPTCom_setTopoCnt(UINT32 topoCnt);

#ifdef __cplusplus
}
#endif

#endif

