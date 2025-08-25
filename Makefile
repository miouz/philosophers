# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhou <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 17:54:02 by mzhou             #+#    #+#              #
#    Updated: 2025/04/10 10:18:54 by mzhou            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---variables✍️

MAKE_CMD ?= $(MAKE)
CC = cc
CFLAGS = -Wall -Wextra -Werror -lpthread
DEBUG_FLAGS = -g3 -fsanitize=thread

#program variables
NAME = philosophers

#include variables
INCLUDE_DIR = includes/

#srcs variables
SRCS_MANDATORY = srcs/main.c \
				 srcs/parse.c \
				 srcs/utils.c \
				 srcs/init.c \
				 srcs/routine.c \
				 srcs/routine_eat.c \
				 srcs/routine_utils.c


#color variables
GREEN = \033[32m
RESET = \033[0m


#---targets and rules🫡$(NAME): $(OBJS)

#defaut target
all: $(NAME)

$(NAME): $(OBJS_MANDATORY)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -I $(INCLUDE_DIR) $(SRCS_MANDATORY) -o $(NAME)
	@echo "$(GREEN)Woah the mandatory is build(ﾉ◕ヮ◕)ﾉ$(RESET)"

#---clean🍻
.PHONY: clean fclean re bonus debug all

debug:fclean
	$(MAKE) MAKE_CMD="make debug"

clean:
	rm -f $(OBJS_MANDATORY)
	@echo "🧹$(GREEN)It was a good moment with you my .o friends, but i cleaned you upm(｡≧ｴ≦｡)m$(RESET)🧹🧹"
fclean: clean
	rm -f $(NAME)
	@echo "🧹🧹$(GREEN)everything has gone with fclean ლ(◉◞౪◟◉ )ლ$(RESET)🧹🧹"
re: fclean
	$(MAKE)
