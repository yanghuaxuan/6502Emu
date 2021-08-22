#include <ncurses.h>
#include <cstdint>
#include "CPU.h"
#include "RAM.h"

namespace emu6502 
{
    class emuUI 
    {
    public:
        emuUI(CPU *cpu, RAM *ram);
        ~emuUI();
        void initUI(); // Create curses TUI
        void drawHeader(); // Draw GUI
        void drawRegister(); // Draw Window used to show register
        void updateRegisters();
        void drawPCViewer();
        void updatePCViewer();
        bool inputHandler(char ch);
        void inputListener();
        void close();
    private:
        CPU *cpu = nullptr;
        RAM *ram = nullptr;
        int maxRow, maxCol;
        WINDOW *winRegister = nullptr;
        WINDOW *winPCView = nullptr;
    };
}