
#include "Uart_Com.h"

unsigned char RxData_Buff[RxData_Size+2] = {'0'}; 
int i =0;

/*-----------------------------------------------------------------------------*
 *  NAME
 *     Com_UART_send_string
 *
 *  DESCRIPTION
 *     sending string data
 *     
 *  PARAMETERS
 *    txData : string data 
 *     tx_Frame_length : string length
 *
 *  RETURNS
 *      Returns nothing 
 *----------------------------------------------------------------------------*/
void Com_UART_send_string(unsigned char txData[], unsigned int tx_Frame_length)
{
    for(unsigned int i=0; i < tx_Frame_length; i++) 
    {
        EUSART_Write(txData[i]);
    }
}  

/*-----------------------------------------------------------------------------*
 *  NAME
 *     Com_UART_Receive_string
 *
 *  DESCRIPTION
 *     receiving string data
 *     
 *  PARAMETERS
 *    void
 *
 *  RETURNS
 *      Returns nothing 
 *----------------------------------------------------------------------------*/

uint8_t Com_UART_Receive_string(void)
{
    uint8_t Uart_RxData;
    Uart_RxData = EUSART_Read( );
    return Uart_RxData;
    
}

/*-----------------------------------------------------------------------------*
 *  NAME
 *     RxData_Process
 *
 *  DESCRIPTION
 *     processing the received data after fetching from queue
 *     
 *  PARAMETERS
 *    void
 *
 *  RETURNS
 *      Returns nothing 
 *----------------------------------------------------------------------------*/

void RxData_Process(void)
{ 
    uint8_t temp_buf[RxData_Size+2]={0}; 
    uint8_t Rem_Byte;
            
    if (Remove_ESPUartQueue(&ESPUart3Queue,&Rem_Byte) && Rem_Byte == '$')
    {
        RxData_Buff[0] = Rem_Byte;
    }
    if(RxData_Buff[0] == '$')
    {
        for(i=1; i<RxData_Size; )
        {
            if(Remove_ESPUartQueue(&ESPUart3Queue,&Rem_Byte))
            {
                RxData_Buff[i] = Rem_Byte;
                i++;
            }
        }
        for(int j=0; j<RxData_Size; j++)
        {
            temp_buf[j] = RxData_Buff[j];
            //EUSART_Write(temp_buf[j]);
        }
        temp_buf[RxData_Size] = '\0';
        memset(RxData_Buff, 0, sizeof(RxData_Buff));
        //Com_UART_send_string(temp_buf,RxData_Size);

        checksum_byte = temp_buf[33]; 
        strncpy(buf_To_CalChecksum, temp_buf,RxData_Size-1);
        Calculated_checksum = calculate_xor_checksum(buf_To_CalChecksum,RxData_Size - 1);

        if(Calculated_checksum == checksum_byte)
        {
            strncpy(received_data, buf_To_CalChecksum + 1, RxData_Size-1);
            strncpy(Lcd2_17bytes, (char*)received_data, 16);
            strncpy(Lcd18_33bytes, (char*)(received_data + 16), 16); 
            //clear_data();
            Go_To_start();
            print_data(Lcd2_17bytes);
            line_select(2);
            print_data(Lcd18_33bytes);
            memset(temp_buf, 0, sizeof(temp_buf));
        }
        else
        {
            clear_data();
            print_data("checksum failed");
            memset(temp_buf, 0, sizeof(temp_buf));
        }
    }
    else
    {
        memset(RxData_Buff, 0, sizeof(RxData_Buff));
    }
}