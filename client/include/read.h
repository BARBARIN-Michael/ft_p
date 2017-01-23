/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:44:59 by barbare           #+#    #+#             */
/*   Updated: 2017/01/19 15:39:37 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

int			getheader(char *str);
int         read_by_command(char *str);
int			protocol(char *str);
void		send_request(const char *cmd, char *args, int fd);
void		is_success(int isok);

#endif
