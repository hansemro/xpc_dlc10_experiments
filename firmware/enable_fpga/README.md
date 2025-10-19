Enable Spartan-3A FPGA Access
=============================

This firmware configures pins for external JTAG access, and enables power and
~48MHz clock to the FPGA.

> [!TIP]
> I recommend programming a different VID:PID to prevent Vivado from
> overwriting the firmware.
>
> ```
> fx2tool -d 03fd:0013 -S <Vend_Ax.hex> update -V dead -P cafe
> ```

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
make VID=dead PID=cafe load
```
