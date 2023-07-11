/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    Comm Alg.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 * Author     : Mahmoud Karem Zamel
 * Created on : Mar 22, 2023
 */

#include "Comm_Algorithm.h"

///**********************************************************************************/

void Set_MSG_ID_Comm_ALG_ID(int s)
{
	SubSys_State = s ;
	switch(SubSys_State)
	{
	case NOCHANGE:
		break;
	case EEBL :
		//EEBL_ALG_ID();
		break;
	case BSW :
		//BSW_ALG_ID();
		break;
	case DNPW :
		//DNPW_ALG_ID();
		break;
	case IMA :
		//IMA_ALG_ID();
		break;
	case FCW :
		//FCW_ALG_ID();
		break;
	}

	printf ("CommAlg ---------- Subsys_State=%d ----------> SubSys_ALG_IDorithm\n" ,SubSys_State);

}


/**********************************************************************************/
