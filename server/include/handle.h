/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:12:20 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 12:28:47 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_H
# define HANDLE_H

#define PATH_MAX        4096

#include "config.h"

typedef struct      s_cli           t_cli;

struct      s_cli
{
    int                 fd;
	int					type_transfer;
	int					fd_transfer;
    char                user[PATH_MAX];
    char                *path_server;
    char                pass[PATH_MAX];
    char                home[PATH_MAX];
    char                auth[PATH_MAX];
	int					isconnected;
	int					istransferable;
	t_env				env;
};


typedef t_cli           (*t_fct_cmd)(t_env env, t_cli cli, char *str);

void                    init_id(unsigned long id_cmd[]);

void                    init_fct(t_fct_cmd *cmd);
void                    handle_cli(t_env env, t_cli cli);
t_cli                   handle_cmd(t_env env, t_cli cli, char *str);
t_cli                   handle_syst(t_env env, t_cli cli, char *param);
t_cli                   handle_ls(t_env env, t_cli cli, char *param);
t_cli                   handle_pwd(t_env env, t_cli cli, char *param);
t_cli                   handle_quit(t_env env, t_cli cli, char *param);
t_cli                   handle_cd(t_env env, t_cli cli, char *param);
t_cli                   handle_user(t_env env, t_cli cli, char *param);
t_cli                   handle_pass(t_env env, t_cli cli, char *param);
t_cli                   handle_get(t_env env, t_cli cli, char *param);
t_cli					handle_type(t_env env, t_cli cli, char *param);
t_cli					handle_port(t_env env, t_cli cli, char *str);
t_cli					handle_pasv(t_env env, t_cli cli, char *str);

unsigned long           getcommand(char *str);


#endif
