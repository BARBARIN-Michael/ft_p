/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user_password.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 14:22:56 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 14:16:37 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_stream.h"
#include "config.h"
#include "read.h"
#include "client.h"

t_cli            handle_user(t_cli cli, t_env UNUSED(env), char *cmd)
{
	char			buf[PATH_MAX];
	int				id;
	int				err;

	buf[0] = '\0';
	send_request("USER", cmd, cli.sock.pi.fdin);
	cli.sock.pi = ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
	id = getheader(buf);
	if ((err = protocol(buf)) == TRUE &&
			(id == 230 || id == 331 || id == 332))
		is_success(TRUE);
	else
		is_success(FALSE);
	return (cli);
}

t_cli			handle_pass(t_cli cli, t_env UNUSED(env), char *cmd)
{
	char			buf[PATH_MAX];
	int				id;
	int				err;

	buf[0] = '\0';
	send_request("PASS", cmd, cli.sock.pi.fdin);
	cli.sock.pi = ft_stream_get_protocol(cli.sock.pi, buf, PATH_MAX, PROT);
	id = getheader(buf);
	if ((err = protocol(buf)) == TRUE &&
			(id == 230 || id == 202))
		is_success(TRUE);
	else
		is_success(FALSE);
	return (cli);
}
