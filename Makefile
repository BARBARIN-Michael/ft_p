# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/07 16:55:33 by mbarbari          #+#    #+#              #
#    Updated: 2016/04/07 17:21:38 by mbarbari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = FT_P
CC=clang

LIB_PATH ?= libs/

MLX_PROJECT ?= no

CFLAGS += -Wall -Wextra -Werror


# ##############################################################################
# File C

SRCS =	src/main.c 												\
		src/ft_env.c

# ##############################################################################
# File H

INC_FILES = include/ft_env.h

# ##############################################################################
# ##############################################################################

LIB_PATH = ./Libs/

STREAM_PATH = $(LIB_PATH)/libftstream/
PRINTF_PATH = $(LIB_PATH)/libftprintf/
LIBFT_PATH = $(LIB_PATH)/libft/

C_INCLUDE_PATH += $(STREAM_PATH)/include $(LIBFT_PATH)/include $(PRINTF_PATH)/include/ include/ 

CFLAGS += $(foreach d, $(C_INCLUDE_PATH), -I$d)

OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))

CP = cp

RM = rm -f

LDFLAGS += -L$(STREAM_PATH) -lftstream -L$(PRINTF_PATH) -lftprintf -L$(LIBFT_PATH) -lft

all: $(NAME)

MKDIR ?= mkdir -p

obj/%.o: src/%.c $(INC_FILES)
	$(MKDIR) -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(LIBFT_PATH)/libftstream.a:
	$(MAKE) -C $(STREAM_PATH)

$(LIBFT_PATH)/libftprintf.a:
	$(MAKE) -C $(PRINTF_PATH)

$(LIBFT_PATH)/libft.a:
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(DIR_LIB)/libftprintf/libftprintf.a $(DIR_LIB)/libftstream/libftstream.a $(LIBFT_PATH)/libft.a $(OBJS)
	$(CC) -O3 -o $@ $(OBJS) $(LDFLAGS)


clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(STREAM_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(PRINTF_PATH) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(STREAM_PATH) fclean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(PRINTF_PATH) fclean

re: fclean all

.PHONY: all clean fclean re $(LIBFT_PATH)/libft.a $(PRINTF_PATH)/libftprintf.a $(MLX_PATH)/libmlx.a
