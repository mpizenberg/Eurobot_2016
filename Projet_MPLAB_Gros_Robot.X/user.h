#ifndef _USER_H_
#define _USER_H_

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#define led _LATA2
#define PIN_LAISSE _RC3     // ==> Pin 5V numero 4.
#define TRIS_LAISSE _TRISC3
#define PIN_TEAM _RA4       // ==> Pin 3.3V numero 2
#define TRIS_TEAM _TRISA4 
// ultrason : en RC4 // defini dans ultrason .h

/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        80000000UL
#define FCY             SYS_FREQ/2
#define FOSC            FCY


#define BAUDRATEAX12 57600
#define BRGVALAX12 ((FCY / BAUDRATEAX12 / 16) - 1)

#define BAUDRATERASPI	57600
#define BRGVALRASPI ((FCY / BAUDRATERASPI / 16) - 1)



extern volatile char Active_Delay_90;
extern volatile long Delay_90;
extern volatile char Delay_90_Over;

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
void InitTimers();
void Init_CN(void);
void writeStringToUART (const char* msg);
// initialize all things
void Init_All(int);




#endif // _USER_H_
