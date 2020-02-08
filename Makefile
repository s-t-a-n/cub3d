# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu <sverschu@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/06 16:50:22 by sverschu      #+#    #+#                  #
#    Updated: 2020/02/08 20:42:13 by sverschu      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

# build variables
BUFFER_SIZE=10 # buffer size used when using 'read' syscall

# directories
SRC_D = src
OBJ_D = obj
INC_D = inc

# C source and header files
SRC =	$(SRC_D)/libft/ft_atoi												\
		$(SRC_D)/libft/ft_strtol											\
		$(SRC_D)/libft/ft_strtoull											\
		$(SRC_D)/libft/ft_bzero												\
		$(SRC_D)/libft/ft_calloc											\
		$(SRC_D)/libft/ft_isupper											\
		$(SRC_D)/libft/ft_islower											\
		$(SRC_D)/libft/ft_isalnum											\
		$(SRC_D)/libft/ft_isalpha											\
		$(SRC_D)/libft/ft_isascii											\
		$(SRC_D)/libft/ft_isdigit											\
		$(SRC_D)/libft/ft_isprint											\
		$(SRC_D)/libft/ft_itoa												\
		$(SRC_D)/libft/ft_dtoa_sc1											\
		$(SRC_D)/libft/ft_dtoa_sc2											\
		$(SRC_D)/libft/ft_ltoa_base											\
		$(SRC_D)/libft/ft_lltoa_base										\
		$(SRC_D)/libft/ft_ultoa_base										\
		$(SRC_D)/libft/ft_ulltoa_base										\
		$(SRC_D)/libft/ft_ldtoa1											\
		$(SRC_D)/libft/ft_ldtoa2											\
		$(SRC_D)/libft/ft_memccpy											\
		$(SRC_D)/libft/ft_memchr											\
		$(SRC_D)/libft/ft_memcmp											\
		$(SRC_D)/libft/ft_memcpy											\
		$(SRC_D)/libft/ft_memmove											\
		$(SRC_D)/libft/ft_memset											\
		$(SRC_D)/libft/ft_putchar_fd										\
		$(SRC_D)/libft/ft_putwchar_fd										\
		$(SRC_D)/libft/ft_putendl_fd										\
		$(SRC_D)/libft/ft_putnbr_fd											\
		$(SRC_D)/libft/ft_putstr_fd											\
		$(SRC_D)/libft/ft_putwstr_fd										\
		$(SRC_D)/libft/ft_strsplit											\
		$(SRC_D)/libft/ft_strchr											\
		$(SRC_D)/libft/ft_strdup											\
		$(SRC_D)/libft/ft_strjoin											\
		$(SRC_D)/libft/ft_strlcat											\
		$(SRC_D)/libft/ft_strlcpy											\
		$(SRC_D)/libft/ft_strlen											\
		$(SRC_D)/libft/ft_wcslen											\
		$(SRC_D)/libft/ft_wclen												\
		$(SRC_D)/libft/ft_strmapi											\
		$(SRC_D)/libft/ft_strncmp											\
		$(SRC_D)/libft/ft_strnstr											\
		$(SRC_D)/libft/ft_strrchr											\
		$(SRC_D)/libft/ft_strtrim											\
		$(SRC_D)/libft/ft_strsub											\
		$(SRC_D)/libft/ft_tolower											\
		$(SRC_D)/libft/ft_toupper											\
		$(SRC_D)/libft/ft_arrayclear										\
		$(SRC_D)/libft/ft_strclen											\
		$(SRC_D)/libft/ft_isspace											\
		$(SRC_D)/libft/ft_issymbol											\
		$(SRC_D)/libft/ft_strndup											\
		$(SRC_D)/libft/ft_strnlen											\
		$(SRC_D)/libft/ft_swap												\
		$(SRC_D)/get_next_line/get_next_line								\
		$(SRC_D)/get_next_line/get_next_line_utils							\
		$(SRC_D)/cub3d														\
		$(SRC_D)/scene_description_read_from_file							\
		$(SRC_D)/scene_description_processing								\
		$(SRC_D)/scene_description_verification

SRC := $(SRC:%=%.c)

INC =	$(INC_D)/libft.h													\
		$(INC_D)/get_next_line.h											\
		$(INC_D)/cub3d.h
OBJ :=	$(SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

# outputting
CC_LOG=./.cc.log
CC_ERROR=./.cc.error

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

ECHO=printf
CAT=cat

# compiler and linker
CC = clang
#CC = gcc

# compile flags
CC_FLAGS = -Werror -Wextra -Wall
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

$(NAME): $(OBJ_D)  $(OBJ) $(INC)
	@$(ECHO) "Linking $(NAME)..."
	@$(CC) $(CC_FLAGS) -o $(NAME) $(OBJ) 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then											\
		$(ECHO) "$(ERROR_STRING)\n" && $(CAT) $(CC_LOG);					\
	elif test -s $(CC_LOG); then											\
		$(ECHO) "$(WARN_STRING)\n" && $(CAT) $(CC_LOG);						\
	else																	\
		$(ECHO) "$(OK_STRING)\n";											\
	fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(OBJ_D):
	@mkdir -p $(OBJ_D)/libft
	@mkdir -p $(OBJ_D)/get_next_line

$(OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(ECHO) "Compiling $<..."
	@$(CC) -I$(INC_D) -I$(SRC_D)/libft $(CC_FLAGS) -c $< -o $@ 2>$(CC_LOG) 	\
		|| touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then											\
		$(ECHO) "$(ERROR_STRING)\n" && $(CAT) $(CC_LOG);					\
	elif test -s $(CC_LOG); then											\
		$(ECHO) "$(WARN_STRING)\n" && $(CAT) $(CC_LOG);						\
	else																	\
		$(ECHO) "$(OK_STRING)\n";											\
	fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

clean:
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_D)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) bonus

re: fclean all

.PHONY = all clean fclean re bonus
