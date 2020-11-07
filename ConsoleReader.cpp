#include "ConsoleReader.h"
#include <stdio.h>
#include <unistd.h>
#include <curses.h>

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    (void) initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    if(!echo)
        (void) noecho();       /* don't echo input */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
    endwin();
}

ConsoleReader::ConsoleReader()
{
    initTermios(0);
}

ConsoleReader::~ConsoleReader()
{
    resetTermios();
}

void ConsoleReader::run()
{
    forever {
        char key = getch();        
        emit KeyPressed(key);
    }
}
