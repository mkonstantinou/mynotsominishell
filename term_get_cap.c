#include "myselect.h"
/*Pre: Takes in the cap
 *Post: Returns the cap code
 *
 * Matthew Konstantinou
 * Scott Harris
 */

char *term_get_cap(char *cap)
{
    char *str;
    static char area[2048];
    if(!(str = tgetstr(cap, (char **)(&area))))
        my_panic("Getting cap failed");
    return str;
}

char check_char(char *c)
{
    char ch = c[0];

    if(ch == '\n')
    {
        //Save command to history
        if (gl_env.historysize < HISTORYMAX)
        {
            gl_env.history[gl_env.historysize] = my_strdup(gl_env.strbuff);
            gl_env.historysize++;
            gl_env.historyindex = gl_env.historysize;

        }
        else
        {
            free(gl_env.history[0]);
            gl_env.history += sizeof(char*); //shift history up
            gl_env.history[HISTORYMAX] = (char*)xmalloc(sizeof(char*)); //hopefully this isn't previously allocated by the program
            gl_env.history[HISTORYMAX] = my_strdup(gl_env.strbuff);
            //historysize and historyindex stay the same
        }
        return '\n';
    }
    else if(!my_strcmp(c, gl_env.left) || !my_strcmp(c, KL))
    {
        //if cursor x is not passed beginning of text
        if (gl_env.x > gl_env.xstart+1)
		{
			reprint(0);
            moveleft();
		}
        return 'L';
    }
    else if(!my_strcmp(c, gl_env.right) || !my_strcmp(c, KR))
    {
        //If cursor x is not passed text
        if (gl_env.x <= (gl_env.xstart + my_strlen(gl_env.strbuff)))
		{
			reprint(0);
            moveright();
		}
        return 'R';
    }
    else if(!my_strcmp(c, gl_env.up) || !my_strcmp(c, KU))
    {
        if (gl_env.historyindex > 0)
        {
            //Clear current strbuff
            int strlen = my_strlen(gl_env.strbuff);
            int start = gl_env.xstart;
            for (; strlen > 0; strlen--)
            {
                term_move(start + strlen, gl_env.y);
                my_termprint(' ');
            }
            term_move(gl_env.x, gl_env.y);

            //assign and print new strbuff
            gl_env.historyindex--;
            gl_env.strbuff = my_strdup(gl_env.history[gl_env.historyindex]);
            gl_env.nbelems = my_strlen(gl_env.strbuff);
            my_str(gl_env.strbuff);
        }

        return 'u';
    }
    else if(!my_strcmp(c, gl_env.down) || !my_strcmp(c, KD))
    {

        if (gl_env.historyindex < HISTORYMAX)
        {
            //if historypos is not at the most recent command
            //Clear current strbuff
            int strlen = my_strlen(gl_env.strbuff);
            int start = gl_env.xstart;
            for (; strlen > 0; strlen--)
            {
                term_move(start + strlen, gl_env.y);
                my_termprint(' ');
            }
            term_move(gl_env.x, gl_env.y);

            //assign and print new strbuff
            gl_env.historyindex++;
            gl_env.strbuff = my_strdup(gl_env.history[gl_env.historyindex]);
            gl_env.nbelems = my_strlen(gl_env.strbuff);
            my_str(gl_env.strbuff);
        }
        else if (gl_env.historyindex == HISTORYMAX)
        {
            //if historypos is at the most recent command, print the current strbuff
            int strlen = my_strlen(gl_env.strbuff);
            int start = gl_env.xstart;
            for (; strlen >= 0; strlen--)
            {
                term_move(start + strlen, gl_env.y);
                my_termprint(' ');
            }
            term_move(gl_env.x, gl_env.y);
            
            gl_env.strbuff = "";
            gl_env.nbelems = 0;
            my_str(gl_env.strbuff);
        }

        return 'd';
    }
    else if(ch == CTRL_K)
    {
        gl_env.clipboard = my_substr(gl_env.strbuff, gl_env.x-gl_env.xstart-1);
        int strlen = my_strlen(gl_env.strbuff);
        int len = my_strlen(gl_env.clipboard);
        for (; len >= 0; len--)
        {
            term_move(gl_env.x + len, gl_env.y);
            my_termprint(' ');
            gl_env.strbuff[strlen - len] = '\0';
        }
        term_move(gl_env.x, gl_env.y);

        return 'k';
    }
    else if(ch == CTRL_Y)
    {
        if (gl_env.clipboard != NULL)
        {
            gl_env.strbuff = my_strdup(gl_env.clipboard);
            gl_env.nbelems = my_strlen(gl_env.strbuff);
            my_str(gl_env.strbuff);
        }
        return 'y';
    }
    else if(ch == CTRL_A)
    {
        gl_env.x = gl_env.xstart+1;
        term_move(gl_env.x, gl_env.y);
        return 'a';
    }
    else if(ch == CTRL_E)
    {
        gl_env.x = gl_env.xstart + my_strlen(gl_env.strbuff);
        term_move(gl_env.x, gl_env.y);
        return 'e';
    }
    else if(ch == CTRL_L)
    {
        //Clear screen, reshow prompt and print current line
        gl_env.y = 0;
        term_clear();
        return 'l';
    }
    else if(ch == CTRL_C)
    {
        quit(0);
        return 'c';
    }
    else if(my_strcmp(c, gl_env.esc) == 0)
    {
        quit(0);
        return ESC;
    }
    else if (my_strcmp(c, gl_env.backspace) == 0)
    {
        /*if (gl_env.nbelems > 0)
          gl_env.strbuff[--gl_env.nbelems] = '\0';*/
        if(gl_env.nbelems > 0)
        {
            int x = gl_env.x - gl_env.xstart - 1;
			reprint(0);
            if(x > 0 && x < gl_env.nbelems)
            {
                int i;
                int len = my_strlen(gl_env.strbuff);
                moveleft();
                for(i = x-1; i+1 < len;i++)
                {
                    gl_env.strbuff[i] = gl_env.strbuff[i+1];
                    my_termprint(gl_env.strbuff[i+1]);
                }
                my_termprint(' ');
                term_move(gl_env.x, gl_env.y);
                gl_env.strbuff[i] = '\0';
                gl_env.nbelems--;
            }
            else if(x >= gl_env.nbelems)        //end of string
            {
                gl_env.strbuff[--gl_env.nbelems] = '\0';
                moveleft();
                my_termprint(' ');
                term_move(gl_env.x, gl_env.y);
            }
        }
        return 'b';
    }
    else 
    {
        return '\0';
    }
}

