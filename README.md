# Temperature Modulator with PIC16F15244

The 'Temperature modulator with PIC16F15244' code uses the PIC16F15244 curiosity nano development board and the ADC convertion alongside LM35 sensor to carry out an action that modulates the room temperature.

##### PIC16F15244 Curiosity Nano Development Board:
![Nano](https://user-images.githubusercontent.com/74994048/100312554-a5dd5f80-2f80-11eb-952c-5f76a1148568.png)
##### Temperature sensor LM35

## Related Documentation
- [PIC16F15244 Product Page](https://www.microchip.com/wwwproducts/en/PIC16F15244)
- [LM35 DDatasheet](https://www.ti.com/lit/ds/symlink/lm35.pdf)

## Software Used
- MPLAB® X IDE 5.40 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.20 or a newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- MPLAB® Code Configurator (MCC) 3.95.0 or newer* [(microchip.com/mplab/mplab-code-configurator)](https://www.microchip.com/mplab/mplab-code-configurator)
- MPLAB® Code Configurator (MCC) Device Libraries PIC10 / PIC12 / PIC16 / PIC18 MCUs* [(microchip.com/mplab/mplab-code-configurator)](https://www.microchip.com/mplab/mplab-code-configurator)
- Microchip PIC16F1xxxx Series Device Support (1.4.119) or newer **[(packs.download.microchip.com/)](https://packs.download.microchip.com/)

## Hardware Used
- PIC16F15244 Curiosity Nano [(EV09Z19A)](https://www.microchip.com/Developmenttools/ProductDetails/EV09Z19A)
- Micro-USB to USB 2.0 cable
- Temperature Sensor LM35
- Operational Amplifiers LM324
- Two 12V relay
- Two Transistors 2N2222 
- Two Leds
- Resistors 
- 12VDC input charger


## Setup
1. Connect the PIC16f15244 Curiosity Nano board to a PC using the Micro-USB to USB 2.0 cable.
2. If not already on your system, download and install MPLABX IDE version 5.40 (or newer).
3. If not already on your system, download and install the XC8 C-Compiler version 2.20 (or newer).
4. Open the 'nombre.X' project as shown in Figure 1.

###### Figure 1: Open Project Window
![1](https://user-images.githubusercontent.com/74994048/100312762-200de400-2f81-11eb-8922-b10d53ed6e9d.png)

5. Press the 'Project Properites' button to open the Project Properties window. Select the Curiosity tool from the Tools drop-down menu as shown in Figure 2.

###### Figure 2: Select the Nano in Project Properties Window
![2](https://user-images.githubusercontent.com/74994048/100312827-492e7480-2f81-11eb-9252-47c689c1b554.png)


6. Press the 'Make and Program Device' button to program the PIC (see Figure 3). Verify that the device was successfully programmed (see Figure 4).

###### Figure 3: 'Make and Program Device' Button
![3](https://user-images.githubusercontent.com/74994048/100312836-4d5a9200-2f81-11eb-8d13-67e0eaa7c06e.png)



###### Figure 4: Program Complete
![4](https://user-images.githubusercontent.com/74994048/100312843-50558280-2f81-11eb-9705-2d38910e0c21.png)


7. Set up the conditioning circuit that goes on the PIC input and set up a simple transistor-relay conenction for the outputs, one for each output. Finally connect everything to the board as shown in figure 7 

###### Figure 5: Circuit Simulation Signal condition Set up
![5](https://user-images.githubusercontent.com/74994048/100349834-07202580-2fb7-11eb-8abf-b96cdcb307cb.jpeg)



###### Figure 6: Circuit Simulation transistor - relay  Set up
![6](https://user-images.githubusercontent.com/74994048/100350270-9c231e80-2fb7-11eb-94ba-c9be81f51c6a.jpeg)



###### Figure 7: Connection to the board
![7](https://user-images.githubusercontent.com/74994048/100352659-51a3a100-2fbb-11eb-9254-d8a36432b43f.png)

## Operation
After the Nano board is programmed, LED0 will toggle between its 'ON' and 'OFF' states every one second.
After the Nano board is programmed and the set up is done correctly, it will work based on the room temperature.
- If the room temperature is between 17°**C** and 21°**C** port RA4 of the board is set high. Turning a lightbulb on.
- If the room temperature is between 22°**C** and 26°**C** is considerate normal and the circuit will do nothing. 
- If the room temperature is between 27°**C** and 30°**C** port RA5 is set high. Turning a fan on. 

This actions can't overlapped, if one is working the others won't.

This can be done with the use of conditionals if/if else/else for each range and action.

###### Example 1: `Main()` Code Snippet

     void main(void) {
	    PIN_MANAGER_Initialize();	// Initialize 
	    ADC_con();
	    while(1){
	        conversion();           // 0 - 1023  17° y 30°
	        if(resultLow  >= 500)   //  >= 27°
	        {
	            CAL = 1;				// RA4 'ON'
	            FRI = 0;				// RA5 'OFF'
            
	        }
	        else if(resultLow < 300) // > 22°
	        {
	            CAL = 0;				//RA4 'OFF'
	            FRI = 1;				//RA5 'ON'
	        }
	        else                     //  between 22° and 27°
	        {
	            FRI = 0;				//RA4 'OFF'
	            CAL = 0;				//RA5 'OFF'
	        }
	    }        
	}
	       


## Summary
The 'Temperature modulator with PIC16F15244' code uses the PIC16F15244 curiosity nano development board and the ADC convertion alongside LM35 sensor to carry out an action that modulates the room temperature. Once programmed, PORTs RA4 and RA5 on the nano board will go 'ON' or 'OFF' based on a room temperatue range prestablished.
