// Copyright (C) 2025 Hansem Ro <hansemro@outlook.com>
// SPDX-License-Identifier: 0BSD

#ifndef JTAG_TAP_H
#define JTAG_TAP_H

#include <stdint.h>
#include <stdbool.h>
#include "board_config.h"

// Required JTAG pin assignment
#ifndef TCK_PIN
    #error "GPIO pin 'TCK_PIN' was not defined"
#endif // TCK_PIN
#ifndef TMS_PIN
    #error "GPIO pin 'TMS_PIN' was not defined"
#endif // TMS_PIN
#ifndef TDI_PIN
    #error "GPIO pin 'TDI_PIN' was not defined"
#endif // TDI_PIN
#ifndef TDO_PIN
    #error "GPIO pin 'TDO_PIN' was not defined"
#endif // TDO_PIN

#ifndef JTAG_TCK_PERIOD_US
    #define JTAG_TCK_PERIOD_US  200U
#endif

// Use n-bits of tms (up-to 32) to traverse the JTAG TAP state machine.
void tap_send_tms(uint32_t tms, int n);

// Assuming the TAP is in SHIFT-DR/IR state, shift n-bits from tdi/tdo, and
// optionally enter EXIT-1-DR/IR state on last cycle if last_tms == true.
//
// Returns n-bits (up-to 32) shifted from tdo starting from the least
// significant bit.
uint32_t tap_shift_bits(uint32_t tdi, int n, bool last_tms);

#endif // JTAG_TAP_H
