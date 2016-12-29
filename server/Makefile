# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/07 16:55:33 by mbarbari          #+#    #+#              #
#    Updated: 2016/12/28 15:43:56 by barbare          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= gcc
CX ?= clang++
CFLAGS += -g -Wall -Wextra -Werror -I./include -I../common/include -I../common/libs/libft/Include -lcrypt
LIBS = -I../common/libs/libft/Include -L../common/libs/libft/ -lft

SRV_SRCS =  src/handle_cmd.c \
            src/handle_system.c \
            src/handle_ls.c \
            src/handle_cd.c \
            src/handle_get.c \
            src/handle_user_password.c \
            src/main.c \
            src/options_com.c \
            src/configure_server.c \
            ../common/src/tool.c \
            src/server.c

SRV_OBJS = $(patsubst src/%.c,obj/%.o,$(SRV_SRCS))

SRC_INCLUDE = include/*.h

RM ?= rm -f
MKDIR ?= mkdir

all: srv

srv: $(SRV_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

obj/%.o: src/%.c $(SRC_INCLUDE)
	$(MKDIR) -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

print-% : ; $(info $* is $(flavor $*) variable set to [$($*)]) @true

clean:
	$(RM) $(SRV_OBJS)

fclean: clean
	$(RM) $(SRV_OBJS)

re: fclean all

.PHONY: clean fclean re all ../common/libs/libft/libft.a ../common/libs/libft/libftstream.a
