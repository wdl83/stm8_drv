#pragma once

#include "stm8.h"

#ifndef FLASH_BASE
#error "Please define FLASH base address"
#endif

#ifndef FLASH_SIZE
#error "Please define FLASH size"
#endif

/* Flash control register 1 */
#define FLASH_CR1                                 STM8_REGISTER(FLASH_BASE, 0x0)
#define CR1_HALT 3
#define CR1_AHALT 2
#define CR1_IE 1
#define CR1_FIX 0

/* Flash control register 2 */
#define FLASH_CR2                                 STM8_REGISTER(FLASH_BASE, 0x1)
#define CR2_OPT 7
#define CR2_WPRG 6
#define CR2_ERASE 5
#define CR2_FPRG 4
#define CR2_PRG 0

/* Flash complementary control register 2 */
#define FLASH_NCR2                                STM8_REGISTER(FLASH_BASE, 0x2)
#define NCR2_NOPT 7
#define NCR2_NWPRG 6
#define NCR2_NERASE 5
#define NCR2_NFPRG 4
#define NCR2_NPRG 0

/* Flash protection register */
#define FLASH_FPR                                 STM8_REGISTER(FLASH_BASE, 0x3)
#define FPR_WPB_MASK 0x1F
#define FPR_WPB5 5
#define FPR_WPB4 4
#define FPR_WPB3 3
#define FPR_WPB2 2
#define FPR_WPB1 1
#define FPR_WPB0 0

/* Flash complementary protection register */
#define FLASH_NFPR                                STM8_REGISTER(FLASH_BASE, 0x4)
#define NFPR_NWPB_MASK 0x1F
#define NFPR_NWPB5 5
#define NFPR_NWPB4 4
#define NFPR_NWPB3 3
#define NFPR_NWPB2 2
#define NFPR_NWPB1 1
#define NFPR_NWPB0 0

/* Flash status register */
#define FLASH_IAPSR                                STM8_REGISTER(FLASH_BASE, 0x5)
#define IAPSR_HVOFF 6
#define IAPSR_DUL 3
#define IAPSR_EOP 2
#define IAPSR_PUL 1
#define IAPSR_WR_PG_DIS 0

/* Flash program memory unprotecting key register */
#define FLASH_PUKR                                STM8_REGISTER(FLASH_BASE, 0x8)

/* Data EEPROM unprotection key register */
#define FLASH_DUKR                                STM8_REGISTER(FLASH_BASE, 0xA)
