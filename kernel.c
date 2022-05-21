#include "gdt.h"
#include "idt.h"
#include "vga.h"
#include "system.h"
#include "kb.h"
#include "prompt.h"

extern void kernMain(){
    //gdt_install();
    idt_install();
    irq_install();
    timer_phase(1);
    timer_install();
    keyboard_install();
    __asm__ __volatile__ ("sti"); 
    colourScreen(0x02);
    print(">-Employee #427 Instructional Prompt                                  v. 1.01.7+");
    print("--------------------------------------------------------------------------------");
    promptInit();
    return;
}