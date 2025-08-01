/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_SG90 */
#define PWM_SG90_INST                                                      TIMG0
#define PWM_SG90_INST_IRQHandler                                TIMG0_IRQHandler
#define PWM_SG90_INST_INT_IRQN                                  (TIMG0_INT_IRQn)
#define PWM_SG90_INST_CLK_FREQ                                             20000
/* GPIO defines for channel 0 */
#define GPIO_PWM_SG90_C0_PORT                                              GPIOA
#define GPIO_PWM_SG90_C0_PIN                                      DL_GPIO_PIN_12
#define GPIO_PWM_SG90_C0_IOMUX                                   (IOMUX_PINCM34)
#define GPIO_PWM_SG90_C0_IOMUX_FUNC                  IOMUX_PINCM34_PF_TIMG0_CCP0
#define GPIO_PWM_SG90_C0_IDX                                 DL_TIMER_CC_0_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA0)
#define TIMER_0_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                          (6399U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_32_MHZ_9600_BAUD                                       (208)
#define UART_0_FBRD_32_MHZ_9600_BAUD                                        (21)





/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for LEDR: GPIOB.18 with pinCMx 44 on package pin 15 */
#define LED_LEDR_PIN                                            (DL_GPIO_PIN_18)
#define LED_LEDR_IOMUX                                           (IOMUX_PINCM44)
/* Defines for LEDG: GPIOB.19 with pinCMx 45 on package pin 16 */
#define LED_LEDG_PIN                                            (DL_GPIO_PIN_19)
#define LED_LEDG_IOMUX                                           (IOMUX_PINCM45)
/* Defines for KEY0: GPIOA.18 with pinCMx 40 on package pin 11 */
#define KEY_KEY0_PORT                                                    (GPIOA)
#define KEY_KEY0_PIN                                            (DL_GPIO_PIN_18)
#define KEY_KEY0_IOMUX                                           (IOMUX_PINCM40)
/* Defines for KEY1: GPIOB.21 with pinCMx 49 on package pin 20 */
#define KEY_KEY1_PORT                                                    (GPIOB)
#define KEY_KEY1_PIN                                            (DL_GPIO_PIN_21)
#define KEY_KEY1_IOMUX                                           (IOMUX_PINCM49)
/* Defines for SCL: GPIOB.14 with pinCMx 31 on package pin 2 */
#define IIC_SCL_PORT                                                     (GPIOB)
#define IIC_SCL_PIN                                             (DL_GPIO_PIN_14)
#define IIC_SCL_IOMUX                                            (IOMUX_PINCM31)
/* Defines for SDA: GPIOA.30 with pinCMx 5 on package pin 37 */
#define IIC_SDA_PORT                                                     (GPIOA)
#define IIC_SDA_PIN                                             (DL_GPIO_PIN_30)
#define IIC_SDA_IOMUX                                             (IOMUX_PINCM5)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_SG90_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_UART_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
