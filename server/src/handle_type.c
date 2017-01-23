/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:48:12 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 12:43:45 by barbare          ###   ########.fr       */
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
	struct sockaddr_in	localAddr;
	socklen_t			addrLength;
	char				**args;
	unsigned short		port;

	port = 0;
	if (cli.istransferable)
		close(cli.env.data_fd);
	cli.env.data_fd = init_sock(cli.env);
	cli.env = bind_sock(cli.env, &cli.env.data_fd, &port);
	addrLength = sizeof(localAddr);
	getsockname(cli.fd, (struct sockaddr*)&localAddr,
			&addrLength);
	args = ft_strsplit2(inet_ntoa(localAddr.sin_addr), '.');
	S_MESSAGE(227, cli.fd, args[0], args[1], args[2], args[3],
			(port >> 8) & 0xff, port & 0xff);
	cli.istransferable = TRUE;
	return (cli);
}
