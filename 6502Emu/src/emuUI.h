#include <ncurses.h>

namespace emu6502 
{
    class emuUI 
    {
        public:
        emuUI();
        ~emuUI();
        void initUI();
        void close();
    };
}