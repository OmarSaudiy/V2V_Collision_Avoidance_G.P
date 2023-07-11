/******************************************************************************/
/*                                                                            */
/* !Layer           : LIB                                                     */
/*                                                                            */
/* !File            : STD_TYPES.h                                             */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : V2V Collision avoidance                                 */
/*                                                                            */
/* !Target          : Raspberry Pi 3 model B                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/* Created by        : Karim Mohamed                    !Date : MARCH  1, 2023*/
/******************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H


#ifndef NULL
#define NULL      ((void *)0)
#endif


typedef unsigned  char 				        u8;
typedef signed 	  char 			 	        s8;

typedef unsigned  short     int 		    u16;
typedef signed 	  short     int 		    s16;

typedef unsigned  long      int 			u32;
typedef signed 	  long      int 			s32;
typedef unsigned  long long int	 	        u64;
typedef signed 	  long long int 	        s64;

typedef float 						        f32;
typedef double 			                	f64;

#endif
