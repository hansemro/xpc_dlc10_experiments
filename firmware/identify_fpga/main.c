// Copyright (C) Hansem Ro <hansemro@outlook.com>
// SPDX-License-Identifier: 0BSD

#include <fx2regs.h>
#include <fx2delay.h>
#include <stdint.h>
#include "board_config.h"
#include "jtag_tap.h"

// TODO: enable/use dedicated serial port 0
// Debug serial on PA0 at 38400 baud
#include <fx2debug.h>
#include <stdio.h>
#define SERIAL_TX_BIT       (1U << 0)
#define SERIAL_TX_PIN       PA0
DEFINE_DEBUG_PUTCHAR_FN(PA0, 38400)

void init(void) {
    // Set Core Frequency to 48MHz
    CPUCS = _CLKSPD1;

    // Select Port Function
    PORTACFG = 0;
    PORTCCFG = 0;
    PORTECFG = 0;
    // Use PB and PD port function
    IFCONFIG = _IFCLKSRC | _3048MHZ;

    // Enable external JTAG TCK buffer by setting CTL2 high
    GPIFCTLCFG = 0;
    GPIFIDLECTL |= TCK_OE_BIT;
    GPIFABORT = 0xff; // Enter IDLE state

    OEA = SERIAL_TX_BIT;
    OEB = TCK_BIT | TMS_BIT | TDI_BIT;
    OEC = FPGA_MANUAL_RESET_BIT;
    OED = 0x00;
    OEE = FPGA_POWER_ENABLE_BIT;

    // Disable FPGA Reset
    FPGA_MANUAL_RESET_PIN = 1;

    // Enable FPGA Power
    IOE = FPGA_POWER_ENABLE_BIT;
}

uint32_t check_identity(void) {
    uint32_t idcode = 0;
    // Enter Test-Logic-Reset
    tap_send_tms(0xffff, 32);
    // Enter SHIFT-IR
    tap_send_tms(0b00110, 5);
    // Shift in IDCODE instruction and enter EXIT-1-IR on last cycle
    tap_shift_bits(IDCODE_INSTRUCTION, INSTRUCTION_LENGTH, true);
    // Enter Shift-DR
    tap_send_tms(0b0011, 4);
    // Shift out IDCODE register and enter EXIT-1-DR on last cycle
    idcode = tap_shift_bits(0, IDCODE_LENGTH, true);
    // Enter Test-Logic-Reset
    tap_send_tms(0xffff, 32);
    return idcode;
}

int main(void) {
    uint32_t idcode;
    init();
    printf("Checking for FPGA identity %#lx:\n", SPARTAN3A_IDCODE);
    while(1) {
        idcode = check_identity();
        printf("Received %s IDCODE: %#lx\n", 
                idcode == SPARTAN3A_IDCODE ? "valid" : "invalid",
                idcode);
        delay_ms(1000);
    }
}
