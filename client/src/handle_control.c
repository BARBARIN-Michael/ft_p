/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 12:01:54 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 16:32:20 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_stream.h"
#include "tool.h"
#include "handle.h"
#include "config.h"
#include "read.h"

t_cli					handle_help(t_cli cli, t_env env, char *cmd)
{
	(void)cli;
	(void)env;
	(void)cmd;
	dprintf(1, "\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", "ls", "cd", "pwd",
			"quit",	"user", "pass", "pasv", "type",	"help");
	return (cli);
}

static void                 init_cmd_unix(char **cmd)
{
    cmd[0] = "ls";
    cmd[1] = "cd";
    cmd[2] = "pwd";
    cmd[3] = "quit";
    cmd[4] = "user";
    cmd[5] = "pass";
    cmd[6] = "pasv";
    cmd[7] = "type";
	cmd[8] = "help";
    cmd[9] = (void*)0;
}

static void                 init_fct_ftp(t_fct_cmd *cmd)
{
    cmd[0] = &handle_ls;
    cmd[1] = &handle_cd;
    cmd[2] = &handle_pwd;
    cmd[3] = &handle_quit;
    cmd[4] = &handle_user;
    cmd[5] = &handle_pass;
    cmd[6] = &handle_pasv;
    cmd[7] = &handle_type;
    cmd[8] = &handle_help;
    cmd[9] = (void*)0;
}

t_cli                handle_control(t_cli cli, t_env env, char *cmd)
{
    static int          isInit = 0;
    static char         *cmd_unix[MAX_CMD];
    static t_fct_cmd    fct_ftp[MAX_CMD];
	char				*args;
    unsigned int        i;

    i = 0;
	args = ft_strchr(cmd, ' ');
	if (isInit == 0)
	{
		init_cmd_unix(cmd_unix);
		init_fct_ftp(fct_ftp);
		isInit = 1;
	}
	while (cmd_unix[i] && djb2(cmd_unix[i], ft_strlen(cmd_unix[i])) != djb2(cmd, ft_strlen(cmd_unix[i])))
		++i;
	if (cmd_unix[i] != NULL && fct_ftp[i] != NULL)
		return (fct_ftp[i](cli, env,
					(args != NULL && args[0] != '\0' ? &args[1] : NULL)));
	return (cli);
}

