/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_local.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 19:11:23 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 20:26:26 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_stream.h"
#include "config.h"
#include "read.h"
#include "client.h"
#include <stdio.h>
#include <sys/wait.h>

extern char **environ;

t_cli            handle_lls(t_cli cli, t_env UNUSED(env), char *cmd)
{
	char		**cmd_args;
	char		newcmd[PATH_MAX];

	if (ft_strchr(cmd, '\n'))
		ft_strchr(cmd, '\n')[0] = '\0';
	ft_strcpy(newcmd, "/bin/ls ");
	ft_strcat(newcmd, cmd && cmd[0] != '\0' ? cmd : "");
	cmd_args = ft_strsplit2(newcmd, ' ');
	if (fork() == 0)
		execve("/bin/ls", cmd_args, environ);
	wait(NULL);
	free(cmd_args);
	return (cli);
}


t_cli            handle_lpwd(t_cli cli, t_env UNUSED(env), char *cmd)
{
	char		path[PATH_MAX];

	(void)cmd;
	getcwd(path, PATH_MAX);
	dprintf(1, "%s", path);
	return (cli);
}

t_cli            handle_lcd(t_cli cli, t_env UNUSED(env), char *cmd)
{
	char		path[PATH_MAX];

	if (ft_strchr(cmd, '\n'))
		ft_strchr(cmd, '\n')[0] = '\0';
	if (cmd)
	{
		getcwd(path, PATH_MAX);
		ft_strcat(path, "/");
		ft_strcat(path, cmd);
		if (chdir(path) == -1)
			dprintf(STDERR_FILENO, "Cannot find repertory %s!\n", path);
	}
	return (cli);
}
