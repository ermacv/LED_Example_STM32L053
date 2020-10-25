#include <stddef.h>

#include "led_control.h"
#include "pwm_timer.h"
#include "counter_timer.h"

void led_control_start(led_control_t led_num)
{
  switch (led_num)
  {
  case kLED_CONTROL_NUM_1:
    /* code */
    break;

  case kLED_CONTROL_NUM_2:
    /* code */
    break;

  case kLED_CONTROL_NUM_3:
    /* code */
    break;

  default:
  led_control_stop();
    break;
  }

}

void led_control_stop(void)
{

}

void led_control_process(void)
{

}

static int led_control_prepare_data(char *buf, size_t buf_size, size_t max_points)
{
  if ((NULL == buf) || (buf_size < (max_points * 2)))
  {
    return -1;
  }

  for (size_t i = 0; i < max_points; i++)
  {
    buf[i] = i + 1;
    buf[((max_points)*2 - 1) - i] = i;
  }

  return 0;
}

static int led_control_calc_preset_data(led_cfg_t *led_cfg, led_desc_t *led_desc)
{
  if ((NULL == led_cfg) || (NULL == led_desc))
  {
    return -1;
  }

  if ((led_cfg->max_brightness_pct > 100) || (0 == led_cfg->max_brightness_pct))
  {
    return -1;
  }

  if ((0 == led_cfg->t1_ms) || (0 == led_cfg->t2_ms) || (0 == led_cfg->t3_ms))
  {
    return -1;
  }

  int rc = prepare_data(led_cfg->data_buf, led_cfg->data_buf_size, led_cfg->max_brightness_pct);

  if (0 != rc)
  {
    return -1;
  }

  led_desc->rising.tmr_desc.tmr_psc = 479;
  led_desc->rising.tmr_desc.tmr_arr = (led_cfg->t1_ms * 100) / led_cfg->max_brightness_pct;
  led_desc->rising.dma_buf_size = led_cfg->max_brightness_pct;
  led_desc->rising.dma_buf = led_cfg->data_buf;

  led_desc->falling.tmr_desc.tmr_psc = 479;
  led_desc->falling.tmr_desc.tmr_arr = (led_cfg->t2_ms * 100) / led_cfg->max_brightness_pct;
  led_desc->falling.dma_buf_size = led_cfg->max_brightness_pct;
  led_desc->falling.dma_buf = led_cfg->data_buf + led_cfg->max_brightness_pct;

  led_desc->stable.tmr_psc = 47999;
  led_desc->stable.tmr_arr = led_cfg->t3_ms;

  return 0;
}
