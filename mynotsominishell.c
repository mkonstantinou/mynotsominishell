#include "../lib/my.h"
#include "myselect.h"

int main(int argc, char** argv)
{
    int n;
    int m;
	int len;
    char array[100];
    init_terminal();
    char *dir;
    char* buffer = (char *)xmalloc(BUF_SZ*sizeof(char));
    char** vect;
    pid_t pid;
    char check;
    term_clear();

    //signal(SIGINT, quit);
	signal(SIGWINCH, reprint);
    dir = getcwd(buffer, BUF_SZ);
    my_str(dir);
    my_str("&>");
	len = my_strlen(dir);
	gl_env.x = len + 2;
	gl_env.y = 0;
    gl_env.xstart = gl_env.x-1;

    while(1)
    {

        n = read(0, (void *)buffer, 3);
        buffer[n] = '\0';

        check = check_char(buffer);

        if (check == '\0')
        {
            //Add to stringbuffer
			gl_env.x += 1;
            gl_env.strbuff[gl_env.nbelems] = buffer[0];
            gl_env.nbelems++;
            my_termprint(buffer[0]);
        }
        else if (check == 'l')
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
           
            if (!my_strcmp(vect[0], "cd"))
            {
                if (vect[1] != NULL)
                    if ((m =chdir(vect[1])) < 0)
                        my_str("Cannot find directory");
            }
			else if(!my_strcmp(vect[0], "exit"))
				quit(0);
            else if ((pid=fork()) < 0)
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
			len = my_strlen(dir);
			gl_env.x = len + 2;
			gl_env.xstart = gl_env.x-1;
            gl_env.strbuff = (char*)xmalloc(BUF_SZ*sizeof(char));
            gl_env.nbelems = 0;


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
}
