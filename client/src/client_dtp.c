/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_dtp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 09:40:52 by barbare           #+#    #+#             */
/*   Updated: 2017/01/25 14:25:28 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "config.h"
#include "libft.h"
#include "error.h"
#include "message.h"
#include "client.h"

int				sock_data(t_cli cli)
{
	int		fd;

	fd = init_socket(cli.dtp_addr);
	fd = connect_socket(cli.dtp_addr, cli.dtp_port, fd);
	return (fd);
}

t_stream		set_dtp_stdout(t_cli cli, t_env env)
{
	(void)env;
	cli.sock.dtp = ft_stream_set_fdin(cli.sock.dtp, sock_data(cli));
	cli.sock.dtp = ft_stream_set_fdout(cli.sock.dtp, STDOUT_FILENO);
	return (cli.sock.dtp);
}

t_stream		set_dtp_receive_file(t_cli cli, t_env env, char *file)
{
	char	buf[PATH_MAX];
	int		fd;

	(void)env;
	buf[0] = '\0';
	getcwd(buf, PATH_MAX);
	ft_strcat(buf, "/");
	ft_strcat(buf, file);
	fd = open(buf, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	cli.sock.dtp = ft_stream_set_fdin(cli.sock.dtp, sock_data(cli));
	cli.sock.dtp = ft_stream_set_fdout(cli.sock.dtp, fd);
	return (cli.sock.dtp);
}

t_stream		set_dtp_put_file(t_cli cli, t_env env, char *file)
{
	int		fd;

	(void)env;
	cli.sock.dtp = ft_stream_set_fdin(cli.sock.dtp, sock_data(cli));
	fd = open(file, O_RDONLY);
	cli.sock.dtp = ft_stream_set_fdin(cli.sock.dtp, fd);
	cli.sock.dtp = ft_stream_set_fdout(cli.sock.dtp, sock_data(cli));
	return (cli.sock.dtp);
}

t_stream		close_dtp_file(t_cli cli)
{
	close(cli.sock.dtp.fdin);
	close(cli.sock.dtp.fdout);
	return (cli.sock.dtp);
}
