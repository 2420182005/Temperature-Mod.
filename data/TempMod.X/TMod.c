/*
 * File:   PA2.c
 * Author: Acer
 *
 * Created on 24 de noviembre de 2020, 08:57 AM
 */
/////////////////// DATOS DEL PROGRAMA ////////////////////

//  TTITULO: Parte 2
//  MICRO:PIC16F15244
//  ESTUDIANTES: Jessica Villamizar Suarez 2420182005
//               Juan Felipe Quiroga       2420192023                    
//  Profesor: Harold F MURCIA
//  FECHA: 26 de noviembre de 2020

///////////// CONFIGURACION del MCU ////////////////// */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>


#pragma config FEXTOSC = OFF    // External Oscillator Mode Selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_1MHZ    // Power-up Default Value for COSC bits->HFINTOSC (1 MHz)
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; I/O function on RA4
#pragma config VDDAR = HI    // VDD Range Analog Calibration Selection bit->Internal analog systems are calibrated for operation between VDD = 2.3V - 5.5V

// CONFIG2
#pragma config MCLRE = EXTMCLR    // Master Clear Enable bit->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RA3 pin function is MCLR
#pragma config PWRTS = PWRT_OFF    // Power-up Timer Selection bits->PWRT is disabled
#pragma config WDTE = OFF    // WDT Operating Mode bits->WDT disabled; SEN is ignored
#pragma config BOREN = ON    // Brown-out Reset Enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = LO    // Brown-out Reset Voltage Selection bit->Brown-out Reset Voltage (VBOR) set to 1.9V
#pragma config PPS1WAY = ON    // PPSLOCKED One-Way Set Enable bit->The PPSLOCKED bit can be cleared and set only once in software
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG4
#pragma config BBSIZE = BB512    // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF    // Boot Block Enable bit->Boot Block is disabled
#pragma config SAFEN = OFF    // SAF Enable bit->SAF is disabled
#pragma config WRTAPP = OFF    // Application Block Write Protection bit->Application Block is not write-protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block is not write-protected
#pragma config WRTC = OFF    // Configuration Registers Write Protection bit->Configuration Registers are not write-protected
#pragma config WRTSAF = OFF    // Storage Area Flash (SAF) Write Protection bit->SAF is not write-protected
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR. MCLRE Configuration bit is ignored.

// CONFIG5
#pragma config CP = OFF    // User Program Flash Memory Code Protection bit->User Program Flash Memory code protection is disabled

///////////// DEFINICIONES  //////////////////
#define _XTAL_FREQ 4000000  // originalmente en 1Mhz

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

#define CAL                       LATAbits.LATA4  //Definiendo RA4 
#define FRI                       LATAbits.LATA5  //Definiendo RA5

///////////// VARIABLES GLOBALES  //////////////////

int resultHigh;
int resultLow;


///////////// DECLARACION DE FUNCIONES Y PROCEDIMIENTOS ///////////////////
void PIN_MANAGER_Initialize(void)
{
    
     // TRISx registers
    TRISA = 0B00000000;     //
    TRISB = 0B00000000;     //
    TRISC = 0B00001000;     //
    
     // ANSELx registers
   
    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0B00001000;    //RC3 como entrada analogica 
   
    WPUA = 0x04;
    WPUB = 0X00;
    WPUC = 0x0C;     
    
    
}

//void OSCILLATOR_Initialize(void)
//{
//    OSCEN = 0x00;                                                               // MFOEN disabled; LFOEN disabled; ADOEN disabled; HFOEN disabled;
//    OSCFRQ = 0x00;                                                              // HFFRQ0 1_MHz
//    OSCTUNE = 0x00;
//}

void ADC_con(void) {
    ADCON0 = 0B01001101;    // Puerto RC3(010011); GO en 0; ON en 1
    ADCON1 = 0B10010000;    // FM en 1, justificado a la derecha
                            // los 6 MSB del ADRESH son ceros
    
}

void conversion(void){
    ADCON0bits.GO = 1;      // inicio
    while (ADCON0bits.GO);  // Espera conversión
    resultHigh = ADRESH;    // Lee resultado
    resultLow = ADRESL;     // Lee resultao
    
}


/////////////  INICIO DEL PROGRAMA PRINCIPAL //////////////////////////

void main(void) {
    PIN_MANAGER_Initialize();
    ADC_con();
    while(1){
        conversion();           // 0 - 1023  17° y 30°
        if(resultLow  >= 500)   // mayor o igual a 27°
        {
            CAL = 1;
            FRI = 0;
            
        }
        else if(resultLow < 300) // menor de 22°
        {
            CAL = 0;
            FRI = 1;
        }
        else                     // mayor o igual a 22° y menor que 27°
        {
            FRI = 0;
            CAL = 0;
        }
    }    
    
}
