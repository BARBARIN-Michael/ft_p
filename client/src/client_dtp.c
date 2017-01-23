/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_dtp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 09:40:52 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 21:10:15 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "error.h"
#include "message.h"
#include "client.h"

int		sock_data(t_cli cli, t_env env)
{
	int					fd;
    struct sockaddr_in6  sockaddr;
	struct hostent		*host;
	struct protoent		*proto;

	if ((proto = getprotobyname("tcp")) == NULL ||
			!(fd = socket(PF_INET6, SOCK_STREAM, env.proto->p_proto)))
	{
		FAILED("Cannot open socket !");
		exit (SOCKET_ERROR);
	}
	if (!(host = gethostbyname2(cli.dtp_addr, AF_INET)) &&
			!(host = gethostbyname2(cli.dtp_addr, AF_INET6)))
		SOCKET_ERRNO("Host name error!");
	if (!(fd = socket(PF_INET6, SOCK_STREAM, proto->p_proto)))
		SOCKET_ERRNO("Data Socket error!");
	ft_bzero(&sockaddr, sizeof(sockaddr));
    sockaddr.sin6_family = AF_INET6;
    sockaddr.sin6_port = htons(cli.dtp_port);
    ft_memcpy(&sockaddr.sin6_addr, host->h_addr, sizeof(sockaddr.sin6_addr));
	if (connect(fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == ERROR)
		SOCKET_ERRNO("Connect error data socket %s!", cli.addr);
	return (fd);
}

t_stream		set_dtp_stdout(t_cli cli, t_env env)
{
	cli.sock.dtp = ft_stream_set_fdin(cli.sock.dtp, sock_data(cli, env));
	cli.sock.dtp = ft_stream_set_fdout(cli.sock.dtp, STDOUT_FILENO);
	return (cli.sock.dtp);
}

t_stream		set_dtp_receive_file(t_cli cli, t_env env, char *file)
{
	char	buf[PATH_MAX];
	int		fd;

	buf[0] = '\0';
	getcwd(buf, PATH_MAX);
	ft_strcat(buf, "/");
	ft_strcat(buf, file);
	fd = open(buf, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	cli.sock.dtp = ft_stream_set_fdin(cli.sock.dtp, sock_data(cli, env));
	cli.sock.dtp = ft_stream_set_fdout(cli.sock.dtp, fd);
	return (cli.sock.dtp);
}

t_stream		set_dtp_put_file(t_cli cli, t_env env, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	cli.sock.dtp = ft_stream_set_fdin(cli.sock.dtp, fd);
	cli.sock.dtp = ft_stream_set_fdout(cli.sock.dtp, sock_data(cli, env));
	return (cli.sock.dtp);
}

t_stream		close_dtp_file(t_cli cli)
{
	close(cli.sock.dtp.fdin);
	close(cli.sock.dtp.fdout);
	return (cli.sock.dtp);
}
