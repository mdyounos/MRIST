#include <avr/io.h>        // AVR হার্ডওয়্যার রেজিস্টার ব্যবহারের জন্য
#include <avr/interrupt.h> // ইন্টারাপ্ট ব্যবহারের জন্য

volatile uint16_t event_count = 0; // volatile = change any time, uint16_t = 16 bit unsigned integer, event_count = counter variable

//------------------- Timer1 Compare Match Interrupt -------------------//
ISR(TIMER1_COMPA_vect)
{
    // Timer1 CTC মোডে OCR1A মানে পৌঁছালে এই ইন্টারাপ্ট চালু হবে
    event_count++; // প্রতি ১ সেকেন্ডে কাউন্টার ১ করে বাড়বে
}

//------------------- Timer1 Initialization Function -------------------//
void timer1_init()
{

    // Timer1 কে CTC মোডে সেট করা (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);

    // Prescaler = 256 নির্বাচন করা
    // Clock = 16MHz / 256 = 62.5kHz
    TCCR1B |= (1 << CS12);

    // OCR1A এর মান সেট করা—62499 হলে Timer1 প্রতি ১ সেকেন্ডে interrupt দেবে
    // কারণ: 62,500Hz → 62,500 count = 1 second
    OCR1A = 62499;

    // Output Compare A Match Interrupt Enable
    TIMSK1 |= (1 << OCIE1A);

    // Global interrupt enable
    sei(); // Set Enable Interrupts না দিলে ISR() রান হবে না
}

int main(void)
{

    // PB5 (Arduino Uno তে LED pin 13) কে output করা
    DDRB |= (1 << DDB5);

    // Timer1 স্টার্ট করা
    timer1_init();
    while (1)
    {
        // event_count প্রতি সেকেন্ডে বেড়ে ১০০০ হয়
        if (event_count >= 1000)
        {
            PORTB ^= (1 << PORTB5); // LED toggle করা
            event_count = 0;        // কাউন্টার রিসেট
        }
    }
    return 0;
}
