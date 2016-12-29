/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 16:56:25 by barbare           #+#    #+#             */
/*   Updated: 2016/12/27 19:04:22 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "config.h"
#include "error.h"
#include "handle.h"

static int         test_file(char **args, int fd)
{
    (void)fd;
    if (access(args[1], 0 | F_OK) != 0)
    {
        ft_putendl_fd(STR_BADPATH, STDERR_FILENO);
        return (ERR_BADPATH);
    }
    return (0);
}

t_cli         handle_get(t_cli cli, char *param)
{
    char **args;

    args = ft_strsplit2(param, ' ');
    test_file(args, cli.fd);
    return (cli);
}
