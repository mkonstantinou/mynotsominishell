#include "myselect.h"
/*Pre: Takes in the cap
 *Post: Returns the cap code
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
            moveleft();
        return 'L';
    }
    else if(!my_strcmp(c, gl_env.right) || !my_strcmp(c, KR))
    {
        //If cursor x is not passed text
        if (gl_env.x <= (gl_env.xstart + my_strlen(gl_env.strbuff)))
            moveright();
        return 'R';
    }
    else if(!my_strcmp(c, gl_env.up) || !my_strcmp(c, KU))
    {
        if (gl_env.historyindex > 0)
        {
            //lineclear();
            gl_env.historyindex--;
            gl_env.strbuff = my_strdup(gl_env.history[gl_env.historyindex]);
            my_str(gl_env.strbuff);
        }
        
        return 'u';
    }
    else if(!my_strcmp(c, gl_env.down) || !my_strcmp(c, KD))
    {
        
        if (gl_env.historyindex < HISTORYMAX)
        {
            //if historypos is not at the most recent command
            //lineclear();
            gl_env.historyindex++;
            gl_env.strbuff = my_strdup(gl_env.history[gl_env.historyindex]);
            my_str(gl_env.strbuff);
        }
        else if (gl_env.historyindex == HISTORYMAX)
        {
            //if historypos is at the most recent command, print the current strbuff
            //lineclear();
            gl_env.strbuff = "";
            my_str(gl_env.strbuff);
        }
        
        return 'd';
    }
    else if(ch == CTRL_K)
    {
        gl_env.clipboard = my_substr(gl_env.strbuff, gl_env.x-gl_env.xstart-1);
        
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
        return 'c';
    else if(my_strcmp(c, gl_env.esc) == 0)
    {
        quit(0);
        return ESC;
    }
    else if (my_strcmp(c, gl_env.backspace) == 0)
    {
        if (gl_env.nbelems > 0)
            gl_env.strbuff[--gl_env.nbelems] = '\0';
        return 'b';
    }
    else 
    {
        return '\0';
    }
}

