# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbear <bbear@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/10 23:20:41 by sleonard          #+#    #+#              #
#    Updated: 2019/09/15 15:25:13 by bbear            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
# MAIN
# ============================================================================ #

MAIN_FILES =					\
	wolf3d.c					\

MAIN_DIR =						\
	$(SRC_DIR)/

MAIN_OBJ = $(addprefix $(OBJ_DIR), $(MAIN_FILES:.c=.o))

# ============================================================================ #
# UTILS
# ============================================================================ #

UTILS_FILES =					\
	binary_search.c				\
	error.c						\
	exit.c						\

UTILS_DIR =						\
	$(SRC_DIR)/utils/

UTILS_OBJ = $(addprefix $(OBJ_DIR), $(UTILS_FILES:.c=.o))

# ============================================================================ #
# TERMINAL
# ============================================================================ #

TERMINAL_FILES =				\
	term_actions.c				\
	term_actions2.c				\
	term_command_parser.c		\
	term_init.c					\
	term_processing.c			\
	term_render.c				\

TERMINAL_DIR =					\
	$(SRC_DIR)/terminal/

TERMINAL_OBJ = $(addprefix $(OBJ_DIR), $(TERMINAL_FILES:.c=.o))

# ============================================================================ #
# SDL_UTILS
# ============================================================================ #

SDL_UTILS_FILES =				\
	sdl_clean.c					\
	sdl_loop.c					\

SDL_UTILS_DIR =					\
	$(SRC_DIR)/SDL_utils/

SDL_UTILS_OBJ = $(addprefix $(OBJ_DIR), $(SDL_UTILS_FILES:.c=.o))

# ============================================================================ #
# RENDER
# ============================================================================ #

RENDER_FILES =					\
	bresenham.c					\
	minimap.c					\
	minimap_utils.c				\
	render.c					\
	render_utils.c				\
	sprite_getter.c				\
	texture_render_utils.c		\
	items.c                     \
	main_menu.c                 \
	controls_window.c           \
	map_choose_menu.c           \

RENDER_DIR =					\
	$(SRC_DIR)/render/

RENDER_OBJ = $(addprefix $(OBJ_DIR), $(RENDER_FILES:.c=.o))

# ============================================================================ #
# PARSING
# ============================================================================ #

PARSING_FILES =					\
	fast_gnl.c					\
	image_parser.c				\
	map_parser.c				\
	parsing_utils.c				\
	sprites_parser.c			\
	texture_parser.c			\
	texture_parsing_utils.c		\
	texture_table_parser.c		\

PARSING_DIR =						\
	$(SRC_DIR)/parsing/

PARSING_OBJ = $(addprefix $(OBJ_DIR), $(PARSING_FILES:.c=.o))

# ============================================================================ #
# INIT
# ============================================================================ #

INIT_FILES =					\
	init.c						\
	parse_params.c				\
	sdl_init.c					\

INIT_DIR =						\
	$(SRC_DIR)/init/

INIT_OBJ = $(addprefix $(OBJ_DIR), $(INIT_FILES:.c=.o))

# ============================================================================ #
# HOOKS
# ============================================================================ #

HOOKS_FILES =					\
	key_hook.c					\
	mouse_hook.c				\
	player_look.c				\
	player_moves.c				\
	menu_interactions.c         \

HOOKS_DIR =						\
	$(SRC_DIR)/hooks/

HOOKS_OBJ = $(addprefix $(OBJ_DIR), $(HOOKS_FILES:.c=.o))

# ============================================================================ #
# GAME_LOGIC
# ============================================================================ #

GAME_LOGIC_FILES =				\
	game_logic_utils.c			\
	parse_items.c				\
	player_actions.c			\

GAME_LOGIC_DIR =				\
	$(SRC_DIR)/game_logic/

GAME_LOGIC_OBJ = $(addprefix $(OBJ_DIR), $(GAME_LOGIC_FILES:.c=.o))

# ============================================================================ #
# BUILD WOLF3D
# ============================================================================ #

NAME =							\
	wolf3d

OBJ =							\
	$(MAIN_OBJ)					\
	$(GAME_LOGIC_OBJ)			\
	$(HOOKS_OBJ)				\
	$(INIT_OBJ)					\
	$(PARSING_OBJ)				\
	$(RENDER_OBJ)				\
	$(SDL_UTILS_OBJ)			\
	$(TERMINAL_OBJ)				\
	$(UTILS_OBJ)				\

LIBFT =							\
	./libft/libft.a

FT_PRINTF = 					\
	./libft/ft_printf/

OBJ_DIR =						\
	./temp/

SRC_DIR =						\
	./sources

COMP_FLAGS = 					\
	-Wall -Wextra -Werror -O2 -g

INCLUDES = 						\
    	./includes/

SDL = ./SDL2_libs

SDL2 = $(SDL)/SDL2
SDL2_LIBS = $(SDL2)/lib
SDL2_INCL = $(SDL2)/include

TTF = $(SDL)/SDL_ttf
TTF_LIBS = $(TTF)/lib
TTF_INCL = $(TTF)/include

FREETYPE = $(SDL)/freetype-2.4.9
FREETYPE_LIBS = $(FREETYPE)/lib
FREETYPE_INCL = $(FREETYPE)/include

COMPILE = gcc $(COMP_FLAGS) -I $(INCLUDES) -I $(LIBFT_INC) -I $(SDL2_INCL) -I $(TTF_INCL)

LIBS =																\
	-L $(LIBFT_DIR) -lft -L $(FT_PRINTF) -lftprintf					\
	-L $(SDL2_LIBS) -lSDL2 -L $(TTF_LIBS) -lSDL2_ttf				\

all : $(NAME)

.PHONY: configure
configure:
	./run.sh

$(NAME) : configure $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(COMPILE) $(LIBS) $(OBJ) -o $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(MAIN_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(UTILS_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(TERMINAL_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(SDL_UTILS_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(RENDER_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(PARSING_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(INIT_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(HOOKS_DIR)%.c
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)%.o : $(GAME_LOGIC_DIR)%.c
	$(COMPILE) -c $< -o $@

.PHONY: clean
clean :
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

.PHONY: fclean
fclean : clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)

.PHONY: bclean
bclean :
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR)

re : fclean $(NAME)

# ============================================================================ #
# 						LIBFT
# ============================================================================ #

LIBFT_DIR =				\
	./libft/			\

LIBFT_INC = 			\
	./libft/includes/	\

$(LIBFT) :
	make -C $(LIBFT_DIR)
	make printf -C $(LIBFT_DIR)