/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 19:14:19 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 18:42:57 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "error.h"
#include "message.h"
#include "handle.h"
#include "config.h"
#include "server.h"
#include "libft.h"

#include <errno.h>

int			init_sock(t_env env)
{
	int opt;
	int len;
	int fd;

	opt = 1;
	len = sizeof(opt);
    if ((env.proto = getprotobyname("tcp")) == NULL)
        exit(SOCKET_ERROR);
    if (!(fd = socket(PF_INET6, SOCK_STREAM, env.proto->p_proto)))
		SOCKET_ERRNO("Cannot open socket !")
	else if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, len) < 0)
		SOCKET_ERRNO("setsockopt(SO_REUSEADDR) failed")
	return (fd);
}

t_env           init_sockcontrol(t_env env)
{
	env.control_fd = init_sock(env);
	env = bind_sock(env, &env.control_fd, &env.config.control_port);
	dprintf(STDOUT_FILENO, "Server launch correctly!\n");
    return (env);
}

t_env		bind_sock(t_env env, int *fd, unsigned short *port)
{
    struct sockaddr_in6  sin;
	socklen_t			len;


	errno = 0;
	len = sizeof(sin);
    ft_bzero(&sin, sizeof(sin));
    sin.sin6_family = AF_INET6;
    sin.sin6_port = htons(*port);
    sin.sin6_addr = in6addr_any;
    if ((bind(*fd, (struct sockaddr *)&sin, sizeof(sin))) == ERROR)
	{
		dprintf(1, "BIND : %s\n", strerror(errno));
        SOCKET_ERRNO("Port %d is already used!", *port);
		return (env);
	}
	getsockname(*fd, (SOCKADDR *)&sin, &len);
	*port = ntohs(sin.sin6_port);
    listen(*fd, env.config.backlog);
	return (env);
}

void            server(t_env env)
{
    env = init_sockcontrol(env);
    env.isrun = TRUE;
    getcwd(env.config.path, PATH_MAX);
    run(env);
}

void    run(t_env env)
{
    socklen_t   len;
    t_cli       cli;
	struct stat s;

	s = (struct stat){0};
    len = sizeof(SOCKADDR);
    cli = (t_cli){0};
	if ((cli.fd = accept(env.control_fd, (SOCKADDR*)&env.cli_addr, &len)))
		if (fork() == 0)
		{
			dprintf(STDOUT_FILENO, "Client Connected : %d\n", cli.fd);
			S_MESSAGE(220, cli.fd);
			cli.path_server = env.config.path;
			snprintf(cli.auth, PATH_MAX, "%s/%s",
					env.config.path, env.config.authorized);
			snprintf(cli.home, PATH_MAX, "/dir/anonymous");
			cli.istransferable = FALSE;
			cli.type_transfer = ASCII;
			if (stat(cli.home, &s) == -1)
				mkdir(cli.home, 0700);
			chdir(cli.home);
			cli.env = env;
			handle_cli(env, cli);
		}
	run(env);
}

void    handle_cli(t_env env, t_cli cli)
{
	char			path[PATH_MAX];
    char            *next;
    int             ret;

    path[0] = '\0';
    ret = recv(cli.fd, path, PATH_MAX, 0);
	if (ret >= (PATH_MAX - 1) || ret == ERROR)
		E_MESSAGE(503, cli.fd)
	else if (path[0] != '\r' && path[0] != '\n' && path[0] != '\0')
	{
		path[ret] = '\0';
		if ((next = ft_strstr(path, "\r\n")) != NULL)
			next[0] = '\0';
		dprintf(1, C_CYAN"Client %d : %s%s\n"C_NONE, cli.fd, C_BLUE, path);
		cli = handle_cmd(env, cli, path);
	}
	handle_cli(env, cli);
}
