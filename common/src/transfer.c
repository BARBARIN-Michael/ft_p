/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:11:40 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 16:17:53 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/socket.h>
#include "libft.h"
#include "tool.h"
#include "message.h"

#define PATH_MAX 4096

void				send_sock_to_fd_binary(int fd, int cli)
{
	unsigned long long	len;
	char				buf[PATH_MAX];
	int					ret;

	len = 0;
	while ((ret = recv(fd, buf, PATH_MAX - 1, 0)) > 0)
		len += write(cli, buf, ret);
	dprintf(1, "%sEcriture de %llu octet%s\n", C_MAGENTA, len, C_NONE);
}

void				send_fd_to_sock_binary(int fd, int cli)
{
	unsigned long long	len;
	char				buf[PATH_MAX];
	int					ret;

	len = 0;
	while ((ret = read(fd, buf, PATH_MAX - 1)) > 0)
		len += send(cli, buf, ret, 0);
	dprintf(1, "%sEcriture de %llu octet%s\n", C_MAGENTA, len, C_NONE);
}

void				send_sock_to_fd_crlf(int fd, int cli,
											char *oldcrlf, char *newcrlf)
{
	unsigned long long	len;
	char				buf[PATH_MAX];
	char				*eof;
	char				*wr;
	int					ret;

	len = 0;
	while ((ret = recv(fd, buf, PATH_MAX - 1, 0)) > 0)
	{
		wr = &buf[0];
		while ((eof = (char *)ft_memstrstr(wr, oldcrlf, &buf[ret] - wr)))
		{
			len += write(cli, wr, eof - wr);
			len += write(cli, newcrlf, ft_strlen(newcrlf));
			wr = &eof[ft_strlen(oldcrlf)];
		}
		if (wr < &buf[ret])
			len += write(cli, wr, &buf[ret] - wr);
	}
	dprintf(1, "%sEcriture de %llu octet%s\n", C_MAGENTA, len, C_NONE);
}

void				send_fd_to_sock_crlf(int fd, int cli,
											char *oldcrlf, char *newcrlf)
{
	char				buf[PATH_MAX];
	char				buf_tmp[PATH_MAX];
	char				*eof;
	char				*wr;
	int					ret;

	while ((ret = read(fd, buf, PATH_MAX - 1)) > 0)
	{
		wr = &buf[0];
		while ((eof = (char *)ft_memstrstr(wr, oldcrlf, &buf[ret] - wr)))
		{
			ft_memcpy(buf_tmp, wr, eof - wr);
			ft_memcpy(&buf_tmp[eof - wr], newcrlf, ft_strlen(newcrlf));
			send(cli, buf_tmp, eof - wr + ft_strlen(newcrlf), 0);
			wr = &eof[ft_strlen(oldcrlf)];
		}
		if (wr < &buf[ret])
			send(cli, wr, &buf[ret] - wr, 0);
	}
}
