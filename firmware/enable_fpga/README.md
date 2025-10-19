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

## Connecting to Spartan-3A JTAG Pins

### Prerequisites

- 1x PCBite base plate
- 4x PCBite holders
- 4x PCBite SP10/SQ10 probes
- 1x 2x7 [JTAG Flying Wire Adapter Cable](https://www.amd.com/en/products/adaptive-socs-and-fpgas/board-accessories/jtag-flyingwire.html)
- [Glasgow Digital Interface Explorer](https://glasgow-embedded.org/)

### Steps

1. Disassemble the DLC10 cover and shield held by a few screws.

2. Affix the DLC10 PCB to the PCBite plate by at least 3 PCBite holders.

3. Attach the JTAG Flying Wire adapter board without the flying wires attached.

4. Connect Glasgow's GND pin to the GND pin of the Flying Wire adapter board.

5. Connect Glasgow's A0, A1, A2, and A3 pins to each PCBite probe, and then
   probe the following locations connected to FPGA JTAG pins:

    - FPGA TDI: PB0 pin of the FX2
    - FPGA TMS: PB4 pin of the FX2
    - FPGA TCK: Pin 4 of the NC7SZ126 between the FX2 and the FPGA
    - FPGA TDO: PC6 pin of the FX2

6. Connect the DLC10 to a computer via USB and load the `enable_fpga` firmware:

```
make VID=dead PID=cafe load
```

Now you are setup to use Glasgow JTAG applets!

### [Glasgow] Detecting JTAG Pinout

Run `jtag-pinout` to identify JTAG pins:

```
$ glasgow run jtag-pinout -V A=3.3 --pins A0,A1,A2,A3
I: g.hardware.device: generating bitstream ID aba57cbb2166af6c57db29d64da37091
I: g.hardware.assembly: port A voltage set to 3.3 V
I: g.cli: running handler for applet 'jtag-pinout'
I: g.applet.interface.jtag_pinout: detecting pull resistors
I: g.applet.interface.jtag_pinout: pull-H: A0, A1, A2, A3
I: g.applet.interface.jtag_pinout: detecting TCK, TMS, and TDO
I: g.applet.interface.jtag_pinout: shifted 10 out of IR with TCK=A2 TMS=A1 TDO=A3
I: g.applet.interface.jtag_pinout: detecting TDI
I: g.applet.interface.jtag_pinout: shifted 6-bit IR with TCK=A2 TMS=A1 TDI=A0 TDO=A3
I: g.applet.interface.jtag_pinout: JTAG interface without reset detected
I: g.applet.interface.jtag_pinout: use `jtag-probe -V A=3.30 --tck A2 --tms A1 --tdi A0 --tdo A3` as arguments
```
