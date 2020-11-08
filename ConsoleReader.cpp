#include "ConsoleReader.h"
#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <termios.h>
struct termios old_settings, new_settings;
WINDOW *window;
/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    window = initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    if(!echo)
        (void) noecho();       /* don't echo input */
    // reconf termios
    tcgetattr( 0, &old_settings );
    new_settings = old_settings;
    new_settings.c_oflag = new_settings.c_oflag | ONLCR;
    tcsetattr( 0, TCSANOW, &new_settings );
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
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
