#ifndef BSW_H
#define BSW_H

/******************* Definetion of ID ********************/
#define BSW_id  2

/************** Definetion of the direction *************/


/***************** Prototype of Functions ******************************************************************/
void BSW_Algorithm( void );
void BSW_Action( void );
void BSW_SendID(void);
uint8_t Get_FrontRightDis( void);
uint8_t Get_FrontLefttDis( void);
uint8_t Get_BackRightDis(void);
uint8_t Get_BackLefttDis( void);



/************************* Definetion of The Safe Distance ******************/
#define SAFE_DISTANCE    25 // Distance in centi-meters

#endif


