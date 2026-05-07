#include <stdint.h>

#ifndef LED_H
#define LED_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint8_t mask;
  uint8_t state;
} LED;


void Led_init(LED *led);
void Led_on(LED *led);
void Led_off(LED *led);
void Led_toggle(LED *led);

#ifdef __cplusplus
}
#endif
#endif