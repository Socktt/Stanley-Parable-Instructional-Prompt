#ifndef GDT_H
#define GDT_H

#include <stdint.h>

typedef struct
{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) gdtr_s;

typedef struct
{
    uint16_t    limit_low;
    uint16_t    base_low;
    uint8_t     base_mid;
    uint8_t     access;
    uint8_t     flags_limit;
    uint8_t     base_high;
} __attribute__((packed)) segment_desc_s;

void gdt_install();

#endif