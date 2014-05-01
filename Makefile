NAME=mynotsominishell
SRC=mynotsominishell.c init_terminal.c get_win_size.c
OBJ=$(SRC:.c=.o)
LIBPATH=../lib
RM=rm -f
LIBS=-lmy -lpthread
#
all:$(OBJ)
	cc -L$(LIBPATH) $(SRC) $(LIBS) -o $(NAME)
clean:
	-$(RM) *.o
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.swp
	-$(RM) *.core
fclean:clean
re:fclean all
