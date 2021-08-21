#include "emuUI.h"
#include "CPU.h"

emu6502::emuUI::emuUI(CPU *_cpu)
{
    cpu = _cpu;
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
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, maxRow, maxCol);
    drawHeader();
    drawControls();
    drawRegister();
    inputListener();
    close();
}

/*
** Input hanndler
** Returns: True (Keep running UI)
**          False (Quit UI)
*/
bool emu6502::emuUI::inputHandler(char ch)
{  
    switch(ch)
    {
    case 'q':
        return false;
    case 'n':
        // Updates Register
        cpu->execute();
        updateRegisters();
    default:
        refresh();
        return true;
    }
}

void emu6502::emuUI::inputListener()
{
    char ch;

    do {
        ch = getch();
    }while (inputHandler(ch));
}

void emu6502::emuUI::drawHeader()
{
    attrset(A_STANDOUT);
    mvprintw(0, (maxCol / 2), "6502 Emulator");
    attroff(A_STANDOUT);
    mvprintw(1, (maxCol / 2), "By 3Gigs");
    refresh();
}

void emu6502::emuUI::drawRegister()
{
    winRegister = newwin(11, 12, 2, maxCol - 12);
    box(winRegister, '|', '=');
    // Draw the "REGISTER" header underlined
    wattrset(winRegister, A_UNDERLINE);
    mvwprintw(winRegister, 1, 2, "REGISTER");
    wattroff(winRegister, A_UNDERLINE);
    // Draw the registers
    mvwprintw(winRegister, 2, 2, "X:");
    mvwprintw(winRegister, 3, 2, "Y:");
    mvwprintw(winRegister, 4, 2, "A:");
    mvwprintw(winRegister, 5, 2, "S:");
    mvwprintw(winRegister, 6, 2, "P:");
    // Draw status header
    wattrset(winRegister, A_UNDERLINE);
    mvwprintw(winRegister, 7, 2, "STATUS");
    wattroff(winRegister, A_UNDERLINE);
    // Draw status flags
    wattrset(winRegister, A_DIM);
    mvwprintw(winRegister, 8, 2, "0123456");
    wattroff(winRegister, A_DIM);
    mvwprintw(winRegister, 9, 2, "CZIDBON");
    // Draw status 

    wrefresh(winRegister);
}

void emu6502::emuUI::updateRegisters()
{
    // Draw the register numbers
    mvwprintw(winRegister, 2, 4, "%X", cpu->getx());
    mvwprintw(winRegister, 3, 4, "%X", cpu->gety());
    mvwprintw(winRegister, 4, 4, "%X", cpu->getA());
    mvwprintw(winRegister, 5, 4, "%X", cpu->getS());
    mvwprintw(winRegister, 6, 4, "%X", cpu->getP());
    wrefresh(winRegister);
}

void emu6502::emuUI::drawControls()
{
    winControl = newwin(maxRow - 4, maxCol * 0.80, 2, 3);
    box(winControl, '|', '=');
    mvwprintw(winControl, 1, 1, "Object Code:");
    wrefresh(winControl);
}

void emu6502::emuUI::close()
{
    werase(winControl);
    werase(winRegister);
    endwin();
}