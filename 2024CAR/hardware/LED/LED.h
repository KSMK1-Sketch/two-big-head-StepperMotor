#ifndef __LED_H_
#define __LED_H_

#include "A_include.h"

#define LEDG(x) ((x) ? (DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_2)) : (DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_2)))
#define LEDB(x) ((x) ? (DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_22)) : (DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_22)))

void LED_Test(void);

#endif
