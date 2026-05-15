#include <avr/io.h>
#include <delay.h>
#include "drivers/gpio/gpio.h"
#include "bsp/nano.h"

#define PRAG_LUMINA 500 

void ADC_Init(void) {
    ADMUX = (1 << REFS0); // Referință 5V
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
}

uint16_t ADC_Read(void) {
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    
    // Înlocuire ADCW pentru a evita erorile de tip "undefined"
    uint8_t low  = ADCL; 
    uint8_t high = ADCH; 
    return (high << 8) | low; 
}

int main(void) {
    GPIO_Init(LED_BUILTIN, GPIO_OUTPUT);
    GPIO_Init(D9, GPIO_OUTPUT); // LED-ul extern
    
    ADC_Init();

    while (1) {
        uint16_t valoare = ADC_Read();

        if (valoare < PRAG_LUMINA) {
            GPIO_Write(LED_BUILTIN, GPIO_HIGH);
            GPIO_Write(D9, GPIO_HIGH);
        } else {
            GPIO_Write(LED_BUILTIN, GPIO_LOW);
            GPIO_Write(D9, GPIO_LOW);
        }

        _delay_ms(50);
    }
    return 0;
}