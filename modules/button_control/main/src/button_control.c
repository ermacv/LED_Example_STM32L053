#include "button_control.h"
#include "button_driver.h"
#include "led_control.h"

static led_control_t current_led = kLED_CONTROL_NUM_1;

void button_control_init(void)
{
  // Not implemented
}

void button_control_process(void)
{
  bool was_switch_button_pressed = button_driver_was_switch_button_pressed();

  if (true == was_switch_button_pressed)
  {
    led_control_start(current_led);

    if (current_led < kLED_CONTROL_NUM_LAST)
    {
      current_led++;
    }
    else
    {
      current_led = kLED_CONTROL_FIRST;
    }
  }
}

void button_control_deinit(void)
{
  // Not implemented
}
