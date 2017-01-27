/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 20:14:05 by barbare           #+#    #+#             */
/*   Updated: 2017/01/24 13:20:20 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include "handle.h"
#include "config.h"
#include "message.h"
#include "server.h"

char		*transform_home(char *home, char *pwd)
{
	int		i;

	i = 0;
	while (home[i] && home[i] == pwd[i])
		++i;
	if (pwd[i] == '\0')
		return ("/");
	return (&pwd[i]);
}

t_cli		handle_pwd(t_env env, t_cli cli, char *param)
{
	char		buf[PATH_MAX];

	(void)env;
	(void)param;
	buf[0] = '\0';
	getcwd(buf, PATH_MAX);
	dprintf(1, "pwd : %s\n", buf);
	S_MESSAGE(257, cli.fd, transform_home(cli.home, buf));
	return (cli);
}
