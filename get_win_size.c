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
}
