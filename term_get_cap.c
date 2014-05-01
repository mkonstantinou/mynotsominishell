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
