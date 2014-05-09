#ifndef _MYSELECT_H_
#define _MYSELECT_H_

#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/termios.h>
#include "../lib/my.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>
#include "../lib/mylist.h"

#define READTIME 1
/* used to return from read after 1/10th of  second passed from the first byte read */

#define READMIN 3
/* used to return from min if 3 bytes have been read. Needed for things like characters which are \E[A B C or D */

#define BUF_SZ 256

#ifndef NULL
#define NULL (0)
#endif

#define KU "\E[A"
#define KD "\E[B"
#define KR "\E[C"
#define KL "\E[D"
#define UP "ku"
#define DOWN "kd"
#define LEFT "kl"
#define RIGHT "kr"
#define CLEAR "cl"
#define MOVE "cm"
#define STANDOUT "so"
#define STAND_END "se"
#define UNDERLINE "us"
#define UNDER_END "ue"
#define CURSOROFF "vi"
#define CURSORON "ve"
#define HISTORYMAX 100
#define VECAP "\E[?25h" // actual string for VE in case tgetstr doesn't find it
#define VICAP "\E[?25l" // same as above but for VI
//#define ESC "\033"
#define ESC 27
#define CTRL_K 11
#define CTRL_Y 25
#define CTRL_A 1
#define CTRL_E 5
#define CTRL_L 12
#define CTRL_C 35

#define SPACE "\040"
#define ENTER "\013"
#define BACKSPACE 127

typedef struct	s_elem
{
  char		*elem;
  int		size;
  int		x;
  int		y;
  int		mode;
}		t_elem;

typedef struct	s_env
{
  char		*left;
  char		*right;
  char		*up;
  char		*down;
  char		*esc;
  char		*backspace;
  char		*underline;
  char		*under_end;
  char		*standout;
  char		*stand_end;
  char		*move;
  char		*clear;
  char		*cursoroff;
  char		*cursoron;
  struct winsize win;
  struct termios	line_backup;
  int		flag;
  int		stdio_backup;
  int		nbelems;
  int		pos;
  t_elem    *elements;
  char	    *strbuff;
  //char      *history[HISTORYMAX];
  char      **history;
  int       historysize;
  int       historyindex;
  char      *copybuff;
  int       xstart;
  int 		x;
  int 		y;
}		t_env;

t_env	gl_env;
// created as a structure to limit number of globals to 1

void	init_terminal();
void	restore_terminal();
char	*term_get_cap(char*);
void	init_caps();
int	my_termprint(int);
void	term_clear();
void	term_vi();
void	term_ve();
char	check_character(char *c);
char	get_win_size();
void	show_elems();
void    show_selection();
void	refreshin();
void	refreshout(int);
void	moveup();
void	movedown();
void	moveleft();
void	moveright();
void	doselect();
void	getout();
void	setup_elems(int, char**);
char	check_char(char*);
void	term_move_to_item(int);
void	term_underline();
void	term_standout();
void	term_standend();
void	term_underend();
void    quit(int);
void	term_move(int, int);
void 	reprint(int);
#endif
