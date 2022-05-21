/*
Stanley Parable Instructional Prompt
Copyright Sockttsoft 2022
*/

#include "vga.h"
#include "kb.h"
#include "system.h"
#include <stdint.h>

char keyToPress = 0;

char keys[] = {
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'k',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v',
    'w',
    'x',
    'y',
    'z',
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9'
};

/*
Called in kb.c whenever the enter key is pressed. InputArray = char array of the input string
*/
void parseInput(char input)
{
    if (kbdus[input] != keyToPress)
    {
        print("Incorrect key.\n");
    }
    print("\n---\n");
    newInput();
    return;
}

void newInput()
{
    if(getCursorPos() > 1920)
    {
        colourScreen(0x02);
        print(">-Employee #427 Instructional Prompt                                  v. 1.01.7+");
        print("--------------------------------------------------------------------------------");
    }
    keyToPress = keys[getTimerVal() % 36];
    print("> Please PRESS '");
    putCh(keyToPress);
    print("' on your KEYBOARD for ");
    printInt((getTimerVal() % 80) + 10, 10);
    print("ms.\n");
}

/*
Initialize the prompt.
*/
void promptInit()
{
    newInput();
    addFunctionToCallbackArray(parseInput);
}