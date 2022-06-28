NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
SRC = philo_func.c philo.c
SRCB = 
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