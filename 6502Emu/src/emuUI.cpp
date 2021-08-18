#include "emuUI.h"

emu6502::emuUI::emuUI()
{
    
}

emu6502::emuUI::~emuUI()
{
    
}

void emu6502::emuUI::initUI()
{
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    printw("Hello world!\n");
    getch();
    close();
}

void emu6502::emuUI::close()
{
    endwin();
}