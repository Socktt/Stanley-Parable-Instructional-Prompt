#include <stdint.h>
#include "system.h"
#include "tss.h"

tss_entry_t tss_entry;

uint32_t tss_base = (uint32_t)&tss_entry;
uint32_t tss_limit = sizeof tss_entry;

void setup_tss()
{
    memset(&tss_entry, 0, sizeof tss_entry);

    tss_entry.ss0 = 0xf;
    tss_entry.esp0 = 0x7c00;
}

void set_kernel_stack(uint32_t stack)
{
    tss_entry.esp0 = stack;
}