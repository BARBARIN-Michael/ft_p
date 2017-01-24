#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Make                                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 14:48:04 by mbarbari          #+#    #+#              #
#    Updated: 2017/01/03 16:38:22 by barbare          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
EXE = a.out

OBJDIR = ./obj

LIBS = -L../libft/ -lft 
INC =  -I ../libft/include/
CFLAGS += -g -O0 -Wall -Wextra -Werror -I ./include/ $(INC)

SRCS =	src/ft_printf.c \
		src/ft_setup.c \
		src/handle_flag_f.c \
		src/handle_flag_s.c \
		src/handle_format.c \
		src/handle_modifier.c \
		src/ft_integer.c \
		src/ft_pointer.c \
		src/ft_string.c \
		src/ft_hexa.c \
		src/ft_printf_replace.c \
		src/ft_make_format.c \
		src/ft_make_format2.c

LIBFT_PATH ?= ../libft

OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))

CP = cp

RM = rm -f

all: $(NAME)

$(OBJS): | obj

obj:
	mkdir -p $@

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(NAME): $(LIBFT_PATH)/libft.a $(OBJS) 
	$(CP) $(LIBFT_PATH)/libft.a $(NAME)
	$(AR) -rcs $(NAME) $^

$(LIBFT_PATH)/libft.a:
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re $(LIBFT_PATH)/libft.a
