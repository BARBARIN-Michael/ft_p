/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer.c                                         :+:      :+:    :+:   */
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
#include "libft.h"
#include "tool.h"
#include "message.h"

#define PATH_MAX 4096

void				transfer_binary(int fd, int cli)
{
	char		buf[PATH_MAX];
	int			ret;

	if ((ret = read(fd, buf, PATH_MAX - 1)) <= 0)
		return ;
	buf[ret] = '\0';
	write(cli, buf, ret);
	transfer_binary(fd, cli);
}

void				transfer_crlf(int fd, int cli, char *oldcrlf, char *newcrlf)
{
	char		buf[PATH_MAX];
	char		*eof;
	char		*wr;
	int			ret;

	if ((ret = read(fd, buf, PATH_MAX - 1)) <= 0)
		return ;
	buf[ret] = '\0';
	wr = &buf[0];
	while ((eof = ft_strstr(wr, oldcrlf)))
	{
		eof[0] = '\0';
		dprintf(cli, "%s%s", wr, newcrlf);
		wr = &eof[ft_strlen(oldcrlf)];
	}
	if (wr[0] != '\0')
		dprintf(cli, "%s%s", wr, newcrlf);
	transfer_crlf(fd, cli, oldcrlf, newcrlf);
}
