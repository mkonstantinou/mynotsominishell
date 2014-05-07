#include "myselect.h"


void init_caps()
{
    char *term;
    term = getenv("TERM");
    if(term != NULL)
    {
        char bp[2048];
        tgetent(bp, term);
        //not sure if arrows are needed
        gl_env.up = term_get_cap(UP);
        gl_env.down = term_get_cap(DOWN);
        gl_env.right = term_get_cap(RIGHT);
        gl_env.left = term_get_cap(LEFT);
        gl_env.clear = term_get_cap(CLEAR);
        gl_env.move = term_get_cap(MOVE);
        gl_env.standout = term_get_cap(STANDOUT);
        gl_env.stand_end = term_get_cap(STAND_END);
        gl_env.underline = term_get_cap(UNDERLINE);
        gl_env.under_end = term_get_cap(UNDER_END);
        //watch this
        gl_env.esc = (char *)xmalloc(2 * sizeof(char));
        gl_env.esc[0] = ESC;
        gl_env.esc[1] = '\0';
	gl_env.backspace = (char*)xmalloc(2 * sizeof(char));
	gl_env.backspace[0] = BACKSPACE;
	gl_env.backspace[1] = '\0';	
   }
    else {
        my_panic("Term is null!\n");
    }
}

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

	ioctl(0, TCGETA, &line);
    gl_env.line_backup = line;
    line.c_lflag &= ~(ICANON | ECHO | ISIG);
    line.c_cc[VMIN] = READMIN;
    line.c_cc[VTIME] = READTIME;
	ioctl(0, TCSETA, &line);

    if (tcsetattr(fd, TCSAFLUSH, &line) < 0)
    {
        my_str("error tcsetattr");
        exit(1);
    }
    gl_env.strbuff = (char*)xmalloc(BUF_SZ * sizeof(char));
    gl_env.copybuff = (char*)xmalloc(BUF_SZ * sizeof(char));

    get_win_size();
	init_caps();
}
