
#ifndef __MAIN_H
#define __MAIN_H


#define LED LATCbits.LATC6
#define TRIS_LED TRISCbits.TRISC6






void main(void);
void SSPISR(char *data);







#endif