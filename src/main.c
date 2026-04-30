#include <stdint.h>
#include "drivers/adc/adc.h"
#include "bsp/nano.h"

int main(void)
{
    // 1. Initializeaza ADC-ul
    ADC_Init();

    // Declararea variabilei pentru stocare (uint16_t conform cerintei)
    uint16_t adc_value;

    while (1)
    {
        // 2. Citeste continuu valoarea de pe pinul A0
        // 3. Stocheaza rezultatul in variabila uint16_t
        adc_value = ADC_Read(0); 
        
        // Optional: Aici se pot adauga intarzieri (delay) pentru stabilitate
    }
}