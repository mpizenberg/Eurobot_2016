

#include <xc.h>
#include "main.h"

void I2C_Init(void) {
    //    long BRG = 1 + FOSC / (FREQ_I2C * 2);        // calculs simplifiés par rapport à la datasheet, à revoir peut-être
    //
    //    if (BRG > 0x1FF)
    //        BRG = 0x1FF;    // registre 9 bits !
    //    //I2CCONbits.A10M = 1;
    //
    //    //I2C1BRG = BRG;      // regle le baudrate
    //
    //    I2C1BRG = 0x1FF;
    //    I2C1CONbits.I2CEN = 1;  // active l'interface

}

void I2C_Try_All(void) {
    //
    //    int add = 0x20;
    //    int toto;
    //    for (add = 0x0; add <= 0x7F; add ++)
    //    {
    //        Set_Maxtime(30);
    //        I2C1CONbits.SEN = 1;    // envoi start condition
    //        while (I2C1CONbits.SEN && Get_Maxtime());    // attente de l'envoi
    //        I2C1TRN = add;     // write de l'adresse
    //        while ((!I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
    //        while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission
    //
    //        //if (!I2C1STATbits.ACKSTAT && Get_Maxtime())  // si on a recu un ack :
    //       // {
    //            //if (!(add & 0x01)) {
    //                Set_Maxtime(30);
    //                I2C1TRN = 0x55;
    //                while ((!I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
    //                while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission
    //
    //           // }
    //
    //            toto = 0;
    //            while (toto < 100){
    //                toto ++;
    //            }
    //            Set_Maxtime(1000);
    //            while (Get_Maxtime());
    //        }
    //        Set_Maxtime(10);
    //        I2C1CONbits.PEN = 1;    // envoi stop condition
    //        while (I2C1CONbits.PEN && Get_Maxtime());    // attente de l'envoi
    //        Set_Maxtime(60);
    //        while (Get_Maxtime());
    //    }
    //    // printf ("Fin\n");
    //    toto = 0;
    //    while (toto < 100){
    //        toto ++;
    //    }
    //    I2C1CONbits.I2CEN = 0;
    //    I2C1CONbits.I2CEN = 1;
    //
}
/*
void I2C_Alti_Send_Command(u8 command)
{
    Set_Maxtime(40);
    I2C1CONbits.SEN = 1;    // envoi start condition
    while (I2C1CONbits.SEN && Get_Maxtime());    // attente de l'envoi
    I2C1TRN = ALTI_ADD;     // write
    while ((!I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
    while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission


    I2C1TRN = command;
    while ((!I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
    while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission

    I2C1CONbits.PEN = 1;    // envoi stop condition
    while (I2C1CONbits.PEN && Get_Maxtime());    // attente de l'envoi
    // if (!Maxtime)
    //    printf ("error Cmd\n");
}

u32 I2C_Alti_Read(u8 nb_bytes)
{
    u8 i;
    u32 val32 = 0;
    Set_Maxtime(40);
    I2C1CONbits.SEN = 1;    // envoi start condition
    while (I2C1CONbits.SEN && Get_Maxtime());    // attente de l'envoi
    I2C1TRN = ALTI_ADD+1;     // read
    while ((!I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
    while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission

    for (i = 1; i <= nb_bytes; i ++) {
        I2C1CONbits.RCEN = 1;   // passage en receive
        while (I2C1CONbits.RCEN && Get_Maxtime());

        val32 = (val32 * 256) + I2C1RCV;

        if (i == nb_bytes)
            I2C1CONbits.ACKDT = 1;      // on veut pas acknoledge
        else
            I2C1CONbits.ACKDT = 0;      // on veut acknoledge

        I2C1CONbits.ACKEN = 1;      // laisse partir le bit acknoledge
        while (I2C1CONbits.ACKEN && Get_Maxtime());
    }

    I2C1CONbits.PEN = 1;    // envoi stop condition
    while (I2C1CONbits.PEN && Get_Maxtime());    // attente de l'envoi
    if (!Get_Maxtime())
        printf ("error Rd\n");
    return val32;
}
 */
