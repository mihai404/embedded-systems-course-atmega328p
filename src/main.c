#include "drivers/gpio/gpio.h"
#include "bsp/nano.h"
#include "utils/delay.h"

int main(void) {
    // 1. Inițializăm cei 4 pini pentru cele 4 LED-uri
    // D10 = Bit 0 (1), D11 = Bit 1 (2), D12 = Bit 2 (4), D13 = Bit 3 (8)
    GPIO_Init(D10, GPIO_OUTPUT);
    GPIO_Init(D11, GPIO_OUTPUT);
    GPIO_Init(D12, GPIO_OUTPUT);
    GPIO_Init(D13, GPIO_OUTPUT);

    uint8_t counter = 0;

    while (1) {
        // 2. Afișăm valoarea curentă a contorului în format binar
        
        // Verificăm Bit 0 (valoarea 1) -> D10
        if (counter & 0x01) GPIO_Write(D10, GPIO_HIGH); else GPIO_Write(D10, GPIO_LOW);
        
        // Verificăm Bit 1 (valoarea 2) -> D11
        if (counter & 0x02) GPIO_Write(D11, GPIO_HIGH); else GPIO_Write(D11, GPIO_LOW);
        
        // Verificăm Bit 2 (valoarea 4) -> D12
        if (counter & 0x04) GPIO_Write(D12, GPIO_HIGH); else GPIO_Write(D12, GPIO_LOW);
        
        // Verificăm Bit 3 (valoarea 8) -> D13
        if (counter & 0x08) GPIO_Write(D13, GPIO_HIGH); else GPIO_Write(D13, GPIO_LOW);

        // 3. Așteptăm o secundă înainte de următorul număr
        Delay(1000);

        // 4. Incrementăm contorul
        counter++;

        // 5. Resetăm la 0 dacă depășim 15 (4 biți: 0-15)
        if (counter > 15) {
            counter = 0;
        }
    }
}