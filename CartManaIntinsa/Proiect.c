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