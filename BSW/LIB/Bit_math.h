/******************************************************************************/
/*                                                                            */
/* !Layer           : LIB                                                     */
/*                                                                            */
/* !File            : Bit_math.h                                              */
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
#ifndef BIT_MATH_H
#define BIT_MATH_H

#define REGISTER_SIZE 8
#define SET_BIT(reg,bit)    reg|=(1<<bit)
#define CLR_BIT(reg,bit)    reg&=(~(1<<bit))
#define TOG_BIT(reg,bit)    reg^=(1<<bit)
#define GET_BIT(reg,bit)    ((reg&(1<<bit))>>bit)
#define IS_BIT_SET(reg,bit)  (reg&(1<<bit))>>bit
#define IS_BIT_CLR(reg,bit)  !((reg&(1<<bit))>>bit)
#define ROR(reg,num)         reg=(reg<<(REGISTER_SIZE-num))|(reg>>(num))
#define ROL(reg,num)         reg=(reg>>(REGISTER_SIZE-num))|(reg<<(num))

#endif
