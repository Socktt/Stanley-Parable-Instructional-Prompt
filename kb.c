#include <stdint.h>

#include "vga.h"
#include "system.h"
#include "kb.h"

void * callbackArray[256];
uint8_t callbackArrayIndex = 0;

/*
Keyboard handler, attached to interrupt 1
*/
void keyboard_handler(struct regs *r)
{
	unsigned char scancode;									// Input Scancode

	scancode = inb(0x60);									// Read from keyboard to get pressed key

	if (!(scancode & 0x80))									// Check if key pressed is a down key or if it is a key being released
	{
        //putCh(kbdus[scancode]);
        for (int i = 0; i < 256; i++)
        {
            if (callbackArray[i] == 0)
                break;
            void (*callbackFunction) (char input);
            callbackFunction = callbackArray[i];
            callbackFunction(scancode);
        }
    }
}

/*
Installs the keyboard handler, attaches to interrupt 1
*/
void keyboard_install()
{
		irq_install_handler(1, keyboard_handler);
}

void * addFunctionToCallbackArray(void * functionPointer)
{
    callbackArray[callbackArrayIndex] = functionPointer;
}

void * removeLastFuntionFromCallbackArray()
{
    callbackArray[callbackArrayIndex] = 0;
    callbackArrayIndex--;
}