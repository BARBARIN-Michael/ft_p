/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:58:05 by barbare           #+#    #+#             */
/*   Updated: 2016/12/28 15:58:27 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "config.h"

static void            usage(char *title)
{
    dprintf(1, "Usage %s [server address] [port]\n", title);
}

int             main(int ac, char **av)
{
    t_env env;

    if (ac < 3)
        usage(av[0]);
    env.addr = av[1];
    env.port = ft_atoi(av[2]);
    initsocket(env);
}
