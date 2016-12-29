/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:47:05 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 18:20:40 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "handle.h"
#include "config.h"
#include "error.h"
#include "message.h"
#include "tool.h"

static int         test_dir(t_cli cli, char *dir)
{
    int     ret;

    if ((ret = access(dir, F_OK)) != 0)
        E_MESSAGE(501, cli.fd)
    else if ((ret = access(dir, F_OK | R_OK)) != 0 || lvl_dir(dir) < 0)
        E_MESSAGE(501, cli.fd)
    if (ret != 0)
        return (ERROR);
    return (0);
}

t_cli         handle_cd(t_cli cli, char *param)
{
    char        **args;
    char        dir[PATH_MAX];

    args = ft_strsplit2(param, ' ');
    getcwd(dir, PATH_MAX);
    ft_strcat(dir, "/");
    ft_strcat(dir, args[1]);
    if (test_dir(cli, dir) != ERROR)
    {
        if (chdir(dir) != ERROR)
            S_MESSAGE(250, cli.fd)
        else
            E_MESSAGE(421, cli.fd)
    }
    return (cli);
}
