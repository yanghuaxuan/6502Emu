#include "emuUI.h"

emu6502::emuUI::emuUI()
{
    maxRow = 0;
    maxCol = 0;
}

emu6502::emuUI::~emuUI()
{
    
}

void emu6502::emuUI::initUI()
{
    initscr();
    curs_set(0);
    raw();
    noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, maxRow, maxCol);
    drawUI();
    drawRegister();

    getch();
    close();
}

void emu6502::emuUI::inputHandler(WINDOW *window)
{  

}

void emu6502::emuUI::drawUI()
{
    attrset(A_STANDOUT);
    mvprintw(0, (maxCol / 2), "6502 Emulator");
    attroff(A_STANDOUT);
    mvprintw(1, (maxCol / 2), "By 3Gigs");
    refresh();
}

void emu6502::emuUI::drawRegister()
{
    registerWin = newwin(11, 12, 2, maxCol - 12);
    box(registerWin, '|', '=');
    // Draw the "REGISTER" header underlined
    wattrset(registerWin, A_UNDERLINE);
    mvwprintw(registerWin, 1, 2, "REGISTER");
    wattroff(registerWin, A_UNDERLINE);
    // Draw the registers
    mvwprintw(registerWin, 2, 2, "X:");
    mvwprintw(registerWin, 3, 2, "Y:");
    mvwprintw(registerWin, 4, 2, "A:");
    mvwprintw(registerWin, 5, 2, "S:");
    mvwprintw(registerWin, 6, 2, "P:");
    // Draw status header
    wattrset(registerWin, A_UNDERLINE);
    mvwprintw(registerWin, 7, 2, "STATUS");
    wattroff(registerWin, A_UNDERLINE);
    // Draw status flags
    wattrset(registerWin, A_DIM);
    mvwprintw(registerWin, 8, 2, "0123456");
    wattroff(registerWin, A_DIM);
    mvwprintw(registerWin, 9, 2, "CZIDBON");

    wrefresh(registerWin);
}

void emu6502::emuUI::close()
{
    endwin();
}