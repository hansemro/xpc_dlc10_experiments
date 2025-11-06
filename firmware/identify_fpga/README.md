Identify FPGA via JTAG
======================

This firmware demonstrates JTAG access to the FPGA from the FX2 by loading the
IDCODE instruction and shifting out from the IDCODE register.

## Prerequisites

- sdcc for compiling firmware
- [fx2tool](https://github.com/whitequark/libfx2/tree/main/software) (from libfx2)
    - libusb-1.0
    - Python 3
    - Python [libusb1](https://github.com/vpelletier/python-libusb1) wrapper

For Fedora, an additional step is needed after installing sdcc to link
`sdcc-`-prefixed executables to ones without:

```
sudo update-alternatives --install /usr/bin/sdcc sdcc /usr/bin/sdcc-sdcc
sudo update-alternatives --install /usr/bin/sdas8051 sdas8051 /usr/bin/sdcc-sdas8051
sudo update-alternatives --install /usr/bin/sdar sdar /usr/bin/sdcc-sdar
```

## Building the Firmware

Build libfx2 components:

```
git submodule update --init --recursive
make -C ../libfx2/firmware
```

and then build the firmware:

```
make
```

## Loading the Firmware

```
make VID=<VID> PID=<PID> load
```
