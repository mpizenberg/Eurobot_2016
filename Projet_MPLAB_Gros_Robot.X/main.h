#ifndef MAIN_H
#define	MAIN_H

#include "user.h"          // User funct/params, such as InitApp
#include <libpic30.h>
#include <stdint.h>
#include "qei.h"           // QEI definitions for easier use
#include "lib_asserv/lib_asserv_default.h"
#include "lib_asserv/lib_asserv.h"
#include "motor.h"
#include "uart.h"
#include "Sick_VBat.h"
#include "Evitement.h"
#include "ultrason.h"
#include "Gestion_IO_AU_Config.h"
#include "actions_ax12.h"
#include "Timer_Asserv.h"
#include "Timer_ms.h"
#include "communication.h"
#include "ax12.h"
#include "lib_asserv/private/tools.h"
#include "I2C.h"


#endif	/* MAIN_H */

void Debug_Asserv_Start(void);