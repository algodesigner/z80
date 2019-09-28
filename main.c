#include "cpu.h"

int main(int argc, char *argv[])
{
    z80 *cpu = z80_new();
    cpu->debug = 1;
    z80_run(cpu);
    Z80_destroy(cpu);
}
