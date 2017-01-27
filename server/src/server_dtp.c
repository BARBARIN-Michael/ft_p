/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_dtp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:22:15 by barbare           #+#    #+#             */
/*   Updated: 2017/01/19 18:38:24 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <stdio.h>
#include "libft.h"
#include "server.h"
#include "config.h"
#include "handle.h"

t_env		server_accept_dtp(t_env env)
{
	socklen_t				len;

	len = sizeof(env.cli_addr);
	if (!(env.dtp_fd = accept(env.data_fd, (SOCKADDR*)&env.cli_addr, &len)))
		dprintf(STDERR_FILENO, "Accept KO\n");
	return (env);
}

t_env		server_close_dtp(t_env env)
{
	close(env.dtp_fd);
	return (env);
}
