# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu <sverschu@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/10 00:10:28 by sverschu      #+#    #+#                  #
#    Updated: 2020/02/10 00:28:45 by sverschu      ########   odam.nl          #
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
SRC =	$(SRC_D)/get_next_line/get_next_line								\
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


LIBFT = $(SRC_D)/libft/libft.a
LIBPRINTF = $(SRC_D)/ft_printf/libftprintf.a

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
CC_FLAGS = -Werror -Wextra -Wall -g -fsanitize=address
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

$(NAME): $(OBJ_D) $(OBJ) $(INC) $(LIBFT) $(LIBPRINTF)
	@$(ECHO) "Linking $(NAME)..."
	@$(CC) $(CC_FLAGS) -o $(NAME) $(OBJ) $(LIBPRINTF) $(LIBFT) 2>$(CC_LOG) || touch $(CC_ERROR)
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

$(LIBPRINTF):
	@make -C $(SRC_D)/ft_printf

$(LIBFT):
	@make -C $(SRC_D)/libft

clean:
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_D)
	@make -C $(SRC_D)/ft_printf clean
	@make -C $(SRC_D)/libft clean

fclean: clean
	@$(RM) $(NAME)
	@$(RM) bonus
	@make -C $(SRC_D)/ft_printf fclean
	@make -C $(SRC_D)/libft fclean

re: fclean all

.PHONY = all clean fclean re bonus
