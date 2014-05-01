NAME=mynotsominishell
SRC=mynotsominishell.c
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
