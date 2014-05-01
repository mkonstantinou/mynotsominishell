#include "myselect.h"

char get_win_size()
{
    return ioctl(0,TIOCGWINSZ, &gl_env.win);
}
