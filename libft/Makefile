# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/30 11:49:37 by bmarecha          #+#    #+#              #
#    Updated: 2021/11/24 23:58:52 by bmarecha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_atof.c \
		ft_strlen.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strdup.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_calloc.c \
		ft_putchar_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_strjoin.c \
		ft_itoa.c \
		ft_str_end.c \
		ft_strmapi.c \
		ft_split.c

SRCS_BONUS = 	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstadd_back.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstiter.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstmap.c \
		ft_lstget.c

OBJS	=	${SRCS:.c=.o}

OBJS_BONUS =	${SRCS_BONUS:.c=.o}

NAME	=	libft.a

.c.o	:
	gcc -Wall -Werror -Wextra -Iincludes/ -c $< -o ${<:.c=.o}

$(NAME)	:	${OBJS} ${OBJS_BONUS}
	ar -rc ${NAME} ${OBJS} ${ONJS_BONUS}

all		:	${NAME}

bonus	:	${OBJS} ${OBJS_BONUS}
	ar -rc ${NAME} ${OBJS} ${OBJS_BONUS}

clean	:
	rm -f ${OBJS} ${OBJS_BONUS}

fclean	:	clean
	rm -f ${NAME}

re		: fclean all bonus

.PHONY	: all clean fclean re
