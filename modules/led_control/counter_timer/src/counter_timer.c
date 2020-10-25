#include <stddef.h>
#include <stdint.h>

#include "stm32l0xx_ll_dma.h"
#include "stm32l0xx_ll_tim.h"

#include "counter_timer.h"
#include "pwm_timer.h"

void counter_timer_load_edge(led_edge_t *edge)
{
  LL_TIM_DisableCounter(TIM6);
  LL_TIM_DisableIT_UPDATE(TIM6);
  LL_TIM_SetPrescaler(TIM6, edge->tmr_desc.tmr_psc);
  LL_TIM_SetAutoReload(TIM6, edge->tmr_desc.tmr_arr);
  if (LL_TIM_IsActiveFlag_UPDATE(TIM6))
    LL_TIM_ClearFlag_UPDATE(TIM6);

  LL_TIM_GenerateEvent_UPDATE(TIM6);

  while (!LL_TIM_IsActiveFlag_UPDATE(TIM6))
    ;

  LL_TIM_EnableDMAReq_UPDATE(TIM6);

  LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);

  LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_2, pwm_timer_get_periph_address());
  LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_2, (uint32_t)edge->dma_buf);
  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, edge->dma_buf_size);
  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_NORMAL);
  LL_DMA_ClearFlag_TC3(DMA1);
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);

  LL_TIM_EnableCounter(TIM6);
}

void counter_timer_load_stable(led_tmr_t *stable)
{
  LL_TIM_DisableCounter(TIM6);
  LL_TIM_DisableUpdateEvent(TIM6);

  LL_TIM_SetPrescaler(TIM6, stable->tmr_psc);
  LL_TIM_SetAutoReload(TIM6, stable->tmr_arr);
  if (LL_TIM_IsActiveFlag_UPDATE(TIM6))
    LL_TIM_ClearFlag_UPDATE(TIM6);

  LL_TIM_EnableUpdateEvent(TIM6);

  LL_TIM_GenerateEvent_UPDATE(TIM6);

  while (!LL_TIM_IsActiveFlag_UPDATE(TIM6))
    ;

  LL_TIM_ClearFlag_UPDATE(TIM6);

  LL_TIM_EnableIT_UPDATE(TIM6);
  LL_TIM_EnableCounter(TIM6);
}

void counter_timer_stop_led(void)
{
  LL_TIM_DisableCounter(TIM6);
  pwm_timer_save_val_to_periph(0);
}
