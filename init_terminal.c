#include "myselect.h"
/* Scott Harris
 * Matthew Konstantinou
 */

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

void init_history()
{
    int i;
    int n;
    int fd;
    char* filename;
    char* filebuff;
    char* buff;

    i=0;
    filename = ".history";
    filebuff = (char*)xmalloc(BUF_SZ * sizeof(char));
    buff = (char*)xmalloc(BUF_SZ * sizeof(char));
   
    gl_env.history = (char**)xmalloc(HISTORYMAX * sizeof(char*));
    gl_env.historysize = 0;
    gl_env.historyindex = 0;
    fd = open(filename, O_RDONLY);
   
    while ((n=read(fd, (void*)filebuff, 1)) > 0)
    {
        if (filebuff[0] != '\n')
        {
            buff[i] = filebuff[0];
            i++;
        }
        else
        {
            buff[i] = '\0';
            gl_env.history[gl_env.historysize] = my_strdup(buff);
            gl_env.historysize++;
            gl_env.historyindex++;
            buff = (char*)xmalloc(BUF_SZ * sizeof(char));
            i = 0;
        }
    }

    close(fd);
}

void init_terminal()
{
    
  	struct termio line;
    ioctl(0, TCGETA, &line);
    gl_env.line_backup = line;
    line.c_cc[VMIN] = READMIN;
    line.c_cc[VTIME] = READTIME;
    line.c_lflag &= ~(ICANON|ECHO|ISIG);
    ioctl(0, TCSETA, &line);
    //--------------------------
    int fd;
    char *name;
    name = ttyname(0);
    fd = open(name, O_WRONLY);
    gl_env.stdio_backup = dup(1);
    dup2(fd, 1);

	gl_env.strbuff = (char*)xmalloc(BUF_SZ * sizeof(char));
    gl_env.clipboard = (char*)xmalloc(BUF_SZ * sizeof(char));
	get_win_size();
    init_caps();
    init_history();
	signal(SIGINT, quit);
}
