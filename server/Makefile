# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/07 16:55:33 by mbarbari          #+#    #+#              #
#    Updated: 2017/01/23 15:12:57 by barbare          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= gcc
CX ?= clang++
CFLAGS += -g -Wall -Wextra -Werror
INC = -I./include -I ../common/include -I../common/libft/libft/include 
LIBS = -L../common/libft/libft/ -lft

SRV_SRCS =  src/handle_cmd.c \
            src/handle_system.c \
            src/handle_ls.c \
            src/handle_pwd.c \
            src/handle_cd.c \
            src/handle_get.c \
            src/handle_put.c \
            src/handle_quit.c \
            src/handle_type.c \
            src/handle_user_password.c \
            src/main.c \
            src/configure_server.c \
            src/server_dtp.c \
            src/server.c

COM_SRCS = ../common/src/tool.c \
		   ../common/src/transfer.c

SRV_OBJS = $(patsubst src/%.c,obj/%.o,$(SRV_SRCS))
COM_OBJS = $(patsubst ../common/src/%.c,../common/obj/%.o,$(COM_SRCS))

SRC_INCLUDE = include/*.h \
			  ../common/include/*.h

RM ?= rm -f
MKDIR ?= mkdir

all: srv

print-% : ; $(info $* is $(flavor $*) variable set to [$($*)]) @true

srv: $(COM_OBJS) $(SRV_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(INC) $(LIBS)

obj/%.o: src/%.c $(SRC_INCLUDE)
	$(MKDIR) -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

../common/obj/%.o: ../common/src/%.c $(SRC_INCLUDE)
	$(MKDIR) -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@ -I../common/include -I../common/libft/libft/include

clean:
	$(RM) $(SRV_OBJS)
	$(RM) $(COM_OBJS)

fclean: clean
	$(RM) ./srv
	$(RM) $(SRV_OBJS)
	$(RM) $(COM_OBJS)

re: fclean all

.PHONY: clean fclean re all ../common/libs/libft/libft.a ../common/libs/libft/libftstream.a
