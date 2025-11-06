// Copyright (C) 2025 Hansem Ro <hansemro@outlook.com>
// SPDX-License-Identifier: 0BSD

#include <fx2regs.h>
#include <fx2delay.h>
#include <stdint.h>
#include <stdbool.h>
#include "jtag_tap.h"

void tap_send_tms(uint32_t tms, int n) {
    for (int i = 0; i < n; i++) {
        TCK_PIN = 0;
        TMS_PIN = tms & 1;
        tms >>= 1;
        delay_us(JTAG_TCK_PERIOD_US/2);
        TCK_PIN = 1;
        delay_us(JTAG_TCK_PERIOD_US/2);
    }
}

uint32_t tap_shift_bits(uint32_t tdi, int n, bool last_tms) {
    uint32_t tdo = 0;
    for (int i = 0; i < n; i++) {
        TCK_PIN = 0;
        TDI_PIN = tdi & 1;
        TMS_PIN = last_tms && (i == n - 1);
        tdi >>= 1;
        delay_us(JTAG_TCK_PERIOD_US/2);
        TCK_PIN = 1;
        delay_us(JTAG_TCK_PERIOD_US/2);
        tdo |= ((uint32_t)TDO_PIN) << i;
    }
    return tdo;
}
