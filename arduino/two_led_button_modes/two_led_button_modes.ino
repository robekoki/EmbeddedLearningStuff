#include <stdint.h>

typedef enum {
  BLINKING,
  FAST_BLINKING,
  OFF
} LED_MODE;

typedef struct {
  uint8_t mask;
  uint8_t state;
  unsigned long last_blink_time;
  unsigned long blink_interval;
} LED;

typedef struct {
  uint8_t mask;
  uint8_t prev;
  unsigned long last_press_time;
  unsigned long debounce_ms;
} Button;

/* ---------- Global state ---------- */
static LED_MODE mode = OFF;

static LED led1 = { (1u << 5), 0, 0, 500ul };
static LED led2 = { (1u << 4), 0, 0, 700ul };

static Button btn = { (1u << 0), 1 , 0, 50ul };

/* ---------- LED driver ---------- */

void led_init(LED *led) {
  DDRB |= led->mask;
  PORTB &= ~led->mask;
  led->state = 0;
  led->last_blink_time = millis();
}

void led_on(LED *led) {
  PORTB |= led->mask;
  led->state = 1;
}

void led_off(LED *led) {
  PORTB &= ~led->mask;
  led->state = 0;
}

void led_toggle(LED *led) {
  if (led->state) {
    led_off(led);
  } else {
    led_on(led);
  }
}

void led_blink(LED *led) {
  if (mode == OFF || led->blink_interval == 0ul) {
    led_off(led);
    return;
  }

  unsigned long now = millis();

  if ((now - led->last_blink_time) >= led->blink_interval) {
    led_toggle(led);
    led->last_blink_time += led->blink_interval;
  }
}

/* ---------- Mode control ---------- */

void cycle_mode(LED *led1, LED *led2) {
  switch (mode) {
    case OFF:
      mode = BLINKING;
      led1->blink_interval = 500ul;
      led2->blink_interval = 250ul;   // drift
      break;

    case BLINKING:
      mode = FAST_BLINKING;
      led1->blink_interval = 100ul;
      led2->blink_interval = 50ul;    // drift
      break;

    case FAST_BLINKING:
      mode = OFF;
      led1->blink_interval = 0ul;
      led2->blink_interval = 0ul;
      led_off(led1);
      led_off(led2);
      break;
  }

  unsigned long now = millis();
  led1->last_blink_time = now;
  led2->last_blink_time = now;
}

/* ---------- Button driver ---------- */

void button_init(Button *btn) {
  DDRB &= ~btn->mask;   // input
  PORTB |= btn->mask;   // internal pull-up

  btn->prev = button_read(btn);
  btn->last_press_time = millis();
}

uint8_t button_read(Button *btn) {
  return (PINB & btn->mask) ? 1u : 0u;
}

uint8_t button_press_event(Button *btn) {
  unsigned long now = millis();
  uint8_t curr = button_read(btn);

  if ((btn->prev == 1u) &&
      (curr == 0u) &&
      ((now - btn->last_press_time) >= btn->debounce_ms)) {
    btn->last_press_time = now;
    btn->prev = curr;
    return 1u;
  }

  btn->prev = curr;
  return 0u;
}

/* ---------- Application ---------- */

void setup(void) {
  led_init(&led1);
  led_init(&led2);
  button_init(&btn);
}

void loop(void) {
  if (button_press_event(&btn)) {
    cycle_mode(&led1, &led2);
  }

  led_blink(&led1);
  led_blink(&led2);
}
