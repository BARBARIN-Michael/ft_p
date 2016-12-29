# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/07 16:55:33 by mbarbari          #+#    #+#              #
#    Updated: 2016/12/29 18:33:27 by barbare          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= gcc
CX ?= clang++
CFLAGS += -g -Wall -Wextra -Werror -I../common/libs/libft/Include/ -I./include -I../common/include -lcrypt
LIBS =  -I../common/libs/libft/Include/ -L../common/libs/libft/ -lft

CLI_SRCS = 	src/client.c \
    		src/handle_cmd.c \
    		src/handle_control.c \
    		src/handle_ls.c \
    		src/main.c \
			../common/src/tool.c

CLI_OBJS = $(patsubst src/%.c,obj/%.o,$(CLI_SRCS))

SRC_INCLUDE = include/*.h

RM ?= rm -f
MKDIR ?= mkdir

all: cli

print-% : ; $(info $* is $(flavor $*) variable set to [$($*)]) @true

cli: $(CLI_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

obj/%.o: src/%.c $(SRC_INCLUDE)
	$(MKDIR) -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(CLI_OBJS)

fclean: clean
	$(RM) $(CLI_OBJS)

re: fclean all

.PHONY: clean fclean re all
