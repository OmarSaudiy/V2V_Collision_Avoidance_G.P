#include "DNPW_BSW_handler.h"


static void checker(u8);

void FrontSidesUS_vidAlg(void)
{

    u8 Distance=0;

    Distance=US_u8GetDistance(/*Front Right us*/);
    checker(Distance);  

    Distance=US_u8GetDistance(/*Front left us*/);
    checker(Distance);
	

}
void checker(u8 Distance)
{

   if( Distance < 5 cm )
    {
		//check for Don't pass system 
		u8 back_dis=0;
		back_dis=US_u8GetDistance(/*From back us*/);
		if(back_dis)
		{
			// SendId(DNPW_id,MyDirection); 
        printf("Send DNPW_ID and My Direction");
			
		}
		else
		{
			
		// SendId(BSW_id,MyDirection); 
        printf("Send BSW_ID and My Direction");
		}
        
    }
	
}