/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:48:12 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 20:50:37 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "config.h"
#include "error.h"
#include "message.h"
#include "handle.h"
#include "tool.h"
#include "server.h"


t_cli		handle_type(t_env UNUSED(env), t_cli cli, char *str)
{
	char	**args;
	
	args = ft_strsplit2(str, ' ');
	if (ft_toupper(args[1][0]) == 'A' || ft_toupper(args[1][0] == 'I'))
	{
		cli.type_transfer = ft_toupper(args[1][0]);
		S_MESSAGE(200, cli.fd);
	}
	else
		E_MESSAGE(504, cli.fd)
	free(args);
	return (cli);
}

t_cli		handle_port(t_env UNUSED(env), t_cli cli, char *UNUSED(str))
{
	E_MESSAGE(500, cli.fd)
	return (cli);
}

t_cli		handle_pasv(t_env UNUSED(env), t_cli cli, char *UNUSED(str))
{
	struct sockaddr_in6	sin;
	socklen_t			addrLength;
	unsigned short		port;
	char				inet[12];

	port = 0;
	if (cli.istransferable)
		close(cli.env.data_fd);
	cli.env.data_fd = init_sock(cli.env);
	cli.env = bind_sock(cli.env, &cli.env.data_fd, &port);
	addrLength = sizeof(sin);
	getsockname(cli.fd, (struct sockaddr*)&sin, &addrLength);
	ft_bzero(inet, 12);
	inet[10] = 0xFF;
	inet[11] = 0xFF;
	if (ft_memcmp(inet, sin.sin6_addr.s6_addr, 12) == 0)
	{
		S_MESSAGE(227, cli.fd, sin.sin6_addr.s6_addr[12],
			sin.sin6_addr.s6_addr[13], sin.sin6_addr.s6_addr[14],
			sin.sin6_addr.s6_addr[15], (port >> 8) & 0xFF, port & 0xFF);
		cli.istransferable = TRUE;
	}
	else
		E_MESSAGE(503, cli.fd);
	return (cli);
}

t_cli		handle_epsv(t_env UNUSED(env), t_cli cli, char *UNUSED(str))
{
	struct sockaddr_in6	localAddr;
	socklen_t			addrLength;
	unsigned short		port;

	port = 0;
	if (cli.istransferable)
		close(cli.env.data_fd);
	cli.env.data_fd = init_sock(cli.env);
	cli.env = bind_sock(cli.env, &cli.env.data_fd, &port);
	addrLength = sizeof(localAddr);
	getsockname(cli.fd, (struct sockaddr*)&localAddr,
			&addrLength);
	S_MESSAGE(229, cli.fd, port);
	cli.istransferable = TRUE;
	return (cli);
}
