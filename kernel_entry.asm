[bits 32]
[extern kernMain]
[extern idtp]

[global idt_load]

call kernMain

jmp $

idt_load:
    lidt [idtp]
    ret