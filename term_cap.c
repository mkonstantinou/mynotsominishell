#include "myselect.h"
/*Pre: Void
 *Post: does tputs for all caps
 */

void term_clear()
{
    tputs(gl_env.clear, 1, my_termprint);
}

void term_standend()
{
    tputs(gl_env.stand_end, 1, my_termprint);
}

void term_standout()
{
    tputs(gl_env.standout, 1, my_termprint);
}

void term_underend()
{
    tputs(gl_env.under_end, 1, my_termprint);
}

void term_underline()
{
    tputs(gl_env.underline, 1, my_termprint);
}

void term_vi()
{
	//tputs(gl_env.cursoroff, 1, my_termprint);
	tputs(VICAP, 1, my_termprint);
}

void term_ve()
{
	//tputs(gl_env.cursoron, 1, my_termprint);
	tputs(VECAP, 1, my_termprint);
}
