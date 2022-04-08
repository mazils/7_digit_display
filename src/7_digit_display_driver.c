#include "7_digit_display_driver.h"
const static uint8_t digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, DOT};
void init_7_segment_display()
{
    DDRA |= 0xFF;
    // SI
    DDRB |= _BV(DDB0);
    // SCK
    DDRB |= _BV(DDB1);
    // RCK
    DDRB |= _BV(DDB2);
    // digits
    DDRF |= _BV(DDF0);
    DDRF |= _BV(DDF1);
    DDRF |= _BV(DDF2);
    DDRF |= _BV(DDF3);
    // pull high
    PORTF |= _BV(PF3);
    PORTF |= _BV(PF2);
    PORTF |= _BV(PF1);
    PORTF |= _BV(PF0);
    // timer innit
    OCR4A = 156; // tick value to get 100hz update frequency
    // Set OCnA/OCnB/OCnC on compare match (set output to high level)
    TCCR4A |= _BV(COM4A0);
    // Selecting a clock source prescaler, in
    // that case it is clk/1024, because 1
    // second is tiny enough to use with
    // this prescaler
    TCCR4B |= (_BV(CS40)) | (_BV(CS41));
    // Clock mode (CTC) is in register B
    TCCR4B |= _BV(WGM42);
    // Enable Timer Interrupt Mask
    TIMSK4 |= _BV(OCIE4A);
    // enable global interupts
    sei();
}
void display_number(uint8_t number)
{
    // set SCK and RCK to 0
    PORTB &= ~(_BV(PB1));
    PORTB &= ~(_BV(PB0));
    // write byte least starting from significant
    for (int i = 0; i < 8; i++)
    {
        // if 0b number == 0 then write
        uint8_t bit = (digits[number] >> (i)) & 1;
        if (bit == 0)
        {
            PORTB &= ~(_BV(PB2));
        }
        else
        {
            PORTB |= _BV(PB2);
        }
        // pull SCK high to write
        PORTB |= _BV(PB1);
        // pull SCK LOW
        PORTB &= ~(_BV(PB1));
        // in the end pull up RCK
    }
    // RCK to high to save(push from buffer and save)
    PORTB |= _BV(PB0);
}
void parse_numbers(uint16_t numbers)
{
    if (numbers > 9999)
    {
        return 0;
    }
    fourth_digit = numbers % 10;
    third_digit = (numbers / 10) % 10;
    second_digit = (numbers / 100) % 10;
    first_digit = (numbers / 1000) % 10;
    parsed_four_digits[0] = first_digit;
    parsed_four_digits[1] = second_digit;
    parsed_four_digits[2] = third_digit;
    parsed_four_digits[3] = fourth_digit;
}

ISR(TIMER4_COMPA_vect)
{
    PORTF |= _BV(0) | _BV(1) | _BV(2) | _BV(3);
    display_number(parsed_four_digits[digit_number]);
    PORTF &= ~(_BV(digit_number));
    digit_number++;
    if (digit_number == 4)
    {
        digit_number = 0;
    }
}