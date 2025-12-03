#include <16F877A.h>
#use delay(crystal = 8000000)
#fuses HS
void main()
{
    while (true)
    {
        output_high(PIN_B7);
        delay_ms(0.5);
        output_low(PIN_B7);
        delay_ms(0.5);
    }
}