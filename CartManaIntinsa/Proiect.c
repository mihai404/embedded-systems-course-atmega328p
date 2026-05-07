#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"
#include "bsp/nano.h"
// str. N-am: D2=R;D3=G;D4=V
// str. Nu Stiu: D5=R;D6=G;D7=V
// str. Nu vreau: D*=R;D9=G;D10=V
// str. Nu Pot: D11=R;D12=G;A7=V



int main(void) {
Timer0_Init();
GPIO_Init(LED_BUILTIN, GPIO_OUTPUT);

uint32_t last_time = 0;

while (1) {
if (Millis() - last_time >= 1000) {
last_time = Millis();
GPIO_Toggle(LED_BUILTIN);
}
}
}