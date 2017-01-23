/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:22:58 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 14:17:18 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_stream.h"
#include "config.h"
#include "read.h"

t_cli            handle_cd(t_cli cli, char *cmd)
{
	char			buf[PATH_MAX];
	int				err;

	buf[0] = '\0';
	send_request("CWD", cmd, cli.sock.pi.fdin);
	ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
	err = protocol(buf);
	if (err)
		dprintf(STDOUT, "%sSUCCESS !%s\n", C_GREEN, C_NONE);
	return (cli);
}
