#include "myselect.h"

void quit(int n)
{
    int i;
    int fd;
    char* filename;

    filename = ".history";
    fd = open(filename, O_WRONLY);
    
    //create .history
    for(i=0; gl_env.history[i] != NULL; i++)
    {
        write(fd, gl_env.history[i], my_strlen(gl_env.history[i]));
        write(fd, "\n", 1);

        free(gl_env.history[i]);
    }

    close(fd);
    free(filename);

    
    getout();

    //exit
    my_str("\nThanks for playing\n");
    
    ioctl(0, TCSETA, &(gl_env.line_backup));
	dup2(gl_env.stdio_backup, 1);
	exit(0);
}

void getout()
{
    free(gl_env.history);
    free(gl_env.left);
    free(gl_env.right);
    free(gl_env.up);
    free(gl_env.down);
    free(gl_env.esc);
    free(gl_env.backspace);
    free(gl_env.underline);
    free(gl_env.under_end);
    free(gl_env.standout);
    free(gl_env.stand_end);
    free(gl_env.move);
    free(gl_env.clear);
    free(gl_env.cursoroff);
    free(gl_env.cursoron);
    free(gl_env.strbuff);
    free(gl_env.clipboard);
}
