#pragma once

/*----------------------------------------------------------------------------*/
#define CLK_BASE                                                          0x50C0
/*----------------------------------------------------------------------------*/
#define UART1_BASE                                                        0x5230
#define IRQ_NO_UART1_TX                                                       17
#define IRQ_NO_UART1_RX                                                       18
/*----------------------------------------------------------------------------*/
#define TIM2_BASE                                                         0x5300
#define IRQ_NO_TIM2                                                           13
#define IRQ_NO_TIM2_CC                                                        14
/*----------------------------------------------------------------------------*/
#define TIM4_BASE                                                         0x5340
#define IRQ_NO_TIM4                                                           23
/*----------------------------------------------------------------------------*/
#define PORT_A_BASE                                                       0x5000
#define IRQ_NO_PORT_A                                                          3
/*----------------------------------------------------------------------------*/
#define PORT_B_BASE                                                       0x5005
#define IRQ_NO_PORT_B                                                          4
/*----------------------------------------------------------------------------*/
#define PORT_C_BASE                                                       0x500A
#define IRQ_NO_PORT_C                                                          5
/*----------------------------------------------------------------------------*/
#define PORT_D_BASE                                                       0x500F
#define IRQ_NO_PORT_D                                                          6
/*----------------------------------------------------------------------------*/
#define PORT_E_BASE                                                       0x5014
#define IRQ_NO_PORT_E                                                          7
/*----------------------------------------------------------------------------*/
#define PORT_F_BASE                                                       0x5019
/*----------------------------------------------------------------------------*/
#define EEPROM_BASE                                                       0x4000
#define EEPROM_SIZE                                                          128
/* WARNING: this extra EEPROM area is NOT documented by device datasheet
 * STM8S003F3 STM8S003K3, DS7147 Rev 10
 * However, its documented by following document (and is known to work):
 * source: PM0051 Programming manual, page 25/27, Doc ID 14614 Rev 3
 * 5 "Flash program memory and data EEPROM comparison", Table 9 */
#define EEPROM_EXTRA_BASE                                                 0x4280
#define EEPROM_EXTRA_SIZE                                                    512
/*----------------------------------------------------------------------------*/
#define FLASH_BASE                                                        0x505A
#define FLASH_SIZE                                                          8192
/*----------------------------------------------------------------------------*/
