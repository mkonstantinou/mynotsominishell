#include "myselect.h"

char get_win_size()
{
    return ioctl(0,TIOCGWINSZ, &gl_env.win);
}

void reprint(int signal)
{
	char buffer[256];
	char *dir;
	term_clear();
	dir = getcwd(buffer, BUF_SZ);
	my_str(dir);
	my_str("&>");
	my_str(gl_env.strbuff);
    gl_env.x = my_strlen(dir) + 2 + gl_env.nbelems;
    term_move(gl_env.x, gl_env.y);
}
