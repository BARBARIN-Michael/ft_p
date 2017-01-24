/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:51:23 by barbare           #+#    #+#             */
/*   Updated: 2017/01/24 13:07:25 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "config.h"

void					handle_sig(int sig);
int						singleton_sig(int quit);

t_env					init(t_cli config, t_env env);
int						init_socket(char *addr);
int						connect_socket(char *add, int port, int fd);
void					server(t_cli config, t_env env);
void					run(t_cli cli, t_env env);

t_stream				set_dtp_stdout(t_cli cli, t_env env);
t_stream				set_dtp_receive_file(t_cli cli, t_env env, char *file);
t_stream				set_dtp_put_file(t_cli cli, t_env env, char *file);
t_stream				close_dtp_file(t_cli cli);
int						sock_data(t_cli cli);

#endif
