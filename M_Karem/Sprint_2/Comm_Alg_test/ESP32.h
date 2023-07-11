
#ifndef ESP32_H_
#define ESP32_H_

#include "state.h"

extern void (*pESP32_state)();

/* Define States */
enum {
	ESP32_BUSY = 0,
	ESP32_IDLE
}ESP32_State_ID;

/* Declare State Functions of ESP32 */
STATE_define(ESP32_busy);
STATE_define(ESP32_idle);

/* INIT */
void ESP32_Init();


#endif /* ESP32_H_ */
