NAME  = cub3D

SRCS  =  src/main.c \
	src/parser.c \
	src/parser_map.c \
	src/parser_colors.c \
	src/checker.c \
	src/free.c \
	src/utils.c \
	../gnl/get_next_line.c \
	../src/get_next_line_utilis.c

OBJS  = ${SRCS:.c=.o}

HEADERS= includes/cub3d.h

CC= clang

CFLAGS= -Wall -Wextra -Werror -g3 

LIBFT= -L libft -lft

VALGRIND = colour-valgrind 


all: 		lib ${NAME} 

${NAME}: 	${OBJS}
				${CC} ${CFLAGS} -L /usr/lib ${OBJS} ${LIBFT} -o ${NAME}

.c.o:
				${CC} ${CFLAGS} -I/usr/include -I${HEADERS} -Imlx -O3 -c $< -o $@

lib:
				make -C libft

clean:
				rm -f ${OBJS} 
							make -C libft clean

fclean:clean
				rm -f ${NAME}
							make -C libft fclean

re:fclean all

norm:
				norminette -R CheckSourceHeader ${SRCS}

.PHONY :all clean fclean re norm 
