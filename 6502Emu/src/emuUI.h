#include <ncurses.h>

namespace emu6502 
{
    class emuUI 
    {
    public:
        emuUI();
        ~emuUI();
        void initUI();
        void drawUI();
        void inputHandler(WINDOW *window);
        void close();
    private:
        int row, col;
    };
}