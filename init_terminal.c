#include "myselect.h"

void init_terminal()
{
    int fd;
    char* name;
    struct termios line;

    name = ttyname(0);
    fd = open(name, O_WRONLY);

    gl_env.stdio_backup = dup(1);
    dup2(fd, 1);

    signal(SIGINT, quit);

    if (tcgetattr(fd, &(gl_env.line_backup)) < 0)
    {
        my_str("error tcgetattr");
        exit(1);
    }

    line = gl_env.line_backup;
    line.c_lflag &= ~(ICANON | ECHO | ISIG);
    line.c_cc[VMIN] = READMIN;
    line.c_cc[VTIME] = READTIME;

    if (tcsetattr(fd, TCSAFLUSH, &line) < 0)
    {
        my_str("error tcsetattr");
        exit(1);
    }

    get_win_size();
}
