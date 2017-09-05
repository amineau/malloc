# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amineau <amineau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/05 16:51:20 by amineau           #+#    #+#              #
#    Updated: 2017/09/05 17:09:14 by amineau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).so
LINK=libft_malloc.so
CC = gcc

SRCS = main.c free.c realloc.c show_alloc_mem.c utils.c

SPATH = srcs
OPATH = objs
HPATH = includes

CFLAGS = -I./$(HPATH) -Wall -Werror -Wextra

SRC = $(addprefix $(SPATH)/,$(SRCS))
OBJ = $(addprefix $(OPATH)/,$(SRCS:.c=.o))

WHITE	= \033[0m
DARK	= \033[1;30m
RED	= \033[1;31m
GREENB	= \033[1;32m
GREEN	= \033[0;32m
YELLOW	= \033[33m
CYAN	= \033[36m

all: $(OPATH) $(NAME)

$(NAME): $(OBJ)
	@printf "$(YELLOW)%-30s$(WHITE)" "Building $@"
	@ar rc $@ $^ && echo "$(GREENB)<<--$(WHITE)" \
	|| echo "$(RED)<<--$(WHITE)"
	@ranlib $@
	ln -s $(NAME) $(LINK)
$(OPATH):
	@printf "$(YELLOW)%-30s$(WHITE)" "Creating $@ directory"
	@mkdir -p $(OPATH)
	@echo "$(GREENB)<<--$(WHITE)"

$(OPATH)/%.o: $(SPATH)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< \
	&& printf "%-30s$(DARK)-->>\t$(GREEN)$@$(WHITE)\n" "$<" \
	|| (printf "%-30s$(DARK)-->>\t$(RED)$@$(WHITE)\n" "$<" \
	&& exit 1)

clean:
	@printf "$(YELLOW)%-30s$(WHITE)" "Deleting $(OPATH)"
	@rm -rf $(OPATH)
	@echo "$(GREENB)<<--$(WHITE)"

fclean: clean
	@printf "$(YELLOW)%-30s$(WHITE)" "Deleting $(NAME)"
	@rm -f $(NAME)
	@echo "$(GREENB)<<--$(WHITE)"
	@printf "$(YELLOW)%-30s$(WHITE)" "Deleting $(LINK)"
	@rm -f $(LINK)
	@echo "$(GREENB)<<--$(WHITE)"

re: fclean all
