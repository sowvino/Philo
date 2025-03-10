NAME = philo

MY_SOURCES = main.c \
			 data_init.c \
			 monitor.c \
			 parsing.c \
			 routine.c \
			 threads.c \
			 utilis.c\
			 clean.c

OBJECTS = $(MY_SOURCES:.c=.o)

COMPILER = cc

CFLAGS = -Wall -Wextra -Werror -pthread 

INCS = philo.h

RM = rm -f

$(NAME): $(OBJECTS) $(INCS)
	$(COMPILER) $(CFLAGS) $(OBJECTS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJECTS)

fclean:clean
	$(RM) $(NAME)

re:fclean all

.PHONY:all clean fclean re