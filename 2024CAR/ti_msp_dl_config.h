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



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA1
#define PWM_0_INST_IRQHandler                                   TIMA1_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA1_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                              4000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOA
#define GPIO_PWM_0_C0_PIN                                         DL_GPIO_PIN_17
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM39)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM39_PF_TIMA1_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOA
#define GPIO_PWM_0_C1_PIN                                         DL_GPIO_PIN_16
#define GPIO_PWM_0_C1_IOMUX                                      (IOMUX_PINCM38)
#define GPIO_PWM_0_C1_IOMUX_FUNC                     IOMUX_PINCM38_PF_TIMA1_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX

/* Defines for PWM_1 */
#define PWM_1_INST                                                         TIMG6
#define PWM_1_INST_IRQHandler                                   TIMG6_IRQHandler
#define PWM_1_INST_INT_IRQN                                     (TIMG6_INT_IRQn)
#define PWM_1_INST_CLK_FREQ                                              4000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_1_C0_PORT                                                 GPIOB
#define GPIO_PWM_1_C0_PIN                                         DL_GPIO_PIN_26
#define GPIO_PWM_1_C0_IOMUX                                      (IOMUX_PINCM57)
#define GPIO_PWM_1_C0_IOMUX_FUNC                     IOMUX_PINCM57_PF_TIMG6_CCP0
#define GPIO_PWM_1_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_1_C1_PORT                                                 GPIOB
#define GPIO_PWM_1_C1_PIN                                         DL_GPIO_PIN_27
#define GPIO_PWM_1_C1_IOMUX                                      (IOMUX_PINCM58)
#define GPIO_PWM_1_C1_IOMUX_FUNC                     IOMUX_PINCM58_PF_TIMG6_CCP1
#define GPIO_PWM_1_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                         (19999U)
/* Defines for TIMER_GD */
#define TIMER_GD_INST                                                    (TIMA0)
#define TIMER_GD_INST_IRQHandler                                TIMA0_IRQHandler
#define TIMER_GD_INST_INT_IRQN                                  (TIMA0_INT_IRQn)
#define TIMER_GD_INST_LOAD_VALUE                                        (39999U)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMG7)
#define TIMER_1_INST_IRQHandler                                 TIMG7_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMG7_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                         (39999U)




/* Defines for I2C_1 */
#define I2C_1_INST                                                          I2C1
#define I2C_1_INST_IRQHandler                                    I2C1_IRQHandler
#define I2C_1_INST_INT_IRQN                                        I2C1_INT_IRQn
#define I2C_1_BUS_SPEED_HZ                                                400000
#define GPIO_I2C_1_SDA_PORT                                                GPIOB
#define GPIO_I2C_1_SDA_PIN                                         DL_GPIO_PIN_3
#define GPIO_I2C_1_IOMUX_SDA                                     (IOMUX_PINCM16)
#define GPIO_I2C_1_IOMUX_SDA_FUNC                      IOMUX_PINCM16_PF_I2C1_SDA
#define GPIO_I2C_1_SCL_PORT                                                GPIOB
#define GPIO_I2C_1_SCL_PIN                                         DL_GPIO_PIN_2
#define GPIO_I2C_1_IOMUX_SCL                                     (IOMUX_PINCM15)
#define GPIO_I2C_1_IOMUX_SCL_FUNC                      IOMUX_PINCM15_PF_I2C1_SCL


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
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_0_FBRD_4_MHZ_115200_BAUD                                       (11)





/* Port definition for Pin Group KEY */
#define KEY_PORT                                                         (GPIOB)

/* Defines for KEY1: GPIOB.21 with pinCMx 49 on package pin 20 */
#define KEY_KEY1_PIN                                            (DL_GPIO_PIN_21)
#define KEY_KEY1_IOMUX                                           (IOMUX_PINCM49)
/* Defines for LEDG: GPIOA.2 with pinCMx 7 on package pin 42 */
#define LED_LEDG_PORT                                                    (GPIOA)
#define LED_LEDG_PIN                                             (DL_GPIO_PIN_2)
#define LED_LEDG_IOMUX                                            (IOMUX_PINCM7)
/* Defines for LEDB: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_LEDB_PORT                                                    (GPIOB)
#define LED_LEDB_PIN                                            (DL_GPIO_PIN_22)
#define LED_LEDB_IOMUX                                           (IOMUX_PINCM50)
/* Defines for AIN1: GPIOA.14 with pinCMx 36 on package pin 7 */
#define TB6612_AIN1_PORT                                                 (GPIOA)
#define TB6612_AIN1_PIN                                         (DL_GPIO_PIN_14)
#define TB6612_AIN1_IOMUX                                        (IOMUX_PINCM36)
/* Defines for AIN2: GPIOA.15 with pinCMx 37 on package pin 8 */
#define TB6612_AIN2_PORT                                                 (GPIOA)
#define TB6612_AIN2_PIN                                         (DL_GPIO_PIN_15)
#define TB6612_AIN2_IOMUX                                        (IOMUX_PINCM37)
/* Defines for BIN1: GPIOA.12 with pinCMx 34 on package pin 5 */
#define TB6612_BIN1_PORT                                                 (GPIOA)
#define TB6612_BIN1_PIN                                         (DL_GPIO_PIN_12)
#define TB6612_BIN1_IOMUX                                        (IOMUX_PINCM34)
/* Defines for BIN2: GPIOA.13 with pinCMx 35 on package pin 6 */
#define TB6612_BIN2_PORT                                                 (GPIOA)
#define TB6612_BIN2_PIN                                         (DL_GPIO_PIN_13)
#define TB6612_BIN2_IOMUX                                        (IOMUX_PINCM35)
/* Defines for CIN1: GPIOB.17 with pinCMx 43 on package pin 14 */
#define TB6612_CIN1_PORT                                                 (GPIOB)
#define TB6612_CIN1_PIN                                         (DL_GPIO_PIN_17)
#define TB6612_CIN1_IOMUX                                        (IOMUX_PINCM43)
/* Defines for CIN2: GPIOB.18 with pinCMx 44 on package pin 15 */
#define TB6612_CIN2_PORT                                                 (GPIOB)
#define TB6612_CIN2_PIN                                         (DL_GPIO_PIN_18)
#define TB6612_CIN2_IOMUX                                        (IOMUX_PINCM44)
/* Defines for DIN1: GPIOA.8 with pinCMx 19 on package pin 54 */
#define TB6612_DIN1_PORT                                                 (GPIOA)
#define TB6612_DIN1_PIN                                          (DL_GPIO_PIN_8)
#define TB6612_DIN1_IOMUX                                        (IOMUX_PINCM19)
/* Defines for DIN2: GPIOA.9 with pinCMx 20 on package pin 55 */
#define TB6612_DIN2_PORT                                                 (GPIOA)
#define TB6612_DIN2_PIN                                          (DL_GPIO_PIN_9)
#define TB6612_DIN2_IOMUX                                        (IOMUX_PINCM20)
/* Defines for E1A: GPIOA.27 with pinCMx 60 on package pin 31 */
#define ENCODER_E1A_PORT                                                 (GPIOA)
// pins affected by this interrupt request:["E1A","E1B","E2A","E2B"]
#define ENCODER_GPIOA_INT_IRQN                                  (GPIOA_INT_IRQn)
#define ENCODER_GPIOA_INT_IIDX                  (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define ENCODER_E1A_IIDX                                    (DL_GPIO_IIDX_DIO27)
#define ENCODER_E1A_PIN                                         (DL_GPIO_PIN_27)
#define ENCODER_E1A_IOMUX                                        (IOMUX_PINCM60)
/* Defines for E1B: GPIOA.26 with pinCMx 59 on package pin 30 */
#define ENCODER_E1B_PORT                                                 (GPIOA)
#define ENCODER_E1B_IIDX                                    (DL_GPIO_IIDX_DIO26)
#define ENCODER_E1B_PIN                                         (DL_GPIO_PIN_26)
#define ENCODER_E1B_IOMUX                                        (IOMUX_PINCM59)
/* Defines for E2A: GPIOA.31 with pinCMx 6 on package pin 39 */
#define ENCODER_E2A_PORT                                                 (GPIOA)
#define ENCODER_E2A_IIDX                                    (DL_GPIO_IIDX_DIO31)
#define ENCODER_E2A_PIN                                         (DL_GPIO_PIN_31)
#define ENCODER_E2A_IOMUX                                         (IOMUX_PINCM6)
/* Defines for E2B: GPIOA.28 with pinCMx 3 on package pin 35 */
#define ENCODER_E2B_PORT                                                 (GPIOA)
#define ENCODER_E2B_IIDX                                    (DL_GPIO_IIDX_DIO28)
#define ENCODER_E2B_PIN                                         (DL_GPIO_PIN_28)
#define ENCODER_E2B_IOMUX                                         (IOMUX_PINCM3)
/* Defines for E3A: GPIOB.10 with pinCMx 27 on package pin 62 */
#define ENCODER_E3A_PORT                                                 (GPIOB)
// pins affected by this interrupt request:["E3A","E3B","E4A","E4B"]
#define ENCODER_GPIOB_INT_IRQN                                  (GPIOB_INT_IRQn)
#define ENCODER_GPIOB_INT_IIDX                  (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define ENCODER_E3A_IIDX                                    (DL_GPIO_IIDX_DIO10)
#define ENCODER_E3A_PIN                                         (DL_GPIO_PIN_10)
#define ENCODER_E3A_IOMUX                                        (IOMUX_PINCM27)
/* Defines for E3B: GPIOB.11 with pinCMx 28 on package pin 63 */
#define ENCODER_E3B_PORT                                                 (GPIOB)
#define ENCODER_E3B_IIDX                                    (DL_GPIO_IIDX_DIO11)
#define ENCODER_E3B_PIN                                         (DL_GPIO_PIN_11)
#define ENCODER_E3B_IOMUX                                        (IOMUX_PINCM28)
/* Defines for E4A: GPIOB.12 with pinCMx 29 on package pin 64 */
#define ENCODER_E4A_PORT                                                 (GPIOB)
#define ENCODER_E4A_IIDX                                    (DL_GPIO_IIDX_DIO12)
#define ENCODER_E4A_PIN                                         (DL_GPIO_PIN_12)
#define ENCODER_E4A_IOMUX                                        (IOMUX_PINCM29)
/* Defines for E4B: GPIOB.13 with pinCMx 30 on package pin 1 */
#define ENCODER_E4B_PORT                                                 (GPIOB)
#define ENCODER_E4B_IIDX                                    (DL_GPIO_IIDX_DIO13)
#define ENCODER_E4B_PIN                                         (DL_GPIO_PIN_13)
#define ENCODER_E4B_IOMUX                                        (IOMUX_PINCM30)
/* Port definition for Pin Group IIC_JY61P */
#define IIC_JY61P_PORT                                                   (GPIOA)

/* Defines for SDA_JY61P: GPIOA.1 with pinCMx 2 on package pin 34 */
#define IIC_JY61P_SDA_JY61P_PIN                                  (DL_GPIO_PIN_1)
#define IIC_JY61P_SDA_JY61P_IOMUX                                 (IOMUX_PINCM2)
/* Defines for SCL_JY61P: GPIOA.0 with pinCMx 1 on package pin 33 */
#define IIC_JY61P_SCL_JY61P_PIN                                  (DL_GPIO_PIN_0)
#define IIC_JY61P_SCL_JY61P_IOMUX                                 (IOMUX_PINCM1)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_PWM_1_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_GD_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_I2C_1_init(void);
void SYSCFG_DL_UART_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
