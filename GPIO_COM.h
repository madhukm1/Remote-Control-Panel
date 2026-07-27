/* 
 * File:   GPIO_COM.h
 * Author: Win10 Pro
 *
 * Created on December 14, 2024, 1:01 PM
 */

#ifndef GPIO_COM_H
#define	GPIO_COM_H

#ifdef	__cplusplus
extern "C" {
#endif

//#include <xc.h>
//#include <stdint.h>
//#include <stdbool.h>
//#include "mcc.h" 
    
#include "../app_layer/system_config.h"
#include "../app_layer/crc1.h"

#define TRUE 1
#define FALSE 0
// Button configurations
#define Button1 PORTBbits.RB0
#define Button2 PORTBbits.RB1
#define Button3 PORTBbits.RB2
#define Button4 PORTBbits.RB3
#define Button5 PORTBbits.RB4

// Button state flags
 bool flag_Button1 = FALSE;
 bool flag_Button2 = FALSE;
 bool flag_Button3 = FALSE;
 bool flag_Button4 = FALSE;
 bool flag_Button5 = FALSE;
 
 bool button_pressed = FALSE;

// Button state variables
static uint8_t var_Button1;
static uint8_t var_Button2;
 
// Function prototypes
void button_status();
void Input_reading_data(void); 
void GPIO_Init(void);
void debounce(void);
bool Output_selection_Button1(void);
bool Screen_selection_Button2(void);
bool NextVideo_Selection(void);
bool PreviousVideo_Selection(void);
bool Enter_Button(void);



#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_COM_H */

