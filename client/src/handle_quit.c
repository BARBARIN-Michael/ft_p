/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 12:45:18 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 13:54:23 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_stream.h"
#include "config.h"
#include "read.h"
#include "client.h"

int				singleton_sig(int quit)
{
	static int		isquit = 0;

	if (quit != 0)
		isquit = quit;
	return (isquit);
}

void			handle_sig(int sig)
{
	singleton_sig(sig);
}

t_cli			handle_quit(t_cli cli, t_env env, char cmd)
{
	(void)env;
	(void)cmd;
	send_request("QUIT", NULL, cli.sock.pi.fdin);
	exit(0);
	return (cli);
}
