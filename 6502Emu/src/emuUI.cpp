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
    getmaxyx(stdscr, row, col);
    drawUI();

    getch();
    close();
}

void emu6502::emuUI::inputHandler(WINDOW *window)
{  

}

void emu6502::emuUI::drawUI()
{
    attrset(A_STANDOUT);
    mvprintw(0, (col / 2), "6502 Emulator");
    attroff(A_STANDOUT);
    mvprintw(1, (col / 2), "By 3Gigs");
}

void emu6502::emuUI::close()
{
    endwin();
}