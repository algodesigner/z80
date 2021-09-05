# Z80 CPU Emulator

Z80 CPU Emulator (with built-in debugger) forked and separated out from [RunCPM Project](https://github.com/MockbaTheBorg/RunCPM) (implemented by [MockbaTheBorg](https://github.com/MockbaTheBorg)) so that it can be used in a stand-alone fashion or integrated into computer simulation projects.

The original `cpu.h` header file has been split into the `z80.h` interface definition and `z80.c` implementation.

The processor state has been moved to the z80 class so that multiple CPU instances can be created in the same process to emulate multi-processor systems.
