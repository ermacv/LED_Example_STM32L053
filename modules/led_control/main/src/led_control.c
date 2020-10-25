#include <stddef.h>

#include "led_control.h"
#include "pwm_timer.h"
#include "counter_timer.h"

#define kMIN_PCT (0)
#define kMAX_PCT (100)
#define kPCT_MIN_STEP (1)
#define kDMA_BUF_SIZE ((kMAX_PCT * kPCT_MIN_STEP) * 2)
#define kTIMER_EDGES_PRESCALER (479)
#define kTIMER_STABLE_PRESCALER (47999)

typedef enum
{
  kLED_CONTROL_RC_OK,
  kLED_CONTROL_RC_ERR,
}led_control_rc_t;

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

static led_control_rc_t led_control_prepare_data(char *buf, size_t buf_size, size_t max_points)
{
  if ((NULL == buf) || (buf_size < (max_points * 2)))
  {
    return kLED_CONTROL_RC_ERR;
  }

  for (size_t i = 0; i < max_points; i++)
  {
    buf[i] = i + 1;
    buf[((max_points)*2 - 1) - i] = i;
  }

  return kLED_CONTROL_RC_OK;
}

static led_control_rc_t led_control_calc_preset_data(led_cfg_t *led_cfg, led_desc_t *led_desc)
{
  if ((NULL == led_cfg) || (NULL == led_desc))
  {
    return kLED_CONTROL_RC_ERR;
  }

  if ((led_cfg->max_brightness_pct > kMAX_PCT) || (kMIN_PCT == led_cfg->max_brightness_pct))
  {
    return kLED_CONTROL_RC_ERR;
  }

  if ((0 == led_cfg->t1_ms) || (0 == led_cfg->t2_ms) || (0 == led_cfg->t3_ms))
  {
    return kLED_CONTROL_RC_ERR;
  }

  led_control_rc_t rc = prepare_data(led_cfg->data_buf, led_cfg->data_buf_size, led_cfg->max_brightness_pct);

  if (kLED_CONTROL_RC_OK != rc)
  {
    return rc;
  }

  led_desc->rising.tmr_desc.tmr_psc = kTIMER_EDGES_PRESCALER;
  led_desc->rising.tmr_desc.tmr_arr = (led_cfg->t1_ms * kMAX_PCT) / led_cfg->max_brightness_pct;
  led_desc->rising.dma_buf_size = led_cfg->max_brightness_pct;
  led_desc->rising.dma_buf = led_cfg->data_buf;

  led_desc->falling.tmr_desc.tmr_psc = kTIMER_EDGES_PRESCALER;
  led_desc->falling.tmr_desc.tmr_arr = (led_cfg->t2_ms * kMAX_PCT) / led_cfg->max_brightness_pct;
  led_desc->falling.dma_buf_size = led_cfg->max_brightness_pct;
  led_desc->falling.dma_buf = led_cfg->data_buf + led_cfg->max_brightness_pct;

  led_desc->stable.tmr_psc = kTIMER_STABLE_PRESCALER;
  led_desc->stable.tmr_arr = led_cfg->t3_ms;

  return kLED_CONTROL_RC_OK;
}
