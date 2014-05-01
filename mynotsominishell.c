#include "../lib/my.h"
#include <unistd.h>

int main(int argc, char** argv)
{
    int n;
    int m;
    char* buffer = (char*)xmalloc(BUF_SZ*sizeof(char));
    char** vect;
    pid_t pid;
    

    while(1)
    {
        my_str("&>");
        n = read(0,(void*)buffer,BUF_SZ-1);
        buffer[n-1] = '\0';
        
        vect = my_str2vect(buffer);

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
        }
    }
}
