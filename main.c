

#include "./app_layer/system_config.h"
#include "./mcc_generated_files/eusart.h"

void main(void)
{
    
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    lcd_initialize();
    LATCbits.LATC5=1;
    LATCbits.LATC0=1;
    GPIO_Init();
    Init_ESPUartQueue(&ESPUart3Queue);
    
    while (1)
    {
        button_status();
        RxData_Process();
    }
}