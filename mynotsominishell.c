#include "../lib/my.h"
#include "myselect.h"

int main(int argc, char** argv)
{
    int n;
    int m;
    char array[100];
    init_terminal();
    char *dir;
    char* buffer = (char *)xmalloc(BUF_SZ*sizeof(char));
    char** vect;
    pid_t pid;
    char check;
    term_clear();

    gl_env.history = (char**)xmalloc(HISTORYMAX * sizeof(char*));

    dir = getcwd(buffer, BUF_SZ);
    my_str(dir);
    my_str("&>");
    while(1)
    {
        signal(SIGINT, quit);
        n = read(0, (void *)buffer, 3);
        buffer[n] = '\0';

        check = check_char(buffer);
        
        if (check == '\0')
        {
            //Add to stringbuffer
            gl_env.strbuff[gl_env.nbelems] = buffer[0];
            gl_env.nbelems++;
            my_termprint(buffer[0]);
        }
        else if (check == 'l' || check == 'L')
        {
            dir = getcwd(buffer, BUF_SZ); 
            my_str(dir);
            my_str("&>");
            my_str(gl_env.strbuff);
        }
        else if (check == '\n')
        {
            my_termprint('\n');

            vect = my_str2vect(gl_env.strbuff);

            if ((pid=fork()) < 0)
            {
                my_str("Process failed to fork\n");
                exit(1);
            }

            if (pid>0) //Parent
            {
                wait();
            }
            else
            {
                if (execvp(vect[0], vect) < 0)
                {
                    my_str("ERROR: ");
                    my_str(my_strconcat(vect[0], " not found.\n"));
                }
                exit(1);
            }
            dir = getcwd(buffer, BUF_SZ);
            my_str(dir);
            my_str("&>");
            gl_env.strbuff = (char*)xmalloc(BUF_SZ*sizeof(char));
            gl_env.nbelems = 0;
        }


        /*
           if (!my_strcmp(buffer, "exit"))
           {
           my_str("thanks for doing the things bye\n");
           exit(0);
           }
           else if (!my_strcmp(vect[0],"cd"))
           {
           if (vect[1] != NULL)
           if ((m =chdir(vect[1])) < 0)
           my_str("Cannot find directory");
           }
           else if(check_char(buffer) == ESC)
           quit(0);
           else
           {
           if ((pid=fork()) < 0)
           {
           my_str("Process failed to fork\n");
           exit(1);
           }

           if (pid>0) //Parent
           {
           wait();
           }
           else
           {
           if (execvp(vect[0], vect) < 0)
           {
           my_str("ERROR: ");
           my_str(my_strconcat(vect[0], " not found.\n"));
           }
           exit(1);
           }
           }*/
    }
}
