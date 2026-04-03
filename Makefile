LIBFTPRINTF       = libftprintf.a

all:
	clang -Wall -Wextra -Wextra -Werror -c *.c
	ar rcs ${LIBFTPRINTF} *.o

bonus: all

clean:
	rm -f *.o

fclean: clean
	rm -f ${LIBFTPRINTF}

re: fclean all

.PHONY: all clean fclean re

