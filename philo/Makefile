NAME =			philo

SRC =			main.c 	\
				parsing.c \
				manage_philos.c \
				free.c \
				eat.c \
				philos_utils.c \
				thread.c \
				display.c \
				utils.c 

CC =			gcc
	
FLAGS =			-Wall -Werror -Wextra

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

OBJS =			$(SRCS:.c=.o)

RM =			rm -rf

HEADERS =	-I $(DIR_HEADERS)

DIR_HEADERS = 		./include/

DIR_SRCS =		./srcs/

DIR_OBJS = 		./objs/
	

LIBS = 	-L$(DIR_LIBFT) -lft	

all:			$(NAME) $(BONUS)

$(NAME) :		$(OBJS)
			gcc  $(HEADERS) $(OBJS) -o $(NAME) -lpthread

%.o: %.c
				@$(CC) $(FLAGS) $(HEADERS) -c $< -o $@
				@echo "Compiled "$<" successfully!"
norme:
				norminette $(DIR_SRCS)
				norminette $(DIR_HEADERS)

clean:
			$(RM) $(OBJS)
			$(RM) $(BONUS_OBJS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(BONUS_NAME)

re:			fclean all

.PHONY:			all, clean, fclean, re, bonus
