NAME	= philosophers

CC	= cc
INCLUDE		= -I ./include
CFLAGS		= -g -Wall -Wextra -Werror $(INCLUDE)

RM	= rm -rf

PATH_SRCS	= ./src/
PATH_OBJS	= ./objs/

SRCS	= $(PATH_SRCS)main.c \
		#$(PATH_MAIN)main.c \

OBJS	= $(patsubst $(PATH_SRCS)%.c, $(PATH_OBJS)%.o, $(SRCS))

all:	$(NAME)

$(NAME):	$(OBJS) 
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

$(PATH_OBJS)%.o:	$(PATH_SRCS)%.c
		@mkdir -p $(PATH_OBJS)
		@mkdir -p $(PATH_OBJS)src/
		$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):     
	make -C ./libft

clean:
	$(RM) ./objs

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft

re:	fclean all

.PHONY:	all $(PATH_OBJS) clean fclean re