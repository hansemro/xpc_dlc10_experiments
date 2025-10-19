Blinky Demo for DLC10
=====================

This demonstrates using IFCLK from the FX2 as a clock source to increment a
counter and drive LEDs.

## Prerequisites

- ISE 14.7 for building the bitstream
- DLC10 with FPGA JTAG pins probed and with `enable_fpga` firmware loaded
    - See [enable_fpga](../../firmware/enable_fpga/README.md) for steps on
      connecting JTAG pins, and building and loading the firmware

## Building the Bitstream

1. Source the ISE 14.7 environment script:

```
source /path/to/Xilinx/14.7/ISE_DS/settings64.sh
```

2. Build the bitstream:

```
make
```

If successful, `blinky.bit` should be generated.
