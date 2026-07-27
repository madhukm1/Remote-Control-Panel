
#include "../app_layer/system_config.h"

#define RxData_Size      34

unsigned char checksum_byte;
unsigned char buf_To_CalChecksum[33];
unsigned char Calculated_checksum;
unsigned char received_data[31];         
unsigned char Lcd2_17bytes[17];
unsigned char Lcd18_33bytes[17];

uint8_t Com_UART_Receive_string(void);
void Com_UART_send_string(unsigned char txData[], unsigned int tx_Frame_length);
void RxData_Process(void);
bool Store_RxData_Into_Queue();     

