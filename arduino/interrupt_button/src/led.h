#ifndef BUTTON_H
#define BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint8_t mask;
  uint8_t state;
  unsigned long last_blink_time;
  unsigned long blink_interval;
} LED;


void led_init(LED *led);
void led_on(LED *led);
void led_off(LED *led);
void led_toggle(LED *led);

#ifdef __cplusplus
}
#endif
#endif