#include <stdint.h>
#include "vga.h"
#include "system.h"
#include "prompt.h"

uint16_t CursorPos = 0;

uint16_t getCursorPos()
{
    return CursorPos;
}

void setCursorPosRaw(uint16_t pos) 
{
    /*if (pos > 1920)
    {
        colourScreen(0x02);
        print(">-Employee #427 Instructional Prompt                                  v. 1.01.7+");
        print("--------------------------------------------------------------------------------");
        //newInput();
        return;
    }*/
    if (pos >= 0 && pos < 2000)
    {
		outb(0x3d4, 0x0f);
		outb(0x3d5, (uint8_t)(pos & 0xff));
		outb(0x3d4, 0x0e);
		outb(0x3d5, (uint8_t)((pos >> 8) & 0xff));
		CursorPos = pos;
	}
	return;
}

void setCursorPos(int x, int y) 
{
    uint16_t pos;
    pos = y * VGA_WIDTH + x;
    setCursorPosRaw(pos);
}

void print(const char* text)
{
    uint8_t* textPtr = (uint8_t*) text;
    uint16_t i = CursorPos;
    while(*textPtr!=0){
        switch(*textPtr){
            case 10:
                if (CursorPos < 1920)
                {
                    i += VGA_WIDTH - i % VGA_WIDTH;
                }
                break;
            case 13:
                i -= i % VGA_WIDTH;
                break;
            default:
                *(VIDEO_MEM + i * 2) = *textPtr;
                i++;
        }
        textPtr++;
    }
    setCursorPosRaw(i);
    return;
}

void printInt(uint32_t num, uint8_t base)
{
    char StringToPrint[255];
    itoa(num, StringToPrint, base);
    print(StringToPrint);
    return;
}

void putCh(char Letter)
{
    switch(Letter)
    {
        case '\n':
            if (CursorPos < 1920)
            {
                CursorPos += VGA_WIDTH - CursorPos % VGA_WIDTH;
            }
            CursorPos -= CursorPos % VGA_WIDTH;
            break;
        case '\b':
            CursorPos--;
            if (CursorPos % VGA_WIDTH < 2)
            {
                CursorPos++;
            }
            else
            {
                *(VIDEO_MEM + CursorPos * 2) = ' ';
            }
            break;
        default:
            *(VIDEO_MEM + CursorPos * 2) = Letter;
            CursorPos++;
    }
    setCursorPosRaw(CursorPos);
    return;
}

void enableCursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void drawPixel(uint8_t x, uint8_t y, uint8_t colour){
    uint8_t * pos = (y * 320 + x) + (uint8_t *)0xA0000;
    *pos = colour;
    return;
}

void clearScreen(){
    for (int i = 0; i<VGA_HEIGHT;i++)
    {
        for (int j = 0;j<VGA_WIDTH;j++)
        {
            *(VIDEO_MEM + (i * VGA_HEIGHT * 2) + j * 2) = (const char)' ';
            *(VIDEO_MEM + (i * VGA_HEIGHT * 2) + j * 2 - 1) = (const char)0x0f;
        }
    }
    setCursorPos(0, 0);
    return;
}

void colourScreen(uint8_t colour){
    for (int i = 0; i<VGA_HEIGHT;i++)
    {
        for (int j = 0;j<VGA_WIDTH;j++)
        {
            *(VIDEO_MEM + (i * VGA_HEIGHT * 2) + j * 2) = (const char)' ';
            *(VIDEO_MEM + (i * VGA_HEIGHT * 2) + j * 2 - 1) = (const char)colour;
        }
    }
    setCursorPos(0, 0);
    return;
}

void graphicsClearScreen(uint8_t colour){
    uint8_t * graphicsVideoMem = (uint8_t *)0xA0000;
    for (int i = 0;i < 200;i++)
    {
        for (int j = 0;j < 320;j++)
        {
            *graphicsVideoMem = colour;
            graphicsVideoMem++;
        }
    }
}

void drawPalette(uint8_t x, uint8_t y){
    uint8_t * graphicsVideoMem = (uint8_t *)0xA0000 + (y * 320 + x);
    uint8_t colourIndex = 0x0;
    for (uint8_t i = 0;i < 0xf;i++)
    {
        for (uint8_t j = 0;j < 0xf;j++)
        {
            *graphicsVideoMem = colourIndex;
            colourIndex++;
            graphicsVideoMem++;
        }
        graphicsVideoMem += (320 - 0xf);
    }
}