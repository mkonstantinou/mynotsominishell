#include "myselect.h"
/*Pre: Takes in coordinates
 *Post: Moves the position in terminal
 */

void term_move(int x, int y)
{
	tputs(tgoto(gl_env.move, x, y), 1, my_termprint);
}

void moveup()
{
	/*
	int i;
	int x = gl_env.elements[gl_env.pos].x;
	int y = gl_env.elements[gl_env.pos].y - 1;
	//term_underend();
	//show_elems();
	for(i = 0;i < gl_env.nbelems;i++)
	{
		if(gl_env.elements[i].x == x && gl_env.elements[i].y == y)
		{
			gl_env.pos = i;
			term_move(x);
			//term_underline();
			//show_elems();
			return;
		}
		else
			;
	}
	*/
}

void movedown()
{
	/*
	int i;
    int x = gl_env.elements[gl_env.pos].x;
    int y = gl_env.elements[gl_env.pos].y + 1;
	//term_underend();
	//show_elems();
 	for(i = 0;i < gl_env.nbelems;i++)
    {
        if(gl_env.elements[i].x == x && gl_env.elements[i].y == y)
        {
            gl_env.pos = i;
            term_move(x);
			//term_underline();
			//show_elems();
            return;
        }
        else
            ;
    }
	*/
}

void moveleft()
{
	gl_env.x -=  1;
	term_move(gl_env.x, gl_env.y);
}

void moveright()
{
	gl_env.x += 1;
	term_move(gl_env.x, gl_env.y);
}

void deselect()
{
	if(gl_env.elements[gl_env.pos].mode == 0)
	{
		gl_env.elements[gl_env.pos].mode = 1;
		//term_standout();
		//show_elems();
	}
	else {
		gl_env.elements[gl_env.pos].mode = 0;
		//term_standend();
		//show_elems();
	}
}
