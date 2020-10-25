
#include "stm32l0xx_ll_gpio.h"

#include "button_driver.h"
#include "button_driver_conf.h"

static volatile button_t switch_button;

static void button_driver_handler_it(volatile button_t *button, bool buttonState);
static void button_driver_clear_event(volatile button_t *button);

bool button_driver_was_switch_button_pressed(void)
{
  bool rc = false;
  if (switch_button.wasPressed)
  {
    button_driver_clear_event(&switch_button);
    rc = true;
  }
  return rc;
}

void button_driver_process(void)
{
  button_driver_handler_it(&switch_button, !(LL_GPIO_ReadInputPort(kBUTTON_PORT) & kBUTTON_PIN));
}

static void button_driver_clear_event(volatile button_t *button)
{
  button->isBeingProcessed = true;

  button->isLong = false;
  button->wasHandled = false;
  button->isShort = false;
  button->isBeingPressed = false;
  button->wasPressed = false;
  button->counter = 0;
  button->lastState = false;

  button->isBeingProcessed = false;
}

static void button_driver_handler_it(volatile button_t *button, bool buttonState)
{
  if (button->isBeingProcessed)
    return;

  if (buttonState)
  {
    if (button->counter < LONG_PRESS)
      button->counter++;

    button->isBeingPressed = true;
    button->wasPressed = false;

    if (button->counter >= LONG_PRESS)
    {
      button->isLong = true;
      button->isShort = false;
    }
    else if (button->counter >= SHORT_PRESS)
    {
      button->isLong = false;
      button->isShort = true;
    }
    else
    {
      button->isLong = false;
      button->isShort = false;
    }
  }
  else if (buttonState != button->lastState)
  {
    button->isBeingPressed = false;
    button->wasPressed = true;
    button->counter = 0;
  }
  button->lastState = buttonState;
}
