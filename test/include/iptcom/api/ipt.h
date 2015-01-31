/*****************************************************************************
*  COPYRIGHT   : (C) 2006 Bombardier Transportation
******************************************************************************
*  PROJECT        : IPTrain
*
*  MODULE         : ipt.h
*
*  ABSTRACT       : Common types for the IPTrain project
*
******************************************************************************
*  HISTORY        :
*	
* $Id: ipt.h 5248 2011-09-08 09:38:58Z gweiss $
*
*  Internal (Bernd Loehr, 2010-08-16) 
* 			Old obsolete CVS history removed
*
*
******************************************************************************/

#ifndef  IPT_H
#define  IPT_H

/*****************************************************************************
*	INCLUDES
*/

#include "iptDef.h"        /* IPT definitions */

/*****************************************************************************
*	DEFINES
*/


/*#define LINUX_MULTIPROC */       /* Define if to use Linux multiprocessing */


/* Define 1 if the computer is BIG ENDIAN, otherwise 0 */

#if defined(O_BE)
#define IS_BIGENDIAN 1
#elif defined(O_LE)
#define IS_BIGENDIAN 0
#else
#define IS_BIGENDIAN 0
#endif

/* Macros for conversion to/from IP wire, 16 and 32 bit data */

#if IS_BIGENDIAN
   /* If we are big endian macros are just dummies */
#define TOWIRE16(A)     (A)
#define TOWIRE32(A)     (A)
#define FROMWIRE16(A)   (A)
#define FROMWIRE32(A)   (A)

#else
#define TOWIRE16(A)  ((((UINT16)(A) & 0xff00) >> 8) | \
                      (((UINT16)(A) & 0x00ff) << 8))
#define TOWIRE32(A)  ((((UINT32)(A) & 0xff000000) >> 24) | \
                      (((UINT32)(A) & 0x00ff0000) >> 8)  | \
                      (((UINT32)(A) & 0x0000ff00) << 8)  | \
                      (((UINT32)(A) & 0x000000ff) << 24))
#define FROMWIRE16     TOWIRE16
#define FROMWIRE32     TOWIRE32
#endif

#ifndef NULL
#define NULL	((void *)0)		/* Used for pointers */
#endif


#ifndef TRUE
#define TRUE	(0==0)          /* Boolean True */
#endif

#ifndef FALSE
#define FALSE	(0!=0)          /* Boolean False */
#endif


/*****************************************************************************
*	TYPEDEFS
*/

#if defined(WIN32)
#include <windows.h>

#ifdef DLL_EXPORT
   #define DLL_DECL   __declspec(dllexport)
#elif DLL_IMPORT
   #define DLL_DECL   __declspec(dllimport)
#else
	#define DLL_DECL 
#endif

#else

#define DLL_DECL 

#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Basic types used for all derived types */
#if defined(O_CSS)
#else
typedef unsigned char 	BYTE;
#endif

#if defined(VXWORKS)
#else
#ifdef __cplusplus

typedef long 		(*FUNCPTR) (...);			/* ptr to function returning int	*/

#else

typedef int 		(*FUNCPTR) ();				/* ptr to function returning int */

#endif			/* _cplusplus */
#endif

#ifdef __cplusplus
}
#endif

#define IPT_UNUSED(x)	(void) x;
#endif /* IPT_H */
