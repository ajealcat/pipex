# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 14:57:32 by ajearuth          #+#    #+#              #
#    Updated: 2021/12/20 14:42:50 by ajearuth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN = pipex

SRCS = main.c pipex.c
SRCSD = srcs/
BONUS_SRCS = main_bonus.c pipex_bonus.c pipex_utils_bonus.c
BONUSD = bonus/
BONUSOD = $(BONUSD)objsb/
OBJSD = objs/
LIBFT_PATH = libft/
LIBFT_SRCS = ft_strlen.c ft_putstr_fd.c ft_split.c ft_strjoin.c ft_substr.c ft_strdup.c \
	    ft_strncmp.c
LIBFT_OBJS = $(addprefix $(OBJSD), $(LIBFT_SRCS:.c=.o))
OBJS = $(addprefix $(OBJSD), $(SRCS:.c=.o))
OBJSBONUS = $(addprefix $(BONUSOD), $(BONUS_SRCS:.c=.o))
CC = gcc -c -o
COMPIL = gcc -o
FLAGS = -Wall -Wextra -Werror

$(BIN):	$(OBJS) $(LIBFT_OBJS)
	$(COMPIL) $@ $(OBJS) $(LIBFT_OBJS)
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
	mkdir -p $(OBJSD)
	$(CC) $@ $< $(FLAGS)

all: $(BIN)

bonus: $(OBJSBONUS) $(LIBFT_OBJS)
	$(COMPIL) $(BIN)_bonus $(OBJSBONUS) $(LIBFT_OBJS)

$(BONUSOD)%.o: $(BONUSD)%.c
	mkdir -p $(BONUSOD)
	$(CC) $@ $< $(FLAGS)

clean:
	rm -rf $(OBJSD) $(BONUSOD)

fclean:	clean
	rm -rf $(BIN) $(BIN)_bonus

re: fclean all 

.PHONY: all clean fclean re

