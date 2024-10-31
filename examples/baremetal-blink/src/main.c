#include "sam4s.h"
#include "pio.h"

// example blinky pin PA8 (change as needed)
#define BLINKY_GPIO_PORT   PIOA
#define BLINKY_GPIO_PIN    PIO_PA8

// should be done with SysTick_Handler, but this is simpler
void wait_cycles(int ms); 

int main (void) {
  SystemCoreClockUpdate();
  PIO_SetOutput(
    BLINKY_GPIO_PORT, 
    BLINKY_GPIO_PIN, 
    0 /* default level */, 
    0 /* no open drain*/, 
    0 /* no pullup */
  );
  while (1) {
    PIO_Set(BLINKY_GPIO_PORT, BLINKY_GPIO_PIN);
    wait_cycles(10000);
    PIO_Clear(BLINKY_GPIO_PORT, BLINKY_GPIO_PIN);
    wait_cycles(10000);
  }
}

void wait_cycles(int ms) {
   while (ms-- > 0) {
      volatile int x=500; // just burn some cycles (inaccurate)
      while (x-- > 0)
         __asm("nop");
   }
}
