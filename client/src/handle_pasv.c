/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pasv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 12:58:44 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 21:02:17 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_stream.h"
#include "config.h"
#include "read.h"
#include "client.h"

t_cli			handle_pasv(t_cli cli, t_env env, char *cmd)
{
	char			buf[PATH_MAX];
	char			*str;
	char			**args;
	char			addr[PATH_MAX];

	(void)env;
	buf[0] = '\0';
	send_request("PASV", cmd, cli.sock.pi.fdin);
	cli.sock.pi = ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
	is_success((protocol(buf)));
	if (getheader(buf) != 227)
		return (cli);
	str = &ft_strchr(buf, '(')[1];
	ft_strchr(str, ')')[0] = '\0';
	args = ft_strsplit2(str, ',');
	snprintf(addr, PATH_MAX, "%s.%s.%s.%s", args[0], args[1], args[2], args[3]);
	cli.dtp_addr = ft_strdup(addr);
	cli.dtp_port = (ft_atoi(args[4]) << 8) + ft_atoi(args[5]);
	cli.istransferable = TRUE;
	return (cli);
}

t_cli			handle_epsv(t_cli cli, t_env env, char *cmd)
{
	char			buf[PATH_MAX];
	char			*str;

	(void)env;
	buf[0] = '\0';
	send_request("EPSV", cmd, cli.sock.pi.fdin);
	cli.sock.pi = ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
	is_success((protocol(buf)));
	if (getheader(buf) != 229)
		return (cli);
	str = &ft_strchr(buf, '(')[4];
	ft_strchr(str, '|')[0] = '\0';
	cli.dtp_addr = cli.addr;
	cli.dtp_port = ft_atoi(str);
	cli.istransferable = TRUE;
	return (cli);
}
