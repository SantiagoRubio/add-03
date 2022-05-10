#include <stdio.h>
#include "pico/stdlib.h"
#include <math.h>
#include "hardware/adc.h"

void main() {

  float Temp0 = 298.0;
  float r0 = 10000.0;
  float beta = 3950.0;
  float r1 = 10000.0;
  float Vr2;
  float r2;

  adc_init();
  adc_gpio_init(26);
  adc_select_input(0);

  while (1) {
    const float conversion_factor = 3.3f / (1 << 12);
    uint16_t result = adc_read();

    Vr2 = conversion_factor * result;
    r2 = r1 / ((3.3f / Vr2)-1);
    float TempK = beta /(log(r2/r0) + (beta/Temp0));

    printf ("Temperatura: %.2f K, Resistencia variable: %.2f Kohms, Voltaje r2: %.2f V\n", TempK, r2 / 1000, Vr2);
    sleep_ms(250);
  }
}