
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000
#include <stdint.h>
#include <stdio.h>
#include "ADC.h"
///////////// VARIABLES GLOBALES  //////////////////
int resultHigh,resultLow;
#define CAL RB3
#define FRI RB4
uint16_t dato;
int a = 4000000;
///////////// DECLARACIï¿½N DE FUNCIONES Y PROCEDIMIENTOS ///////////////////
void PIN_MANAGER_Initialize(void)
{
    TRISB3=0;
    TRISB4=0;
}

void Duty(void)
{
    // 0 - 1023  17° y 30°
    if(dato>=500)
    {
        CAL=0;
        FRI=1;
    }
    else if(dato>=300 && dato<500)
    {
        CAL=0;
        FRI=0;
    }
    else if(dato<300)
    {
        CAL=1;
        FRI=0;
    }
}

void main (void)
{
    PIN_MANAGER_Initialize();
    ADC_init();
    while(1)
    {   
        dato = ADC_read(0);
        Duty();
    }
    return;
}