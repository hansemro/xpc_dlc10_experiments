// Copyright (C) Hansem Ro <hansemro@outlook.com>
// SPDX-License-Identifier: 0BSD

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

// JTAG TCK period in microseconds
#define JTAG_TCK_PERIOD_US      1000U

// CTL2:TCK Output Enable (active-high)
#define TCK_OE_BIT              _CTL2
// PB7:TCK
#define TCK_BIT                 (1U << 7)
#define TCK_PIN                 PB7
// PB4:TMS
#define TMS_BIT                 (1U << 4)
#define TMS_PIN                 PB4
// PB0:TDI
#define TDI_BIT                 (1U << 0)
#define TDI_PIN                 PB0
// PC6:TDO
#define TDO_BIT                 (1U << 6)
#define TDO_PIN                 PC6
// PC7:FPGA Manual Reset (active-low)
#define FPGA_MANUAL_RESET_BIT   (1U << 7)
#define FPGA_MANUAL_RESET_PIN   PC7
// PE6:FPGA Power Enable (active-high)
#define FPGA_POWER_ENABLE_BIT   (1U << 6)

// Spartan 3A TAP
#define SPARTAN3A_IDCODE        0x02218093UL
#define IDCODE_INSTRUCTION      0b001001U
#define BYPASS_INSTRUCTION      0b111111U
#define INSTRUCTION_LENGTH      6
#define IDCODE_LENGTH           32

#endif // BOARD_CONFIG_H
