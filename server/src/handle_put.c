/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:07:02 by barbare           #+#    #+#             */
/*   Updated: 2017/01/24 16:15:17 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include "message.h"
#include "config.h"
#include "error.h"
#include "handle.h"
#include "tool.h"
#include "server.h"

t_cli         handle_put(t_env UNUSED(env), t_cli cli, char *param)
{
    char	**args;
	int		fd;

	args = ft_strsplit2(param, ' ');
	fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	S_MESSAGE(150, cli.fd);
	if (fd != -1 && fork() == 0)
	{
		cli.env = server_accept_dtp(cli.env);
		if (cli.type_transfer == BINARY)
			transfer_binary(cli.env.dtp_fd, fd);
		else if (cli.type_transfer == ASCII)
			transfer_crlf(cli.env.dtp_fd, fd, "\r\n", CRLF);
		S_MESSAGE(250, cli.fd);
		exit(0);
	}
	wait(NULL);
    return (cli);
}
