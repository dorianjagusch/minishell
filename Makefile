# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#              #
#    Updated: 2023/04/04 10:30:46 by asarikha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = minishell


# Libft
LIBFT_PATH	= ./libft/
LIBFT_NAME	= Libft.a
LIBFT		= -L ./libft -lft

# Includes
INCLUDE = -I ./includes/\
				-I ./libft/\

# MinishellSources				
SRC_PATH	= src/
SRC = main.c
SRCS		= $(addprefix $(SRC_PATH),$(SRC))	
			
# Objects
OBJ_PATH	= obj/
OBJ = $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

READLINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include


.PHONY: all  clean fclean re

all: $(NAME)

print:
	@echo $(SRCS)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
	@mkdir $(OBJ_PATH)/ft_printf

$(OBJS): $(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ_PATH) $(OBJS)
	@echo "Making libft"
	@make -C $(LIBFT_PATH)
	@echo "Compiling minishell"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME) $(INCLUDE)
	@echo "minishell ready."

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH)
	@echo "Objects removed"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)
	@echo "executable removed"

.PHONY: re
re: fclean all