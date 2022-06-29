NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC =  philo_bonus.c philo_func_bonus.c philo_func1_bonus.c
OBJ = ${SRC:.c=.o}
RM = rm -f

all: ${NAME}

${NAME}: $(OBJ)
	${CC} ${OBJ}  -o ${NAME}
%.o : %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME} 

re: fclean all

.PHONY: clean all bonus fclean re