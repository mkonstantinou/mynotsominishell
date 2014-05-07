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
    if(c[0] == '\n')
        return '\n';
   	 
    else if(!my_strcmp(c, gl_env.left) || !my_strcmp(c, KL))
        return 'l';
    else if(!my_strcmp(c, gl_env.right) || !my_strcmp(c, KR))
        return 'r';
    else if(!my_strcmp(c, gl_env.up) || !my_strcmp(c, KU))
        return 'u';
    else if(!my_strcmp(c, gl_env.down) || !my_strcmp(c, KD))
        return 'd';
    else if(c[0] == CTRL_K)
    {
	return 'k';
    }
    else if(c[0] == CTRL_Y)
    {
        return 'y';
    }
    else if(c[0] == CTRL_A)
        return 'a';
    else if(c[0] == CTRL_E)
        return 'e';
    else if(c[0] == CTRL_L)
        return 't';
    else if(c[0] == CTRL_C)
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

