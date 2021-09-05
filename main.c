#include <stdio.h>
#include "z80.h"

static void intercept(void *ctx)
{
    z80 *cpu = ctx;
    if (PC == 5) {
        puts("\nReached address: 5, terminating the simulation...");
        cpu->status = 1;
    }
}

int main(int argc, char *argv[])
{
    z80 *cpu = z80_new();
    cpu->debug = 1;
    z80_set_intercept(cpu, cpu, intercept);
    z80_run(cpu);
    z80_destroy(cpu);
}
