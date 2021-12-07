# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 14:57:32 by ajearuth          #+#    #+#              #
#    Updated: 2021/12/07 14:45:09 by ajearuth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN = pipex

SRCS = main.c main_utils.c pipex.c 
SRCSD = srcs/
bonus =

OBJSD = objs/

LIBFT_PATH = libft/
LIBFT_SRCS = ft_strlen.c ft_putstr_fd.c 
LIBFT_OBJS = $(addprefix $(OBJSD), $(LIBFT_SRCS:.c=.o))
OBJS = $(addprefix $(OBJSD), $(SRCS:.c=.o))
OBJSBONUS = $(bonus:.c=.o)

CC = gcc -c -o
LINKER = gcc -o
FLAGS = -Wall -Wextra -Werror

$(BIN):	$(OBJS) $(LIBFT_OBJS)
	$(LINKER) $@ $(OBJS) $(LIBFT_OBJS)
	@echo "\033[0;32m\n          _         "
	@echo "   ______/ \-.   _  "
	@echo ".-/     (    o\_//    *~o~o~* MAKEFILE OK *~o~o~* "
	@echo " |  ___  \_/\---'   "
	@echo "  |_||  |_||        "
	@echo "\033[0;35m                     Bonne correction !"


$(OBJSD)%.o: $(SRCSD)%.c
	mkdir -p $(OBJSD)
	$(CC) $@ $< $(FLAGS) 

$(OBJSD)%.o: $(LIBFT_PATH)%.c
	$(CC) $@ $< $(FLAGS)

all: $(BIN)

clean:
	rm -rf $(OBJSD) $(OBJSBONUS)

fclean:	clean
	rm -rf $(BIN)

re: fclean all 

.PHONY: all clean fclean re

