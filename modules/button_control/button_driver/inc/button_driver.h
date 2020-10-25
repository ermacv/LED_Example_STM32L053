#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

/**
 * @brief
 * @addtogroup
 * @{
 */

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
  bool isBeingPressed;
  bool wasPressed;
  bool isShort;
  bool isLong;
  bool isBeingProcessed;
  bool lastState;
  bool wasHandled;
  uint16_t counter;
} button_t;

void button_driver_process(void);
// void button_driver_clear_event(volatile button_t *button);
bool button_driver_was_switch_button_pressed(void);

#endif // BUTTON_DRIVER_H

    /** @} */