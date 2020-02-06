# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu </var/mail/sverschu>                +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/30 16:10:10 by sverschu      #+#    #+#                  #
#    Updated: 2020/02/06 18:57:41 by sverschu      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# C sourcefiles & objects
SRC =	atoi				\
		strtol				\
		strtoull			\
		bzero				\
		calloc				\
		isupper				\
		islower				\
		isalnum				\
		isalpha				\
		isascii				\
		isdigit				\
		isprint				\
		itoa				\
		dtoa_sc1			\
		dtoa_sc2			\
		ltoa_base			\
		lltoa_base			\
		ultoa_base			\
		ulltoa_base			\
		ldtoa1				\
		ldtoa2				\
		memccpy				\
		memchr 				\
		memcmp				\
		memcpy				\
		memmove				\
		memset				\
		putchar_fd			\
		putwchar_fd			\
		putendl_fd			\
		putnbr_fd			\
		putstr_fd			\
		strsplit			\
		strchr				\
		strdup				\
		strjoin				\
		strlcat				\
		strlcpy				\
		strlen				\
		strmapi				\
		strncmp				\
		strnstr				\
		strrchr				\
		strtrim				\
		strsub				\
		tolower				\
		toupper 			\
		arrayclear			\
		strclen				\
		isspace				\
		issymbol			\
		strndup				\
		strnlen				\
		swap				\
		vector
SRC := $(SRC:%=ft_%.c)
OBJ = $(SRC:.c=.o)

# compiler and linker
CC = clang
#CC = gcc

# compile flags
CC_FLAGS = -Werror -Wextra -Wall -g
#CC_FLAGS =	-Werror -Wextra -Wall	\
			-ftrapv					\
			-Wunreachable-code		\
			-fsanitize=undefined	\
			-fsanitize=address		\
			-fno-omit-frame-pointer	\
			-fstack-protector-all	\
			-fstack-check

# make commands
all: $(NAME)

%.o: %.c
	@echo "$<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@$(RM) $(OBJ) $(BONUS_OBJ) bonus

fclean: clean
	@$(RM) $(NAME)

re: fclean all
