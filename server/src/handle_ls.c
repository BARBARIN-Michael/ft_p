/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 18:51:13 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 16:22:38 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "config.h"
#include "error.h"
#include "message.h"
#include "handle.h"
#include "tool.h"
#include "server.h"

static int                parse_args(char **args)
{
	unsigned int        i;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] != '-')
		{
			if (access(args[i], 0 | F_OK) != 0)
				return (ERROR);
			else if (access(args[i], 0 | F_OK | R_OK) != 0 ||
					lvl_dir(args[i]) < 0)
				return (ERROR);
		}
	}
	return (0);
}

void                fork_ls(t_cli cli, t_env env, char **args)
{
    int         ret;
	int			pid[2];

	pipe(pid);
    if ((ret = fork()) == 0)
    {
        close(pid[0]);
        dup2(pid[1], STDOUT_FILENO);
        EXEC("/bin/ls", args);
        ft_putendl_fd("Fork error in function ls", STDERR_FILENO);
		E_MESSAGE(451, cli.fd);
    }
    if (ret == ERROR)
        E_MESSAGE(425, cli.fd)
	else
	{
		close(pid[1]);
		transfer_crlf(pid[0], env.dtp_fd, "\n", "\r\n");
		wait(NULL);
    	S_MESSAGE(226, cli.fd)
	}
	free(args);
}

t_cli        handle_ls(t_env UNUSED(env), t_cli cli, char *str)
{
    int             nbargs;
    char            **args;
    char            path[PATH_MAX];

	ft_bzero(path, PATH_MAX);
	if (cli.isconnected == TRUE)
	{
		args = ft_nstrsplit2(str, ' ', ((nbargs = count_args(str, ' ')) + 2));
		args[0] = ft_strdup("/bin/ls");
    	if (nbargs >= 1)
    	{
    	    if (parse_args(&args[1]) != 0)
    	    {
    	        free(args);
    	        E_MESSAGE(501, cli.fd);
    	        return (cli);
    	    }
    	}
    	else
    	{
    	    getcwd(path, PATH_MAX);
    	    args[nbargs + 1] = path;
			args[nbargs + 2] = NULL;
    	}
        S_MESSAGE(150, cli.fd)
		cli.env = server_accept_dtp(cli.env);
    	fork_ls(cli, cli.env, args);
		free(args[0]);
	}
	else 
		E_MESSAGE(530, cli.fd);
	cli.env = server_close_dtp(cli.env);
    return (cli);
}
