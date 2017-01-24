/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 12:20:05 by barbare           #+#    #+#             */
/*   Updated: 2017/01/20 18:17:41 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "config.h"

void			server(t_env env);
void			run(t_env env);
t_env			init(t_serv conf);
t_env			bind_sock(t_env env, int *fd, unsigned short *port);
t_env			server_accept_dtp(t_env env);
t_env			server_close_dtp(t_env env);
int				init_sock(t_env env);

#endif
