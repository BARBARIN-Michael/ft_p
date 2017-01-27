/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:12:20 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 15:20:56 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOL_H
# define TOOL_H

unsigned long   djb2(const char *str, unsigned int size);
int             lvl_dir(char *dir);
unsigned int    count_args(char *args, int c);
void			send_sock_to_fd_crlf(int fd, int cli, char *o, char *n);
void			send_fd_to_sock_crlf(int fd, int cli, char *o, char *n);
void			send_sock_to_fd_binary(int fd, int cli);
void			send_fd_to_sock_binary(int fd, int cli);
void            print_time(char *color);

#endif
