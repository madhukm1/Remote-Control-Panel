

#include "../app_layer/system_config.h"
#include "GPIO_COM.h"

unsigned char data_buffer[txFramelength] = {0};

uint8_t release_flag1 = 0;
uint8_t release_flag2 = 0;
uint8_t release_flag3 = 0;
uint8_t release_flag4 = 0;
uint8_t release_flag5 = 0;

void GPIO_Init(void)
{
    TRISB = 0x1F;                           
}

void debounce(void)
{
    __delay_ms(20);                   
}

void button_status()
{
    //if((flag_Button1 == FALSE)|| (flag_Button2 == FALSE) || (flag_Button3 == FALSE)||(flag_Button4 == FALSE)||(flag_Button5 == FALSE))
    //{
        Output_selection_Button1();
        Screen_selection_Button2();
        NextVideo_Selection();
        PreviousVideo_Selection();
        Enter_Button();
    //}
}
/*-----------------------------------------------------------------------------*
 *  NAME
 *     Input_reading_data  
 *
 *  DESCRIPTION
 *    Reading  5 input button data
 *     
 *  PARAMETERS
 *     void
 *
 *  RETURNS
 *      void
 *----------------------------------------------------------------------------*/
 void Input_reading_data(void)
{
     if((flag_Button1 == TRUE) || (flag_Button2 == TRUE) || (flag_Button3 == TRUE) || (flag_Button4 == TRUE) || (flag_Button5 == TRUE))
     {
        data_buffer[0] = START_FRAME;
        data_buffer[6] = calculate_xor_checksum(data_buffer,Lenght);
        Com_UART_send_string(data_buffer,txFramelength);
        
        flag_Button1 = FALSE;
        flag_Button2 = FALSE;
        flag_Button3 = FALSE;
        flag_Button4 = FALSE;
        flag_Button5 = FALSE;
        
        //__delay_ms(200);
     }
}
/*-----------------------------------------------------------------------------*
 *  NAME
 *     Output_selection_Button1 
 *
 *  DESCRIPTION
 *    Reading input button 1 data
 *     
 *  PARAMETERS
 *     void
 *
 *  RETURNS
 *      true or false
 *----------------------------------------------------------------------------*/
 
bool Output_selection_Button1() 
{
    if(flag_Button1 == FALSE)
    {
        if (Button1 == FALSE) 
        {
            debounce();
            if ((Button1 == FALSE) && (release_flag1 == 0)) 
            {
                data_buffer[1] = '1'; 
                flag_Button1 = TRUE;
                Input_reading_data();
                release_flag1 = 1;
            }
            else
            {
                data_buffer[1] = '0';
            }
        }
        else
        {
            data_buffer[1] = '0';
            release_flag1 = 0;
        }
    }
}
/*-----------------------------------------------------------------------------*
 *  NAME
 *    Screen_selection_Button2
 *
 *  DESCRIPTION
 *    Reading input button 2 data
 *     
 *  PARAMETERS
 *     void
 *
 *  RETURNS
 *     true or false
 *----------------------------------------------------------------------------*/
bool Screen_selection_Button2() 
{
    if(flag_Button2 == FALSE)
    {
        if (Button2 == FALSE)
        {
            debounce();
            if ((Button2 == FALSE) && (release_flag2 == 0)) 
            {
                data_buffer[2] = '1';

                flag_Button2 = TRUE;
                Input_reading_data();
                release_flag2 = 1;
            }
            else
            {
                data_buffer[2] = '0';
            }
        }
        else
        {
            data_buffer[2] = '0';
            release_flag2 = 0;
        }
    }
}
/*-----------------------------------------------------------------------------*
 *  NAME
 *    NextVideo_Selection
 *
 *  DESCRIPTION
 *    Reading input button 3 data
 *     
 *  PARAMETERS
 *     void
 *
 *  RETURNS
 *      true or false
 *----------------------------------------------------------------------------*/
bool NextVideo_Selection()
{
    if(flag_Button3 == FALSE)
    {
        if (Button3 == FALSE)
        {
            debounce();
            if ((Button3 == FALSE) &&  (release_flag3 == 0))
            {
                data_buffer[3] = '1';
                flag_Button3 = TRUE;
                Input_reading_data();
                release_flag3 = 1;
            }
            else
            {
                data_buffer[3] = '0';
            }
        }
        else
        {
            data_buffer[3] = '0';
            release_flag3 = 0;
        }
    }
}
/*-----------------------------------------------------------------------------*
 *  NAME
 *     PreviousVideo_Selection 
 *
 *  DESCRIPTION
 *    Reading input button 4 data
 *     
 *  PARAMETERS
 *     void
 *
 *  RETURNS
 *      true or false
 *----------------------------------------------------------------------------*/
bool PreviousVideo_Selection() 
{
    if(flag_Button4 == FALSE)
    {
        if (Button4 == FALSE)
        {
            debounce();
            if ((Button4 == FALSE) && (release_flag4 == 0)) 
            {
                data_buffer[4] = '1';
                flag_Button4 = TRUE;
                Input_reading_data();
                release_flag4 = 1;
            }
            else
            {
                data_buffer[4] = '0';
            }
        }
        else
        {
            data_buffer[4] = '0';
            release_flag4 = 0;
        }
    }
}
/*-----------------------------------------------------------------------------*
 *  NAME
 *    Enter_Button
 *
 *  DESCRIPTION
 *    Reading input button 5 data
 *     
 *  PARAMETERS
 *     void
 *
 *  RETURNS
 *     true or false
 *----------------------------------------------------------------------------*/
bool Enter_Button() 
{
    if(flag_Button5 == FALSE)
    {
        if (Button5 == FALSE) 
        {
            debounce();
            if ((Button5 == FALSE) && (release_flag5 == 0)) 
            {
               flag_Button5 = TRUE;   
               data_buffer[5] = '1';
               Input_reading_data();
               release_flag5 = 1;
            }
            else
            {
               data_buffer[5] = '0';
            }
        }
        else
        {
           data_buffer[5] = '0';
           release_flag5 = 0;
        }
    }
}

 

// Other button functions (Screen_selection_Button2, NextVideo_Selection, PreviousVideo_Selection, Enter_Button)
// Implementation is similar to Output_selection_Button1, handling respective actions
