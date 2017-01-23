/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 11:16:58 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 13:53:08 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_stream.h"
#include "config.h"
#include "read.h"
#include "client.h"

t_cli            handle_pwd(t_cli cli, t_env env, char *cmd)
{
	char			buf[PATH_MAX];

	buf[0] = '\0';
	send_request("PWD", cmd, cli.sock.pi.fdin);
	cli.sock.dtp = ft_stream_set_fdin(cli.sock.dtp, sock_data(cli, env));
	cli.sock.pi = ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
	is_success ((protocol(buf)));
	return (cli);
}
