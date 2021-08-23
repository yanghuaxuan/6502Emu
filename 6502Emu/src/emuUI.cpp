#include "emuUI.h"

emu6502::emuUI::emuUI(CPU *_cpu, RAM *_ram)
{
    cpu = _cpu;
    ram = _ram;
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
    drawPCViewer();
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
        updatePCViewer();
        return true;
    case 'r':
        cpu->reset();
        updateRegisters();
        updatePCViewer();
        return true;
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
    winRegister = newwin(11, 12, 3, maxCol - 12);
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
    winControls =  newwin(1, maxCol, 2, 3);
    mvwprintw(winControls, 0, 1, "(n)Execute  " 
                                 "(r)Reset CPU  "
                                 "(q)Quit "  );
    wrefresh(winControls);
}

void emu6502::emuUI::drawPCViewer()
{
    winPCView = newwin(maxRow - 4, maxCol * 0.80, 3, 3);
    box(winPCView, '|', '=');
    mvwprintw(winPCView, 1, 1, "PC Viewer");
    wrefresh(winPCView);
}

void emu6502::emuUI::updatePCViewer()
{
    int maxPCVX, maxPCVY;
    getmaxyx(winPCView, maxPCVY, maxPCVX);
    int pcOffset = maxPCVY / 2;
    for(int i = 2; i < maxPCVY - 1; i++)
    {
        if((cpu->getP() + i - 6) == cpu->getP())
        {
            wattrset(winPCView, A_STANDOUT);
        }
        mvwprintw(winPCView, i, 1, "%X, %X", (cpu->getP() + i - 6), (ram->mem_read(cpu->getP() + i - 6)));
        wattroff(winPCView, A_STANDOUT);
    }
    wrefresh(winPCView);
    refresh();
}

void emu6502::emuUI::close()
{
    werase(winPCView);
    werase(winRegister);
    endwin();
}