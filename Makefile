SRCS	=	parsing/pa_init.c \
			parsing/pa_check.c \
			parsing/pa_parse.c \
			parsing/pa_signals.c \
			parsing/pa_test.c \
			parsing/pa_utils1.c \
			parsing/pa_utils2.c \
			parsing/pa_utils3.c \
			parsing/pa_redirections.c \
			parsing/pa_env.c \
			parsing/pa_error.c \
			parsing/pa_heredoc.c \
			executing/chain_cmd.c \
			executing/built_in.c \
			executing/vne_built_in.c \
			executing/get_cmd.c \
			executing/utils.c \
			executing/alpha_print.c \
			executing/ft_cd.c

OBJS	=	${SRCS:.c=.o}

NAME	=	minishell

LIBFT = libft/libft.a

INCLUDES = -Ilibft/ \
		-Iparsing/ \
		-Iexecuting/

LIBS = -lft -Llibft/ -L/usr/include -lreadline

.c.o	:
	gcc -Wall -Werror -Wextra -c $< ${INCLUDES} -o ${<:.c=.o}

all     :   ${NAME}

$(LIBFT) :
	make -C libft/

$(NAME)	: ${OBJS}
	@make --no-print-directory -C libft
	gcc -o ${NAME} ${OBJS} ${INCLUDES} ${LIBS}

clean	:
	rm -f ${OBJS}
	@make --no-print-directory clean -C libft/

fclean	:	clean
	@make --no-print-directory fclean -C libft/
	rm -f ${NAME}

re		: fclean all 

.PHONY	: all clean fclean re
