#ifndef BSW_H
#define BSW_H

/******************* Definetion of ID ********************/
#define BSW_id  2

/************** Definetion of the direction *************/

 
/***************** Prototype of Functions ******************************************************************/
void BSW_vAlgorithm( void );
void BSW_Action( void );
void BSW_SendID(void);
unsigned char Get_FrontRightDis( void);
unsigned char Get_FrontLeftDis( void);
unsigned char Get_BackRightDis(void);
unsigned char Get_BackLeftDis( void); 



/************************* Definetion of The Safe Distance ******************/
#define SAFE_DISTANCE    25 // Distance in centi-meters

#endif


