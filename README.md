# Runtime Core Architecture Switching On The RP2350
Project that showcases how to switch the same core from arm to risc-v and back during runtime on the RP2350 microcontroller.

Example code blinks the built in LED slowly on the ARM side switches architectures, and blinks it quickly on the RISC-V side and again changes architecture, looping infinitely.

Idea is to write to the ARCHSEL register, to switch the core architectures by a hardware reset. In this case you can either use the watchdog timeout for the reset or setting SYSRESETREQ in the AIRCR register on the arm side to issue this restart request. (RP2350 datasheet section 3.9 - Arm/RISC-V architecture switching)

The other important part is to set up the two partitions where the code for each architecture exists. (check partitions.json). By writing the riscv binary to 0x10100000, we can make the bootloader try to boot it when we switch from arm to risc. (RP2350 datasheet section 5.1.19 - Address translation)

By setting ignored_during_arm_boot or ignored_during_riscv_boot on either of the partitions we make the bootloader ignore either partition when it reboots in a particular architecture, making the bootloader select the correct binary to execute.

Does this have any use? I don't know. Was it fun to figure out? Obviously!
## How to run
1. Install the Pi Pico SDK visual studio code plugin.
2. Compile both of the binaries in armside and riscside
3. Using ``make_part.sh``, create and upload the partition .uf2 to the RP2350
4. using ``build_upload.sh``, upload the two compiled .uf2 binaries to the RP2350 partitions
