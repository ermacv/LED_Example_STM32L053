#include <stddef.h>

#include "led_control_conf.h"
#include "led_control.h"
#include "pwm_timer.h"
#include "counter_timer.h"

#define kMIN_PCT (0)
#define kMAX_PCT (100)
#define kPCT_MIN_STEP (1)
#define kDMA_BUF_SIZE ((kMAX_PCT * kPCT_MIN_STEP) * 2)
#define kTIMER_EDGES_PRESCALER (479)
#define kTIMER_STABLE_PRESCALER (47999)

typedef enum led_control_rc_
{
  kLED_CONTROL_IDLE,
  kLED_CONTROL_PROCESS,
} led_control_state_t;

typedef enum led_control_state_
{
  kLED_CONTROL_RC_OK,
  kLED_CONTROL_RC_ERR,
} led_control_rc_t;

static volatile char dma_tc_int = 0;
static volatile char tim16_tc_int = 0;
static led_control_state_t state = kLED_CONTROL_IDLE;
static uint8_t led_process_mode_counter = 0;
led_desc_t led_desc;
static char dma_buf[kDMA_BUF_SIZE];

static led_control_rc_t led_control_prepare_data(char *buf, size_t buf_size, size_t max_points);
static led_control_rc_t led_control_calc_preset_data(led_cfg_t *led_cfg, led_desc_t *led_desc);
static void led_control_process_led(void);

    void DMA_TC_callback(void)
{
  dma_tc_int = 1;
}

void TMR_TC_callback(void)
{
  tim16_tc_int = 1;
}

void led_control_init(void)
{
  pwm_timer_init();
}

void led_control_deinit(void)
{
  // Not implemented
}

void led_control_start(led_control_t led_num)
{
  uint16_t t1, t2, t3;
  uint8_t max_brightness;

  switch (led_num)
  {
  case kLED_CONTROL_NUM_1:
    t1 = kLED_MODE_1_T1;
    t2 = kLED_MODE_1_T2;
    t3 = kLED_MODE_1_T3;
    max_brightness = kLED_MODE_1_MAX_BRIGHTNESS;
    break;

  case kLED_CONTROL_NUM_2:
    t1 = kLED_MODE_2_T1;
    t2 = kLED_MODE_2_T2;
    t3 = kLED_MODE_2_T3;
    max_brightness = kLED_MODE_2_MAX_BRIGHTNESS;
    break;

  case kLED_CONTROL_NUM_3:
    t1 = kLED_MODE_3_T1;
    t2 = kLED_MODE_3_T2;
    t3 = kLED_MODE_3_T3;
    max_brightness = kLED_MODE_3_MAX_BRIGHTNESS;
    break;

  default:
  led_control_stop();
    return;
    // break;
  }

  led_cfg_t led_cfg =
  {
    .data_buf = dma_buf,
    .data_buf_size = kDMA_BUF_SIZE,
    .max_brightness_pct = max_brightness,
    .t1_ms = t1,
    .t2_ms = t2,
    .t3_ms = t3
  };

  led_control_rc_t rc = led_control_calc_preset_data(&led_cfg, &led_desc);

  if (kLED_CONTROL_RC_OK == rc)
  {
    led_process_mode_counter = 0;
    state = kLED_CONTROL_PROCESS;
  }
}

void led_control_stop(void)
{
  state = kLED_CONTROL_IDLE;
  counter_timer_stop_led();
}

void led_control_process(void)
{
  if (kLED_CONTROL_IDLE != state)
  {
    led_control_process_led();
  }
}

static void led_control_process_led(void)
{
  static size_t led_process_mode_counter = 0;

  switch (led_process_mode_counter)
  {
  case 0:
    if (tim16_tc_int)
    {
      tim16_tc_int = 0;
      counter_timer_load_edge(&led_desc.rising);
      led_process_mode_counter++;
    }
    break;

  case 1:
    if (dma_tc_int)
    {
      dma_tc_int = 0;
      counter_timer_load_stable(&led_desc.stable);
      led_process_mode_counter++;
    }
    break;

  case 2:
    if (tim16_tc_int)
    {
      tim16_tc_int = 0;
      counter_timer_load_edge(&led_desc.falling);
      led_process_mode_counter++;
    }
    break;

  case 3:
    if (dma_tc_int)
    {
      dma_tc_int = 0;
      counter_timer_load_stable(&led_desc.stable);
      led_process_mode_counter = 0;
    }
    break;

  default:
    break;
  }
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

  led_control_rc_t rc = led_control_prepare_data(led_cfg->data_buf, led_cfg->data_buf_size, led_cfg->max_brightness_pct);

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
