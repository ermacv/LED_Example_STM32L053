#include "stm32l0xx_ll_tim.h"

#include "pwm_timer.h"

void pwm_timer_init(void)
{
  LL_TIM_OC_SetCompareCH1(TIM21, 0);
  LL_TIM_CC_EnableChannel(TIM21, LL_TIM_CHANNEL_CH1);
  LL_TIM_EnableCounter(TIM21);
}

uint32_t pwm_timer_get_periph_address(void)
{
  return (uint32_t)(&TIM21->CCR1);
}

void pwm_timer_save_val_to_periph(uint16_t val)
{
  LL_TIM_OC_SetCompareCH1(TIM21, val);
}

void pwm_timer_deinit(void)
{
  // Not implemented
}
