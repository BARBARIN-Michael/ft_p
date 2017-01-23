/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:53:19 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 15:27:45 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_stream.h"
#include "config.h"
#include "read.h"
#include "client.h"
#include <stdio.h>
#include <sys/wait.h>

t_cli            handle_type(t_cli cli, t_env UNUSED(env), char *cmd)
{
	char			buf[PATH_MAX];
	int				err;

	buf[0] = '\0';
	send_request("TYPE", cmd, cli.sock.pi.fdin);
	cli.sock.pi = ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
	err = protocol(buf);
	if (err)
	{
		if (cmd[0] == 'I')
			cli.type_transfer = BINARY;
		else
			cli.type_transfer = ASCII;
		dprintf(STDOUT, "%sSUCCESS !%s\n", C_GREEN, C_NONE);
	}
	return (cli);
}
