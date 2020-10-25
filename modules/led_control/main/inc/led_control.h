#ifndef LED_CONTROL_H
#define LED_CONTROL_H

/**
 * @brief
 * @addtogroup
 * @{
 */

typedef enum
{
  kLED_CONTROL_NUM_1,
  kLED_CONTROL_NUM_2,
  kLED_CONTROL_NUM_3
} led_control_t;

void led_control_start(led_control_t led_num);
void led_control_stop(void);
void led_control_process(void);

#endif // LED_CONTROL_H

/** @} */