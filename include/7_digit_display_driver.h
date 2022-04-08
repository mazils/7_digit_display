#pragma once
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define ZERO  0b00000011
#define ONE  0b10011111
#define TWO  0b00100101
#define THREE  0b00001101
#define FOUR  0b10011001
#define FIVE  0b01001011
#define SIX  0b01000001
#define SEVEN  0b00011111
#define EIGHT  0b00000001
#define NINE  0b00001001
#define DOT  0b11111110

uint8_t first_digit;
uint8_t second_digit;
uint8_t third_digit;
uint8_t fourth_digit;
uint8_t parsed_four_digits[4];
uint8_t digit_number = 0;
void init_7_segment_display();
void display_number(uint8_t number);
void parse_numbers(uint16_t numbers);
