# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/10 23:20:41 by sleonard          #+#    #+#              #
#    Updated: 2019/07/14 16:03:28 by rearming         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
# MAIN
# ============================================================================ #

MAIN_FILES =					\
	wolf3d.c					\

MAIN_DIR =						\
	$(SRC_DIR)

MAIN_OBJ = $(addprefix $(OBJ_DIR), $(MAIN_FILES:.c=.o))

# ============================================================================ #
# BUILD FRACTOL
# ============================================================================ #

NAME =							\
	wolf3d

OBJ =							\
	$(MAIN_OBJ)					\

LIBFT =							\
	./libft/libft.a

FT_PRINTF = 					\
	./libft/ft_printf/

OBJ_DIR =						\
	./temp/

SRC_DIR =						\
	./sources/

COMP_FLAGS = 					\
	-Wall -Wextra -Werror -O2

INCLUDES = 						\
	./includes/

COMP = gcc $(COMP_FLAGS) -I $(INCLUDES) -I $(LIBFT_INC) -I $(SDL_INCL)

SDL_INCL = ./SDL2/includes/

SDL_LIB = ./SDL2/lib/

LIBS = -L $(LIBFT_DIR) -lft -L $(FT_PRINTF) -lftprintf -L $(SDL_LIB) -lSDL2

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(COMP) $(LIBS) $(OBJ) -o $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(MAIN_DIR)%.c
	$(COMP) -c $< -o $@

clean :
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re : fclean $(NAME)

# ============================================================================ #
# 						LIBFT
# ============================================================================ #

LIBFT_DIR =				\
	./libft/			\

LIBFT_INC = 			\
	./libft/includes/	\

$(LIBFT) :
	@make -C $(LIBFT_DIR)
	@make printf -C $(LIBFT_DIR)