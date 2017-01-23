/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 11:56:53 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 16:30:29 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_H
# define HANDLE_H

#include "config.h"
#include "ft_stream.h"

#define MAX_CMD 20

typedef t_cli           (*t_fct_cmd)(t_cli cli, t_env env, char *cmd);
t_cli                   handle_cmd(t_cli cli, t_env env, char *cmd);
void					handle_sig(int sig);
int						singleton_sig(int quit);

void					handle_transfer(t_cli cli, t_env env, char *cmd);
t_cli                   handle_control(t_cli cli, t_env env, char *cmd);

t_cli					handle_ls(t_cli cli, t_env env, char *cmd);
t_cli                   handle_cd(t_cli cli, t_env env, char *cmd);
t_cli                   handle_pwd(t_cli cli, t_env env, char *cmd);
t_cli                   handle_quit(t_cli cli, t_env env, char *cmd);
t_cli					handle_user(t_cli cli, t_env env, char *cmd);
t_cli					handle_pass(t_cli cli, t_env env, char *cmd);
t_cli					handle_pasv(t_cli cli, t_env env, char *cmd);
t_cli					handle_type(t_cli cli, t_env env, char *cmd);
t_cli					handle_help(t_cli cli, t_env env, char *cmd);

#endif
