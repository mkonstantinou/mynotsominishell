#include "myselect.h"

void quit(int n)
{
    //exit
    my_str("Thanks for playing");

    ioctl(0, TCSETA, &(gl_env.line_backup));
	dup2(gl_env.stdio_backup, 1);
	exit(0);
}
