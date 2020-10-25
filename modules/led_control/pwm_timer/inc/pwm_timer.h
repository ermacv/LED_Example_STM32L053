#ifndef PWM_TIMER_H
#define PWM_TIMER_H

/**
 * @brief
 * @addtogroup
 * @{
 */

#include <stdint.h>

void pwm_timer_init(void);
uint32_t pwm_timer_get_periph_address(void);
void pwm_timer_save_val_to_periph(uint16_t val);
void pwm_timer_deinit(void);

#endif // PWM_TIMER_H

    /** @} */