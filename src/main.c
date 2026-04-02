#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"
#include "bsp/nano.h"

int main(void) {
    // 1. Inițializăm sistemul de timp
    Timer0_Init();

    // 2. Definim pinii conform conexiunilor tale fizice
    GPIO_Init(D13, GPIO_OUTPUT); // Primul LED pe D13
    GPIO_Init(D12, GPIO_OUTPUT); // Al doilea LED pe D12

    uint32_t last_time1 = 0;
    uint32_t last_time2 = 0;

    while (1) {
        uint32_t current_time = Millis();

        // Logica pentru LED-ul de pe D13 (200 ms)
        if (current_time - last_time1 >= 800) {
            last_time1 = current_time;
            GPIO_Toggle(D13);
        }

        // Logica pentru LED-ul de pe D12 (1000 ms)
        if (current_time - last_time2 >= 1000) {
            last_time2 = current_time;
            GPIO_Toggle(D12);
        }
    }
}