/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:47:05 by barbare           #+#    #+#             */
/*   Updated: 2017/01/19 16:08:25 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "handle.h"
#include "config.h"
#include "error.h"
#include "message.h"
#include "tool.h"

static int		test_dir(t_cli cli, char *dir)
{
	if (access(dir, F_OK) != 0)
	{
		E_MESSAGE(501, cli.fd);
		return (ERROR);
	}
	else if (access(dir, 0 | F_OK | R_OK) != 0 ||
			lvl_dir(dir) < lvl_dir(cli.home))
	{
		E_MESSAGE(501, cli.fd);
		return (ERROR);
	}
	return (0);
}

t_cli			handle_cd(t_env env, t_cli cli, char *param)
{
	char		**args;
	char		olddir[PATH_MAX];
	char		dir[PATH_MAX];

	(void)env;
	dir[0] = '\0';
	args = ft_strsplit2(param, ' ');
	getcwd(olddir, PATH_MAX);
	snprintf(dir, PATH_MAX, "%s/%s/", olddir, args[1]);
	chdir(dir);
	getcwd(dir, PATH_MAX);
	dprintf(1, "On cd sur %s\n", dir);
	if (test_dir(cli, dir) != ERROR)
	{
		S_MESSAGE(250, cli.fd);
	}
	else
		chdir(olddir);
	return (cli);
}
