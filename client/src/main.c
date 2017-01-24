/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:58:05 by barbare           #+#    #+#             */
/*   Updated: 2017/01/03 12:46:39 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "config.h"

static void		usage(char *title)
{
	dprintf(1, "Usage %s [server address] [port]\n", title);
}

int				main(int ac, char **av, char **envp)
{
	t_cli		cli;

	if (ac < 3)
		usage(av[0]);
	else
	{
		cli.addr = av[1];
		cli.port = ft_atoi(av[2]);
		cli.env = envp;
		client(cli);
	}
	return (0);
}
