NAME 		= philo/philo
NAME_BONUS  = philo_bonus/philo_bonus
CFLAGS 		= -Wall -Wextra -Werror #-g -fsanitize=address
MANDATORY 	= philo/main.c philo/ft_atoi.c philo/utils.c philo/creat_potok.c
BON_FILE	= philo_bonus/main.c philo_bonus/utils.c \
				philo_bonus/atoi.c philo_bonus/create_proc.c \
				philo_bonus/parser.c
OBJ_MAN 	= $(patsubst %.c,%.o,$(MANDATORY))
OBJ_BON		= $(patsubst %.c,%.o,$(BON_FILE))

all 			: $(NAME)

bonus 			: $(NAME_BONUS)

$(NAME) 		: $(OBJ_MAN)
				$(CC) $(CFLAGS) $(OBJ_MAN) -o $(NAME) 

$(NAME_BONUS)	: $(OBJ_BON)
				$(CC) $(CFLAGS) $(OBJ_BON) -o $(NAME_BONUS)

%.o : %.c philo/philo.h philo_bonus/philo_bonus.h Makefile
		gcc $(CFLAGS) -c $< -o $@ -g

clean			:
				rm -f $(OBJ_MAN) $(OBJ_BON)

fclean 			: clean
				rm -f $(NAME) $(NAME_BONUS)

re 				: fclean all

.PHONY 			: all clean fclean re
