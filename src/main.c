#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"
#include "bsp/nano.h"

int main(void) {
    
    Timer0_Init();

    
    GPIO_Init(LED_BUILTIN, GPIO_OUTPUT);

    uint32_t last_time1 = 0;
    uint32_t last_time2 = 0;
    uint32_t last_time3 = 0;

    while (1) {

            
        if (Millis() - last_time1 >= 1000) {
            last_time1 = Millis();
            GPIO_Toggle(LED_BUILTIN);
        }
        if (Millis() - last_time2 >= 4000) {
            last_time2 = Millis();
            GPIO_Toggle(LED_BUILTIN);
        }
        if (Millis() - last_time3 >= 1000) {
            last_time3 = Millis();
            GPIO_Toggle(LED_BUILTIN);
        }
    }
}