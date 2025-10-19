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
