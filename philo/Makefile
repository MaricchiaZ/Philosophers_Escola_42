NAME	= philo

CC	= cc
INCLUDE		= -I ./include
CFLAGS		= -g -pthread -Wall -Wextra -Werror $(INCLUDE)

RM	= rm -rf

PATH_SRC	= ./src/
PATH_OBJS	= ./objs/

SRCS	= $(PATH_SRC)main.c \
		$(PATH_SRC)check_args.c \
		$(PATH_SRC)init_free.c \
		$(PATH_SRC)life_philos.c \
		$(PATH_SRC)to_sleep.c \
		$(PATH_SRC)utils.c \

OBJS	= $(patsubst $(PATH_SRCS)%.c, $(PATH_OBJS)%.o, $(SRCS))

all:	$(NAME)

$(NAME):	$(OBJS) 
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

$(PATH_OBJS)%.o:	$(PATH_SRCS)%.c
		@mkdir -p $(PATH_OBJS)
		@mkdir -p $(PATH_OBJS)src/
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) ./objs

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all $(PATH_OBJS) clean fclean re