/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 14:53:44 by barbare           #+#    #+#             */
/*   Updated: 2017/01/24 14:33:20 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <arpa/inet.h>
#include "libft.h"
#include "ft_stream.h"
#include "error.h"
#include "message.h"
#include "handle.h"
#include "config.h"
#include "client.h"

int           init_socket(char *addr)
{
    int				fd;
	struct protoent *proto;
	struct hostent	*host;


    if ((proto = getprotobyname("tcp")) == NULL)
    	SOCKET_ERRNO("Error tcp %s!", addr);
	if (!(host = gethostbyname2(addr, AF_INET))
			&& !(host = gethostbyname2(addr, AF_INET6)))
    	SOCKET_ERRNO("Host %s not found init_sock !", addr);
	if (!(fd = socket(host->h_addrtype, SOCK_STREAM, proto->p_proto)))
    	SOCKET_ERRNO("Connect error socket %s!", addr);
	return (fd);
}

int		connect_socket(char *addr, int port, int fd)
{
	t_sockaddr					sin;
	struct hostent				*host;
	int							len;

	if (!(host = gethostbyname2(addr, AF_INET))
			&& !(host = gethostbyname2(addr, AF_INET6)))
    	SOCKET_ERRNO("Host %s not found connect_sock !", addr);
	ft_bzero(&sin, sizeof(sin));
	if (host->h_addrtype == AF_INET6)
	{
		sin.sa6.sin6_family = host->h_addrtype;
		inet_pton(AF_INET6, addr, &(sin.sa6.sin6_addr));
		sin.sa6.sin6_port = htons(port);
		len = sizeof(sin.sa6);
	}
	else
	{
		sin.sa4.sin_family = host->h_addrtype;
		inet_pton(AF_INET, addr, &(sin.sa4.sin_addr));
		sin.sa4.sin_port = htons(port);
		len = sizeof(sin.sa4);
	}
    if (connect(fd, (struct sockaddr *)&sin.sa, len) == -1)
    	SOCKET_ERRNO("Error connect %s!", addr);
	return (fd);
}

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

void            client(t_cli cli)
{
    t_env				env;
	struct hostent		*host;

	if (!(host = gethostbyname2(cli.addr, AF_INET))
			&& !(host = gethostbyname2(cli.addr, AF_INET6)))
    	SOCKET_ERRNO("Host %s not found client!", cli.addr);
    env.cli_fd = init_socket(cli.addr);
	STATUS("Resolving address of %s\n", cli.addr);
    env.cli_fd = connect_socket(cli.addr, cli.port, env.cli_fd);
    STATUS("Connecting to %s\n", cli.addr);
	cli.type_transfer = ASCII;
    cli.sock.pi = ft_stream_new(env.cli_fd, STDOUT_FILENO, STDERR_FILENO);
    server_isOK(cli);
	cli.istransferable = FALSE;
    getcwd(cli.path, PATH_MAX);
	if (host->h_addrtype == AF_INET)
		cli.fct_connect = &handle_pasv;
	else
		cli.fct_connect = &handle_epsv;
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

