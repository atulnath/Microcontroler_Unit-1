#include "init.h"

void showData(int value);

/********************************************************************
 *                              main                                *
 ********************************************************************/
void main(void)
{
    /* board initialization */
    Init();

    /* forever */
    for(;;)
    {
    value = ADC_0.CDR[4].B.CDATA; /* Potentiometer */
    showdata(value);


    }
}

void showData(int value)
{
/********************************************************************
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 ********************************************************************/  
  if(value <= 256)
  {   
    /* LED0 - on, LED1 - off, LED2 - off, LED3 - off */
			SIU.GPDO[9].R = 0; /* LED0 */
            SIU.GPDO[42].R = 1; /* LED1 */
            SIU.GPDO[13].R = 1; /* LED2 */
            SIU.GPDO[12].R = 1; /* LED3 */
            SIU.GPDO[62].R = 1; /* LED4 */
            SIU.GPDO[61].R = 1; /* LED5 */
            SIU.GPDO[59].R = 1; /* LED6 */
            SIU.GPDO[11].R = 1; /* LED7 */
  }
  else if(value > 256 && value <= 512)
  {  
    /* LED0 - on, LED1 - on, LED2 - off, LED3 - off */
			SIU.GPDO[9].R = 0; /* LED0 */
            SIU.GPDO[42].R = 0; /* LED1 */
            SIU.GPDO[13].R = 1; /* LED2 */
            SIU.GPDO[12].R = 1; /* LED3 */
            SIU.GPDO[62].R = 1; /* LED4 */
            SIU.GPDO[61].R = 1; /* LED5 */
            SIU.GPDO[59].R = 1; /* LED6 */
            SIU.GPDO[11].R = 1; /* LED7 */
  }
  else if(value > 512 && value <= 768)
  {  
    /* LED0 - on, LED1 - on, LED2 - on, LED3 - off */
			SIU.GPDO[9].R = 0; /* LED0 */
            SIU.GPDO[42].R = 0; /* LED1 */
            SIU.GPDO[13].R = 0; /* LED2 */
            SIU.GPDO[12].R = 1; /* LED3 */
            SIU.GPDO[62].R = 1; /* LED4 */
            SIU.GPDO[61].R = 1; /* LED5 */
            SIU.GPDO[59].R = 1; /* LED6 */
            SIU.GPDO[11].R = 1; /* LED7 */
  }    
  else
  {  
    /* LED0 - on, LED1 - on, LED2 - on, LED3 - on */
			SIU.GPDO[9].R = 0; /* LED0 */
            SIU.GPDO[42].R = 0; /* LED1 */
            SIU.GPDO[13].R = 0; /* LED2 */
            SIU.GPDO[12].R = 0; /* LED3 */
            SIU.GPDO[62].R = 1; /* LED4 */
            SIU.GPDO[61].R = 1; /* LED5 */
            SIU.GPDO[59].R = 1; /* LED6 */
            SIU.GPDO[11].R = 1; /* LED7 */
  }     
}

/********************************************************************
 *                      Interrupt Functions                         *
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 *                Interrupts can be handled below.                  *
 ********************************************************************/  
void PITCHANNEL0() {
    /* clear flag */
    PIT.CH[0].TFLG.B.TIF = 1;
}

void PITCHANNEL1() {
    /* clear flag */
    PIT.CH[1].TFLG.B.TIF = 1;
}

/********************************************************************
 *                   Interrupt Vector Table                         *
 *                                                                  *
 *                 Don't touch anything below!                      *
 ********************************************************************/
#pragma interrupt Ext_Isr
#pragma section IrqSect RX address=0x040
#pragma use_section IrqSect Ext_Isr

void Ext_Isr() {
    switch(INTC.IACKR.B.INTVEC)
    {
        case 59:
            /* Timer Interrupt */
            PITCHANNEL0();
            break;
        case 60:
            /* Timer Interrupt */
            PITCHANNEL1();
            break;            
        default:
            break;
    }
    /* End of Interrupt Request */
    INTC.EOIR.R = 0x00000000;
}
