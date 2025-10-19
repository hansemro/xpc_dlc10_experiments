// Copyright (C) Hansem Ro <hansemro@outlook.com>
// SPDX-License-Identifier: 0BSD

#include <fx2regs.h>

void init(void) {
    // Set Core Frequency to 48MHz
    CPUCS = _CLKSPD1;

    // Select Port Function
    PORTACFG = 0;
    PORTCCFG = 0;
    PORTECFG = 0;
    // Use PB and PD port function
    IFCONFIG = _IFCLKSRC | _3048MHZ;

    // Set external JTAG TCK buffer to tristate by setting CTL2 low
    GPIFCTLCFG = 0;
    GPIFIDLECTL &= ~(_CTL2);
    GPIFABORT = 0xff; // Enter IDLE state

    // Tristate pins to FPGA
    OEA = 0x00;
    OEB = 0x00;
    OED = 0x00;

    // Set Manual Reset (MR) pin of MAX6412 high to stop PROG_B from toggling
    OEC = (1U << 7);
    PC7 = 1;

    // Enable FPGA Power
    OEE = 1U << 6;
    IOE = 1U << 6;

    // Enable IFCLK
    IFCONFIG |= _IFCLKOE;
}

int main(void) {
    init();
    while(1);
}
