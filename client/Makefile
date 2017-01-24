# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/07 16:55:33 by mbarbari          #+#    #+#              #
#    Updated: 2017/01/23 19:25:19 by barbare          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= gcc
CX ?= clang++
CFLAGS += -g -Wall -Wextra -Werror
INC = -I./include -I ../common/include -I../common/libs/libft/include -I../common/libs/libftstream/include
LIBS = -L../common/libs/libft/ -L../common/libs/libftstream/ -lft -lftstream

CLI_SRCS = 	src/client.c \
    		src/handle_cmd.c \
    		src/client_dtp.c \
    		src/handle_control.c \
    		src/handle_transfer.c \
    		src/handle_ls.c \
    		src/handle_cd.c \
    		src/handle_pwd.c \
    		src/handle_quit.c \
    		src/handle_type.c \
    		src/handle_pasv.c \
    		src/handle_local.c \
    		src/handle_user_password.c \
    		src/send.c \
    		src/main.c

COM_SRCS = ../common/src/tool.c \
		   ../common/src/transfer.c

CLI_OBJS = $(patsubst src/%.c,obj/%.o,$(CLI_SRCS))
COM_OBJS = $(patsubst ../common/src/%.c,../common/obj/%.o,$(COM_SRCS))

SRC_INCLUDE = include/*.h \
			  ../common/include/*.h

RM ?= rm -f
MKDIR ?= mkdir

all: cli

print-% : ; $(info $* is $(flavor $*) variable set to [$($*)]) @true

cli: $(COM_OBJS) $(CLI_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(INC) $(LIBS)

obj/%.o: src/%.c $(SRC_INCLUDE)
	$(MKDIR) -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

../common/obj/%.o: ../common/src/%.c $(SRC_INCLUDE)
	$(MKDIR) -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@ -I../common/include -I../common/libs/libft/include

clean:
	$(RM) $(CLI_OBJS)
	$(RM) $(COM_OBJS)

fclean: clean
	$(RM) cli
	$(RM) $(CLI_OBJS)
	$(RM) $(COM_OBJS)

re: fclean all

.PHONY: clean fclean re all
