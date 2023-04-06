# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 11:46:33 by djagusch          #+#    #+#              #
#    Updated: 2023/04/06 15:55:00 by djagusch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = cc
CFLAGS = -Wall -Werror -Wall -I$I

RM = /bin/rm -f
RMDIR = /bin/rmdir -p

LIBFT = libft/libft.a

S = src
O = obj
I = includes

FILES = main \
	env
#	builtin
#	pipex parse_input parse_command do_child utils
#	#ft_split2 ft_count_words

HEADER = libft.h minishell.h
HEADER := $(addprefix $I/,$(HEADER))

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name '$(FILE).c'))
OBJS = $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS = $(dir $(OBJS))

READLINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

NAME = minishell

### RULES ###
all: $(NAME)

print:
	@echo $(SRCS)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(READLINE) -Llibft -lft -o $(NAME)
	@echo "$(COLOUR_GREEN) $(NAME) created$(COLOUR_END)"

$O:
	@mkdir -p $@ $(O_DIRS)

$O/%.o: $S/%.c $(HEADER) | $O
	@$(CC) $(CFLAGS) -c $< -o $@

### LIBFT

libft: $(LIBFT)

$(LIBFT):
	@$(MAKE) -C libft
	@echo "$(COLOUR_GREEN) $(LIBFT) created$(COLOUR_END)"

### CLEANING

clean:
	@cd libft && $(MAKE) clean
	@echo "$(COLOUR_RED) $(LIBFT) removed$(COLOUR_END)"
	@$(RM) $(OBJS) $(B_OBJS)
	@if [ -d $O ]; then $(RM) -rf $(O_DIRS) $O; fi
	@if [ -d $(BO) ]; then $(RM) -rf $(BO_DIRS) $(BO); fi

fclean : clean
	@cd libft && $(MAKE) fclean
	@$(RM) $(NAME) pipex_bonus
	@echo "$(COLOUR_RED) $(NAME) (bonus) removed$(COLOUR_END)"

re: fclean $(NAME) bonus

.PHONY: all clean fclean re bonus
