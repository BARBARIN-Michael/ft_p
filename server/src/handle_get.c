/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 16:56:25 by barbare           #+#    #+#             */
/*   Updated: 2017/01/24 15:47:17 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include "message.h"
#include "error.h"
#include "handle.h"
#include "tool.h"
#include "server.h"
#include "config.h"

static int		test_file(char *args, int fd)
{
	char		path[PATH_MAX];

	getcwd(path, PATH_MAX);
	ft_strcat(path, "/");
	ft_strcat(path, args);
	if (access(path, 0 | F_OK) != 0)
	{
		E_MESSAGE(501, fd);
		ft_putendl_fd(STR_BADPATH, STDERR_FILENO);
		return (ERR_BADPATH);
	}
	else if (access(path, 0 | F_OK | R_OK) != 0 ||
			lvl_dir(args) < 0)
	{
		E_MESSAGE(502, fd);
		ft_putendl_fd(STR_NOTACCESS, STDERR_FILENO);
		return (ERR_NOTACCESS);
	}
	return (0);
}

t_cli			handle_get(t_env env, t_cli cli, char *param)
{
	char	**args;
	int		fd;

	(void)env;
	args = ft_strsplit2(param, ' ');
	if ((cli.access & 0x10) != 0x10)
		E_MESSAGE(550, cli.fd);
	if (test_file(args[1], cli.fd) < 0)
		return (cli);
	S_MESSAGE(150, cli.fd);
	if (fork() == 0)
	{
		cli.env = server_accept_dtp(cli.env);
		fd = open(args[1], O_RDONLY);
		if (cli.type_transfer == BINARY)
			send_fd_to_sock_binary(fd, cli.env.dtp_fd);
		else if (cli.type_transfer == ASCII)
			send_fd_to_sock_crlf(fd, cli.env.dtp_fd, CRLF, PROT);
		S_MESSAGE(250, cli.fd);
		exit(0);
	}
	wait(NULL);
	return (cli);
}
