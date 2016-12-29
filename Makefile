# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/07 16:55:33 by mbarbari          #+#    #+#              #
#    Updated: 2016/12/28 10:28:51 by barbare          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= gcc
CX ?= clang++
CFLAGS += -g -Wall -Wextra -Werror -Ilibs/libft/Include/ -Iserver/include -lcrypt

SRV_SRCS =  server/src/handle_cmd.c \
      		server/src/handle_system.c \
      		server/src/handle_ls.c \
      		server/src/handle_cd.c \
      		server/src/handle_get.c \
      		server/src/handle_user_password.c \
      		server/src/main.c \
      		server/src/options_com.c \
			server/src/configure_server.c \
			server/src/tool.c \
      		server/src/server.c

SRV_OBJS = $(patsubst server/src/%.c,server/obj/%.o,$(SRV_SRCS))

SRC_INCLUDE = server/include/options.h

CLI_SRCS = client/client.c

CLI_OBJS = $(patsubst client/src/%.c,client/obj/%.o,$(CLI_SRCS))

RM ?= rm -f
MKDIR ?= mkdir

all: srv cli

libs/libft/libft.a:
	$(MAKE) -C libs/libft/

libs/libft/libftstream.a:
	$(MAKE) -C libs/libftstream

srv: libs/libft/libft.a $(SRV_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -Llibs/libft/ -lft

cli: libs/libft/libft.a libs/libft/libftstream.a $(CLI_OBJS) $(COM_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -Llibs/libft/ -lft

server/obj/%.o: server/src/%.c $(SRC_INCLUDE)
	$(MKDIR) -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(MAKE) -C libs/libft/ clean
	$(MAKE) -C libs/libftstream/ clean
	$(RM) $(SRV_OBJS)
	$(RM) $(CLI_OBJS)

fclean: clean
	$(MAKE) -C libs/libft/ fclean
	$(MAKE) -C libs/libftstream/ fclean
	$(RM) $(SRV_OBJS)
	$(RM) $(CLI_OBJS)

re: fclean all

.PHONY: clean fclean re all libft/libft.a libft/libftstream.a
