
#ifndef CA_PROGRAM_H_
#define CA_PROGRAM_H_

#include "state.h"

/**********************************************************************************/

/* Define States of Sub Systems */
enum {
	NOCHANGE=0,
	EEBL,
	BSW,
	DNPW,
	IMA,
	FCW
}SubSys_State;


/**********************************************************************************/

/* Declare State Functions of CA */
// Nothing

void Set_MSG_ID_Comm_Alg(int s);

/**********************************************************************************/

#endif /* CA_PROGRAM_H_ */
