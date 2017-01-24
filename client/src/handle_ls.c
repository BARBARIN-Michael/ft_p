/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 13:40:02 by barbare           #+#    #+#             */
/*   Updated: 2017/01/24 13:51:15 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_stream.h"
#include "config.h"
#include "read.h"
#include "client.h"
#include <stdio.h>
#include <sys/wait.h>

t_cli		handle_ls(t_cli cli, t_env env, char *cmd)
{
	char			buf[PATH_MAX];
	int				id;

	buf[0] = '\0';
	if (!(cli = cli.fct_connect(cli, env, NULL)).istransferable)
		return (cli);
	send_request("LIST", cmd, cli.sock.pi.fdin);
	cli.sock.pi = ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
	id = getheader(buf);
	if (protocol(buf) && (id == 125 || id == 150))
	{
		cli.sock.dtp = set_dtp_stdout(cli, env);
		if ((fork() == 0))
		{
			cli.sock.dtp = ft_stream_read_full(cli.sock.dtp, 0 | F_MOVE);
			exit(0);
		}
		wait(NULL);
		cli.sock.pi = ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
		is_success(protocol(buf));
		close(cli.sock.dtp.fdin);
	}
	else
		is_success(FALSE);
	return (cli);
}
