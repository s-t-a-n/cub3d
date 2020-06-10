# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu <sverschu@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/10 00:10:28 by sverschu      #+#    #+#                  #
#    Updated: 2020/06/10 19:20:46 by sverschu      ########   odam.nl          #
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
		$(SRC_D)/scene_description_verification								\
		$(SRC_D)/scene_description_verification_map							\
		$(SRC_D)/mlx_interface												\
		$(SRC_D)/mlx_hooks													\
		$(SRC_D)/mlx_generic												\
		$(SRC_D)/mlx_rendering												\
		$(SRC_D)/mlx_initialisation											\
		$(SRC_D)/game														\
		$(SRC_D)/keyhandling												\
		$(SRC_D)/raycaster_initialisation									\
		$(SRC_D)/raycaster_initialisation1									\
		$(SRC_D)/raycaster_keyhandling										\
		$(SRC_D)/raycaster_keyhandling1										\
		$(SRC_D)/raycaster5													\
		$(SRC_D)/raycaster4													\
		$(SRC_D)/raycaster3													\
		$(SRC_D)/raycaster2													\
		$(SRC_D)/raycaster1													\


SRC := $(SRC:%=%.c)

INC =	$(INC_D)/libft.h													\
		$(INC_D)/get_next_line.h											\
		$(INC_D)/ft_printf.h												\
		$(INC_D)/mlx.h														\
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
CCL_FLAGS = -Werror -Wextra -Wall
#CC_FLAGS =	-Werror -Wextra -Wall	\
			-ftrapv					\
			-Wunreachable-code		\
			-fsanitize=undefined	\
			-fsanitize=address		\
			-fno-omit-frame-pointer	\
			-fstack-protector-all	\
			-fstack-check

ifeq ($(DEBUG),1)
	CC_FLAGS += -g -fsanitize=address -DDEBUG
	CCL_FLAGS += -g -fsanitize=address -DDEBUG
else
	CC_FLAGS += -Ofast -march=native
	CCL_FLAGS += -Ofast -march=native
endif

# dependencies
LIBFT = $(SRC_D)/libft/libft.a
LIBPRINTF = $(SRC_D)/ft_printf/libftprintf.a

# os variables
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    OS = LINUX
    CC_FLAGS += -D LINUX
    CCL_FLAGS += -lXext -lX11 -lm
    MINILIBX = libmlx.a
    MINILIBX_D = minilibx_linux
endif
ifeq ($(UNAME_S),Darwin)
    OS = OSX
    CC_FLAGS += -D OSX 
    CCL_FLAGS += -framework AppKit -framework OpenGL
    MINILIBX = libmlx.dylib
    MINILIBX_D = minilibx
endif

# make commands
all: $(NAME)

$(NAME): $(LIBFT) $(LIBPRINTF) $(MINILIBX) $(OBJ_D) $(OBJ) $(INC_D) $(INC)
	@$(ECHO) "Linking $(NAME)..."
	@$(CC) $(CCL_FLAGS) -o $(NAME) $(OBJ) $(LIBPRINTF) $(LIBFT) $(MINILIBX) 2>$(CC_LOG) || touch $(CC_ERROR)
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
	@$(CC) $(CC_FLAGS) -I$(INC_D) -I$(SRC_D)/libft -c $< -o $@ 2>$(CC_LOG) 	\
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

$(MINILIBX):
	@make -C $(SRC_D)/$(MINILIBX_D)
	@ln -s $(SRC_D)/$(MINILIBX_D)/$(MINILIBX) ./

clean:
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_D)
	@make -C $(SRC_D)/ft_printf clean
	@make -C $(SRC_D)/libft clean
	@make -C $(SRC_D)/$(MINILIBX_D) clean

fclean: clean
	@$(RM) $(NAME)
	@$(RM) bonus
	@make -C $(SRC_D)/ft_printf fclean
	@make -C $(SRC_D)/libft fclean
	@make -C $(SRC_D)/$(MINILIBX_D)/ clean
	@$(RM) -f $(MINILIBX)

lre:
	@$(RM) $(NAME)
	@$(RM) bonus
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_D)
	@make

re: fclean all

.PHONY = all clean fclean re bonus
