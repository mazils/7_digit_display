#include <Arduino.h>
#include "7_digit_display_driver.h"

int main(int argc, char const *argv[])
{
  init_7_segment_display();
  // display_number(0);
  parse_numbers(1234);

  while (1)
  {
    /* code */
  }
  
  return 0;
}
