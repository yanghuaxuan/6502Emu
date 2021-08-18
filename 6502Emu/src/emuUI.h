#include <ncurses.h>

namespace emu6502 
{
    class emuUI 
    {
    public:
        emuUI();
        ~emuUI();
        void initUI(); // Create curses TUI
        void drawUI(); // Draw GUI
        void drawRegister(); // Draw Window used to show register
        void inputHandler(WINDOW *window);
        void close();
    private:
        int maxRow, maxCol;
        WINDOW *registerWin = nullptr;
    };
}