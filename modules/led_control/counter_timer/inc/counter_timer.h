#ifndef COUNTER_TIMER_H
#define COUNTER_TIMER_H

/**
 * @brief
 * @addtogroup
 * @{
 */

#include <stddef.h>
#include <stdint.h>

typedef struct
{
  uint16_t t1_ms;
  uint16_t t2_ms;
  uint16_t t3_ms;
  char max_brightness_pct;
  char *data_buf;
  size_t data_buf_size;
} led_cfg_t;

typedef struct
{
  uint16_t tmr_arr;
  uint16_t tmr_psc;
} led_tmr_t;

typedef struct
{
  led_tmr_t tmr_desc;
  char *dma_buf;
  size_t dma_buf_size;
} led_edge_t;

typedef struct
{
  led_edge_t rising;
  led_edge_t falling;
  led_tmr_t stable;
} led_desc_t;

void counter_timer_load_edge(led_edge_t *edge);
void counter_timer_load_stable(led_tmr_t *stable);
void counter_timer_stop_led(void);

#endif // COUNTER_TIMER_H

/** @} */