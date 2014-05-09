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
        write(fd, gl_env.history[i], my_strlen(gl_env.history[i]-1));
        write(fd, "\n", 1);
    }

    close(fd);

    //exit
    my_str("\nThanks for playing\n");
    
    ioctl(0, TCSETA, &(gl_env.line_backup));
	dup2(gl_env.stdio_backup, 1);
	exit(0);
}
