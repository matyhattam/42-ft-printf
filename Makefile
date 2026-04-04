FTPRINTF       = libftprintf.a
LIBFT          = ../libft/libft.a

SRCS           = ft_printf.c \
						src/ft_formatting_utils.c \
						src/ft_parsing_utils.c \
						src/ft_printf_utils.c
all:
	make -C ../libft
	clang -Wall -Wextra -Wextra -Werror -c ${SRCS}
	cp ../libft/libft.a ${FTPRINTF}
	ar rcs ${FTPRINTF} *.o

bonus: all

clean:
	rm -f *.o

fclean: clean
	rm -f ${FTPRINTF}

re: fclean all

.PHONY: all clean fclean re

