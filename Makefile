# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu <sverschu@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/10 00:10:28 by sverschu      #+#    #+#                  #
#    Updated: 2020/06/19 22:07:31 by sverschu      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# build variables
BUFFER_SIZE=10 # buffer size used when using 'read' syscall

# directories
SRC_D = src
OBJ_D = obj
INC_D = inc
LIB_D = lib
TEXT_D = textures

# C source and header files
SRC =	$(SRC_D)/cub3d														\
		$(SRC_D)/scene_description_read_from_file							\
		$(SRC_D)/scene_description_read_from_file1							\
		$(SRC_D)/scene_description_read_from_file2							\
		$(SRC_D)/scene_description_read_from_file3							\
		$(SRC_D)/scene_description_processing1								\
		$(SRC_D)/scene_description_processing2								\
		$(SRC_D)/scene_description_processing3								\
		$(SRC_D)/scene_description_verification								\
		$(SRC_D)/scene_description_verification1							\
		$(SRC_D)/scene_description_verification_map							\
		$(SRC_D)/scene_description_verification_map1						\
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
		$(SRC_D)/file														\
		$(SRC_D)/bmp														\
		$(SRC_D)/bmp1														\
		$(SRC_D)/bmp_wrapper
SRC := $(SRC:%=%.c)
INC =	$(INC_D)/cub3d.h													\
		$(INC_D)/file.h														\
		$(INC_D)/bmp.h
OBJ :=	$(SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

# dependencies
LIBFT = $(LIB_D)/libft/libft.a
LIBPRINTF = $(LIB_D)/libprintf/libftprintf.a
GET_NEXT_LINE = $(LIB_D)/get_next_line/get_next_line.a

LIB_INC = -I$(LIB_D)/libprintf/inc/											\
		  -I$(LIB_D)/libft/inc/												\
		  -I$(LIB_D)/get_next_line/inc/										\

# output format
CC_LOG=./.cc.log
CC_ERROR=./.cc.error

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

# warriors of choice
ECHO=printf
CAT=cat

# compiler and linker
CC = clang
LD = clang

# compile flags
CC_FLAGS = -Werror -Wextra -Wall
LD_FLAGS = $(CC_FLAGS)

# debugging or optimilization flags
CC_OPT_FLAGS = -O3													\
			   -march=native

ifeq ($(ASAN),1)
	CC_FLAGS += -fsanitize=address										\
				-fno-optimize-sibling-calls
	LD_FLAGS += -fsanitize=address										\
				 -fno-optimize-sibling-calls
	DEBUG = 1
endif

ifeq ($(DEBUG),1)
	CC_FLAGS += -g 														\
				-O0														\
				-fno-omit-frame-pointer									\
				-fstack-protector-all									\
				-DDEBUG
	LD_FLAGS += -g -O0 -DDEBUG
else
	CC_FLAGS += $(CC_OPT_FLAGS)
	LD_FLAGS += $(CC_OPT_FLAGS)
endif

# os variables
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    OS = LINUX
    CC_FLAGS += -D LINUX
    LD_FLAGS += -lXext -lX11 -lm
    MINILIBX = libmlx.a
    MINILIBX_D = minilibx_linux
endif
ifeq ($(UNAME_S),Darwin)
    OS = OSX
    CC_FLAGS += -D OSX
    LD_FLAGS += -framework AppKit -framework OpenGL
    MINILIBX = libmlx.dylib
    MINILIBX_D = minilibx_mac
endif

# regressive dependencies
LIB_INC += -I$(LIB_D)/$(MINILIBX_D)/

# make commands
all: $(NAME)

$(TEXT_D):
	@xz -d $(TEXT_D).tar.xz

$(TEXT_D).tar.xz:
	tar -cf - $(TEXT_D) | xz -9 -c - > $(TEXT_D).tar.xz 
	$(RM) -r $(TEXT_D)

submodule:
	@git submodule update --init --remote --recursive

$(NAME): $(GET_NEXT_LINE) $(LIBFT) $(LIBPRINTF) $(MINILIBX) $(OBJ_D) $(OBJ) $(INC_D) $(INC) $(TEXT_D)
	@$(ECHO) "Linking $(NAME)..."
	@$(CC) $(LD_FLAGS) -o $(NAME) $(OBJ) $(GET_NEXT_LINE) $(LIBPRINTF) $(LIBFT) $(MINILIBX)	\
	2>$(CC_LOG) || touch $(CC_ERROR)
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
	@$(CC) $(CC_FLAGS) -I$(INC_D) $(LIB_INC) -c $< -o $@ 2>$(CC_LOG) 	\
		|| touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then											\
		$(ECHO) "$(ERROR_STRING)\n" && $(CAT) $(CC_LOG);					\
	elif test -s $(CC_LOG); then											\
		$(ECHO) "$(WARN_STRING)\n" && $(CAT) $(CC_LOG);						\
	else																	\
		$(ECHO) "$(OK_STRING)\n";											\
	fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(GET_NEXT_LINE):
	@make -C $(LIB_D)/get_next_line

$(LIBPRINTF):
	@make -C $(LIB_D)/libprintf

$(LIBFT):
	@make -C $(LIB_D)/libft

$(MINILIBX):
	@make -C $(LIB_D)/$(MINILIBX_D)
	@ln -s $(LIB_D)/$(MINILIBX_D)/$(MINILIBX) ./

clean:
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_D)
	@make -C $(LIB_D)/get_next_line clean
	@make -C $(LIB_D)/libprintf clean
	@make -C $(LIB_D)/libft clean
	@make -C $(LIB_D)/$(MINILIBX_D) clean

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -r $(NAME).dSYM
	@$(RM) bonus
	@$(RM) ./screenshot.bmp
	@make -C $(LIB_D)/get_next_line fclean
	@make -C $(LIB_D)/libprintf fclean
	@make -C $(LIB_D)/libft fclean
	@make -C $(LIB_D)/$(MINILIBX_D)/ clean
	@$(RM) $(MINILIBX)

bonus: $(NAME)
	@touch bonus

lre:
	@$(RM) $(NAME)
	@$(RM) bonus
	@$(RM) -f $(OBJ)
	@$(RM) -r $(OBJ_D)
	@make

norm:
	@norminette $(LIB_D)/libprintf/src
	@norminette $(LIB_D)/libprintf/inc
	@norminette $(LIB_D)/get_next_line/src
	@norminette $(LIB_D)/get_next_line/inc
	@norminette $(LIB_D)/libft/src
	@norminette $(LIB_D)/libft/inc
	@norminette $(SRC) $(INC)

re: fclean all

.PHONY = all clean fclean re bonus
