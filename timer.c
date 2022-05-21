#include "system.h"
#include "port_io.h"

int timer_ticks = 0;

void timer_phase(int hz)
{
    int divisor = 1193180 / hz;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}

void timer_handler(struct regs *r)
{
    timer_ticks++;

    /*if (timer_ticks % 18 == 0)
    {
        printInt(timer_ticks, 10);
    }*/
}

void sleep(int ms)
{
    if (ms == 0)
    {
        return;
    }
    int initial_time = timer_ticks;
    while (timer_ticks - initial_time < ms / 10)
    {}
}

void timer_install()
{
    irq_install_handler(0, timer_handler);
}

int getTimerVal()
{
    return timer_ticks;
}