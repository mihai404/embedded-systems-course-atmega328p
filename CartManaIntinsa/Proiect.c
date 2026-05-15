#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h" // Presupunând că timer0 oferă PWM
#include "bsp/nano.h"
#include <util/delay.h>

// Definirea pinilor conform structurii cursului
// LDR pe A0 (ADC0)
// LED pe un pin care suportă PWM (de obicei D6/PD6 pe Nano pentru Timer0)

void setup() {
    // Inițializare comunicare Serială (dacă driverul serial.h există)
    // În screenshot-ul tău Serial.begin dă eroare pentru că nu este inclus header-ul de serial
    // Dacă vrei doar funcționalitate LED + Senzor:
    
    // Configurare pin LED ca ieșire
    gpio_set_mode(PIN_D6, OUTPUT); 
}

void loop() {
    // Citire valoare analogică
    // În acest curs, funcția se numește probabil adc_read sau similar
    // Dacă nu ai un driver de ADC gata, folosim citirea directă pe regiștri:
    
    ADMUX = (1 << REFS0); // Referință AVcc
    ADCSRA |= (1 << ADSC) | (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    
    while(ADCSRA & (1 << ADSC)); // Așteaptă conversia
    uint16_t valoareSenzor = ADCW;

    // Mapare manuală (Invers: lumină multă -> intensitate mică)
    // 1023 -> 0, 0 -> 255
    uint8_t intensitateLED = 255 - (valoareSenzor / 4);

    // Scrierea valorii PWM
    // Folosim registrul OCR0A (aferent pinului D6) pentru a controla luminozitatea
    OCR0A = intensitateLED;

    _delay_ms(50);
}

// Dacă sistemul tău de build folosește un main.c separat care apelează setup/loop:
int main(void) {
    setup();
    while(1) {
        loop();
    }
}



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