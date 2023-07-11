/*
 * state.h
 *
 *  Created on: Aug 10, 2022
 *      Author: Mahmoud Karem Zamel
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h>

/* Automatic State Function Generated */
#define STATE_define(_StateFunc_) void ST_##_StateFunc_()

/* Func name for using in implementation for calling */
#define STATE(_StateFunc_)  ST_##_StateFunc_


/*** States Connections ***/


///* ESP32_Driver --> Communication_ALG_IDorithm */
void Set_MSG_ID_Comm_ALG_ID(int s);
//
///* Main_ALG_IDorithm --> SubSystems */
void EEBL_ALG_ID();
void BSW_ALG_ID();
void DNPW_ALG_ID();
void IMA_ALG_ID();
void FCW_ALG_ID();


#endif /* STATE_H_ */
