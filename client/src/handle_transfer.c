/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_transfer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 18:54:33 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 16:12:44 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "libft.h"
#include "message.h"
#include "error.h"
#include "config.h"
#include "handle.h"
#include "client.h"
#include "read.h"
#include "tool.h"

static void		handle_get(t_env env, t_cli cli, char *cmd)
{
	char 	buf[PATH_MAX];
	int		id;

	send_request("RETR", cmd, cli.sock.pi.fdin);
	cli.sock.pi = ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
	id = getheader(buf);
	if (protocol(buf) && (id == 125 || id == 150))
	{
		cli.sock.dtp = set_dtp_receive_file(cli, env, cmd);
		if (fork() == 0)
		{
			if (cli.type_transfer == ASCII)
			{
				dprintf(1, "transfer ascii\n");
				transfer_crlf(cli.sock.dtp.fdin, cli.sock.dtp.fdout, PROT, CRLF);
			}
			else if (cli.type_transfer== BINARY)
			{
				dprintf(1, "transfer bin\n");
				transfer_binary(cli.sock.dtp.fdin, cli.sock.dtp.fdout);
			}
			exit(0);
		}
		wait(NULL);
		cli.sock.pi = ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
		dprintf(1, "\nTest : %s\n", buf);
		is_success(protocol(buf));
		cli.sock.dtp = close_dtp_file(cli);
	}
	else
		is_success(FALSE);
}

static void		handle_put(t_env env, t_cli cli, char *cmd)
{
	(void)env, (void)cli, (void)cmd;
}

void		handle_transfer(t_cli cli, t_env env, char *cmd)
{
	if (ft_strncmp(cmd, "get", 3) == 0)
		handle_get(env, cli, &cmd[4]);
	else
		handle_put(env, cli, &cmd[4]);
}
