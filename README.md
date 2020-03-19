# DE10-Nano-GHRD

This project is a fleshed-out implementation of the GHDR (Golden Hardware Design Reference) demo for the Terasic DE10-Nano board. The board itself is a breakout for an SoC consisting of an Intel Cyclone V FPGA and an ARM Cortex-A9 processor, which is configured to run Angstrom Linux. 
The HDL files to configured the FPGA have been provided by Terasic and can be automatically generated using the Platform Designer tool (formerly known as Qsys) on Quartus Prime. 
The firmware files (written in C) were not given and must be created by the user. Using help from design references, I've written a basic script that flashes the series-LEDs in a consecutive one-hot pattern. The LEDs on the DE10-Nano "belong" to the Cyclone V, so the firmware must access the LED PIO through the HPS-FPGA AXI bus. Once the virtual address space is uncovered, we are free to write to the LEDs. 
Use the code here with the given GHDR demo and other DE10-Nano guides to set up your own DE10-Nano dual FPGA and Embedded Linux system with ease. 
