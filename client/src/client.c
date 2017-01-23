/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 14:53:44 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 15:19:40 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "libft.h"
#include "ft_stream.h"
#include "error.h"
#include "message.h"
#include "handle.h"
#include "config.h"
#include "client.h"

int            server_isOK(t_cli cli)
{
    char    buf[PATH_MAX];

    dprintf(STDOUT, C_BROWN"Waiting server response\n");
	cli.sock.pi = ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
    if (GET_RESPONSE(buf, 220) != 0)
    {
        FAILED("Could not connect to server !");
        return (FALSE);
    }
    dprintf(STDOUT, C_GREEN"%s\n", buf);
    return (TRUE);
}

t_env           init_client(t_cli cli, t_env env)
{
    ft_bzero(&env.cli_addr, sizeof(env.cli_addr));
    env.cli_addr.sin_family = AF_INET;
    env.cli_addr.sin_port = htons(cli.port);
    env.cli_addr.sin_addr = *(IN_ADDR *)env.host->h_addr;
    STATUS("Connecting to %s\n", cli.addr);
    if (connect(cli.sock.pi.fdin, (SOCKADDR*)&env.cli_addr, sizeof(SOCKADDR)) == ERROR)
    	SOCKET_ERRNO("Connect error %s!", cli.addr);
    return (env);
}

t_env           init_socket(t_cli cli, t_env env)
{
    int     fd;

    if ((env.proto = getprotobyname("tcp")) == NULL ||
            !(fd = socket(PF_INET, SOCK_STREAM, env.proto->p_proto)))
    {
        FAILED("Cannot open soint !");
        exit (SOCKET_ERROR);
    }
    STATUS("Resolving address of %s\n", cli.addr);
    if ((env.host = gethostbyname(cli.addr)) == NULL)
    {
        FAILED("Host %s not found !", cli.addr);
        exit (SOCKET_ERROR);
    }
	env.cli_fd = fd;
    return (env);
}

void            client(t_cli cli)
{
    t_env       env;

    env = init_socket(cli, env);
	cli.type_transfer = ASCII;
    cli.sock.pi = ft_stream_new(env.cli_fd, STDOUT_FILENO, STDERR_FILENO);
    env = init_client(cli, env);
    server_isOK(cli);
	cli.istransferable = FALSE;
    getcwd(cli.path, PATH_MAX);
    run(cli, env);
	if (cli.istransferable)
		free(cli.dtp_addr);
}

void    run(t_cli cli, t_env env)
{
    char            buff[PATH_MAX];
    int             ret;

    buff[0] = '\0';
	signal(SIGINT, handle_sig);
	if (singleton_sig(0) != 0)
		handle_quit(cli, env, NULL);
    dprintf(STDOUT_FILENO, "\n%sftp>%s ", C_BLUE, C_NONE);
    ret = read(STDIN_FILENO, buff, PATH_MAX);
    if (ret >= (PATH_MAX - 1) || ret == ERROR)
    {
        FAILED("Error command, max lengh %d!\n", PATH_MAX - 1)
    }
    else if (!ft_isspace(buff[0]))
    {
        buff[ret] = '\0';
        cli = handle_cmd(cli, env, buff);
    }
    run(cli, env);
}

