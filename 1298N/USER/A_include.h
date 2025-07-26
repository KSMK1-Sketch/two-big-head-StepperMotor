#ifndef _A_include_H_
#define _A_include_H_

/******************系统头文件*******************/
#include "ti_msp_dl_config.h"
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

/******************用户变量*******************/
#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

#ifndef u64
#define u64 uint64_t
#endif

/******************用户文件*******************/
#include "A_include.h"

#include "..\software\delay\delay.h"
#include "..\software\usart\usart.h"

#include "..\HARDWARE\LED\LED.h"
#include "..\HARDWARE\OLED\oled.h"
#include "..\HARDWARE\1298N\1298n.h"


#endif
