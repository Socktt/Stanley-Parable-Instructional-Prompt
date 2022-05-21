#include "gdt.h"

#define SEG_NUM 6

segment_desc_s gdt[SEG_NUM];
gdtr_s gdtr;

void gdt_set_gate(segment_desc_s seg, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    seg.limit_low   =   (uint16_t)(limit & 0xffff);
    seg.base_low    =   (uint16_t)(base & 0xffff);
    seg.base_mid    =   (uint8_t)((base & 0xff0000) >> 16);
    seg.access      =   access;
    seg.flags_limit =   (uint8_t)(((limit & 0xf0000) >> 16) | (flags << 4));
    seg.base_high   =   (uint8_t)((base & 0xff000000) >> 24);
}

void gdt_install()
{
    //memset(gdt, 0, sizeof(segment_desc_s));
    gdt_set_gate(gdt[0], 0, 0, 0, 0);
    gdt_set_gate(gdt[1], 0, 0xffffffff, 0b10011010, 0b0100); // code ring 0
    gdt_set_gate(gdt[2], 0, 0xffffffff, 0b10010010, 0b0100); // data ring 0
    gdt_set_gate(gdt[3], 0, 0xffffffff, 0b11111010, 0b0100); // code ring 3
    gdt_set_gate(gdt[4], 0, 0xffffffff, 0b11110010, 0b0100); // data ring 3

    gdtr.size = sizeof(gdt) - 1;
    gdtr.offset = gdt;

    asm volatile("lgdt %0" : "=m" (gdtr));
}