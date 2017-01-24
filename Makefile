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


all: ftp

ftp:
	make -C ./common/libs/libft/
	make -C ./common/libs/libftstream/
	make -C ./client/
	make -C ./server/

clean:
	make -C ./client/ clean
	make -C ./server/ clean

fclean: clean
	make -C ./client/ fclean
	make -C ./server/ fclean

re: fclean all

.PHONY: clean fclean re all libft/libft.a libft/libftstream.a
