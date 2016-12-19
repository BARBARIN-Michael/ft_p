/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 09:55:16 by barbare           #+#    #+#             */
/*   Updated: 2016/12/19 17:55:04 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <libft.h>
#include "config.h"

static int  test_nb_args(int ac, char *cmd_line)
{
    if (ac < 3)
    {
        ft_putstr("usage ");
        ft_putstr(cmd_line);
        ft_putendl(" [ip : string] [port : integer]");
        return (TRUE);
    }
    else
        return (FALSE);
}

int         main(int ac, char **av)
{
    t_servconfig    config;

    if (test_nb_args(ac, av[0]) == FALSE)
        return (-1);
    config = configure_server(&av[1]);
    (void)config;
    return (0);
}
