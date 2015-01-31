/*                                                                     */
/* $Id: iptDef.h 5395 2012-02-10 17:14:13Z bloehr $           */
/*                                                                     */
/* DESCRIPTION    System level definitions for IP-Train                */
/*                                                                     */
/* AUTHOR         M.Ritz         PPC/EBTS                              */
/*                                                                     */
/* REMARKS                                                             */
/*                                                                     */
/* DEPENDENCIES                                                        */
/*                                                                     */
/*  MODIFICATIONS:                                                     */
/*                                                                     */
/*  CR-3326 (Bernd Loehr, 2012-02-10)                                  */
/*           Improvement for 3rd party use / Darwin port added.        */
/*                                                                     */
/*  CR-3477 (Bernd Löhr, 2012-02-09)                                   */
/* 			TÜV Assessment findings                                    */
/*                                                                     */
/*  CR-382 (Bernd Loehr, 2010-08-20)                                   */
/* 			Definitions for UINT64 added                               */
/*                                                                     */
/*                                                                     */
/* All rights reserved. Reproduction, modification, use or disclosure  */
/* to third parties without express authority is forbidden.            */
/* Copyright Bombardier Transportation GmbH, Germany, 2002.            */
/*                                                                     */

/* ---------------------------------------------------------------------------- */

#if !defined (IPTDEF_H)
   #define IPTDEF_H

/* ---------------------------------------------------------------------------- */

#if defined (__cplusplus)
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* ----- Definition of the BASE TYPES used in IP-Train porject ------------- */
/* ------------------------------------------------------------------------- */

#if !defined (BASE_TYPES_ARE_DEFINED)
   #define BASE_TYPES_ARE_DEFINED

   /* If the Basetypes happen to be defined already (e.g. WIN32, CSS2 ...),
      define BASE_TYPES_ARE_DEFINED before including iptDef.h.
   */

   #if defined (VXWORKS)
   
      /* --------------------   Standard Definitions   ------------------------ */
   
      typedef signed                      char        T_IPT_INT8;
      typedef unsigned                    char        T_IPT_UINT8;
      typedef signed    short             int         T_IPT_INT16;
      typedef unsigned  short             int         T_IPT_UINT16;
      typedef signed                      int         T_IPT_INT32;
      typedef unsigned                    int         T_IPT_UINT32; 
      typedef signed                      long long   T_IPT_INT64;
      typedef unsigned                    long long   T_IPT_UINT64; 
   
   #elif defined(__INTEGRITY)
   
      /* --------------------   Standard Definitions   ------------------------ */
   
      typedef signed                      char        T_IPT_INT8;
      typedef unsigned                    char        T_IPT_UINT8;
      typedef signed    short             int         T_IPT_INT16;
      typedef unsigned  short             int         T_IPT_UINT16;
      typedef signed                      int         T_IPT_INT32;
      typedef unsigned                    int         T_IPT_UINT32; 
      typedef signed                      long long   T_IPT_INT64;
      typedef unsigned                    long long   T_IPT_UINT64; 
   
   #elif defined (LINUX)
   
        /* --------------------   Standard Definitions   ---------------------- */

        typedef signed                   char        T_IPT_INT8;
        typedef unsigned                 char        T_IPT_UINT8;
        typedef signed    short          int         T_IPT_INT16;
        typedef unsigned  short          int         T_IPT_UINT16;
        typedef signed                   int         T_IPT_INT32;
        typedef unsigned                 int         T_IPT_UINT32;
        typedef signed                   long long   T_IPT_INT64;
        typedef unsigned                 long long   T_IPT_UINT64; 

    #elif defined (DARWIN)
    
        /* --------------------   Standard Definitions   ---------------------- */
        
        typedef signed                   char        T_IPT_INT8;
        typedef unsigned                 char        T_IPT_UINT8;
        typedef signed    short          int         T_IPT_INT16;
        typedef unsigned  short          int         T_IPT_UINT16;
        typedef signed                   int         T_IPT_INT32;
        typedef unsigned                 int         T_IPT_UINT32;
        typedef signed                   long long   T_IPT_INT64;
        typedef unsigned                 long long   T_IPT_UINT64; 
    
    #elif defined (WIN32)
   
            /* --------------------   Standard Definitions   ---------------------- */
   
            typedef signed                char        T_IPT_INT8;
            typedef unsigned              char        T_IPT_UINT8;
            typedef signed    short       int         T_IPT_INT16;
            typedef unsigned  short       int         T_IPT_UINT16;
            typedef signed                int         T_IPT_INT32;
            typedef unsigned              int         T_IPT_UINT32;
            typedef signed                long long   T_IPT_INT64;
            typedef unsigned              long long   T_IPT_UINT64;
   
    #else
   
        #error "Either VXWORKS, INTEGRITY, LINUX, DARWIN or WIN32 has to be specified"

   #endif
#endif

/* ------------------------------------------------------------------------- */

#if !defined (INT8)
   #define INT8               T_IPT_INT8
#endif

#if !defined (UINT8)
   #define UINT8              T_IPT_UINT8
#endif

#if !defined (INT16)
   #define INT16              T_IPT_INT16
#endif

#if !defined (UINT16)
   #define UINT16             T_IPT_UINT16
#endif

#if !defined (INT32)
   #define INT32              T_IPT_INT32
#endif

#if !defined (UINT32)
   #define UINT32             T_IPT_UINT32
#endif

#if !defined (INT64)
   #define INT64              T_IPT_INT64
#endif

#if !defined (UINT64)
   #define UINT64             T_IPT_UINT64
#endif

/* ------------------------------------------------------------------------- */

#define ASSERT_BASE_TYPES()      (    (sizeof (INT8)    == 1)         \
                                   && (sizeof (UINT8)   == 1)         \
                                   && (sizeof (INT16)   == 2)         \
                                   && (sizeof (UINT16)  == 2)         \
                                   && (sizeof (INT32)   == 4)         \
                                   && (sizeof (UINT32)  == 4)         \
                                 )

/* ------------------------------------------------------------------------- */

typedef UINT32                               T_IPT_IP_ADDR;
/* for example: IP-Addr    10.0.8.35 translates to
                           (10 * << 24) + (0 * << 16) + (8 << 8) + 35
*/

/* ------------------------------------------------------------------------- */

#define IPT_MAX_LABEL_LEN                    16   /* incl. terminating '\0' */
typedef char                                 T_IPT_LABEL[IPT_MAX_LABEL_LEN];

/*  A uri is a string of the following form:                                 */
/*  ipt://instLabel.funcLabel@devLabel.carLabel.cstLabel.trainLabel          */
/*  Hence the max. uri length is:                                            */
/*  6 + (6 * 15) + 5 * (sizeof (separator)) + 1                              */

#define IPT_MAX_URI_LEN                      ((6 * IPT_MAX_LABEL_LEN) + 6)
typedef char                                 T_IPT_URI[IPT_MAX_URI_LEN];

/* ------------------------------------------------------------------------- */

#if defined (__cplusplus)
}
#endif

#endif
