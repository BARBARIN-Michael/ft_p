/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 18:51:13 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 18:18:04 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "config.h"
#include "error.h"
#include "message.h"
#include "handle.h"
#include "tool.h"

#ifndef PATH_MAX
    #define PATH_MAX        4096
#endif


const char          *error_ls(int error)
{
    static const char     *str_error[5] = {
        STR_UNKNOWERROR, STR_NOTACCESS, STR_BADPATH, STR_UNKNOWERROR
    };
    return (error < -3 ? str_error[3] : str_error[-error]);
}

static int                parse_args(t_cli cli, char **args)
{
    unsigned int        i;
    int                 ret;

    i = -1;
    while (args[++i])
        if (args[i][0] != '-')
        {
            if ((ret = access(args[1], 0 | F_OK)) != 0)
                return (ERROR);
            else if ((ret = access(args[1], 0 | F_OK | R_OK) != 0 ||
                lvl_dir(args[1])) < 0)
                return (ERROR);
        }
    return (0);
}

void                fork_ls(t_cli cli, char **args)
{
    int         ret;

    if ((ret = fork()) == 0)
    {
        dup2(cli.fd, STDOUT_FILENO);
        dup2(cli.fd, STDERR_FILENO);
        S_MESSAGE(150, cli.fd)
        write(cli.fd, CYAN, ft_strlen(CYAN));
        EXEC("/bin/ls", args);
        ft_putendl_fd(C_RED"Fork error in function ls", STDERR_FILENO);
    }
    if (ret == ERROR)
        E_MESSAGE(425, cli.fd)
    else
    {
        wait(NULL);
        S_MESSAGE(226, cli.fd)
        S_MESSAGE(250, cli.fd)
    }
}

t_cli        handle_ls(t_cli cli, char *str)
{
    int             nbargs;
    char            **args;
    char            path[PATH_MAX];

    args = ft_nstrsplit2(str, ' ', ((nbargs = count_args(str, ' ')) + 1));
    if (nbargs > 1)
    {
        if (parse_args(cli, &args[1]) != 0)
        {
            free(args);
            E_MESSAGE(501, cli.fd)
            return (cli);
        }
    }
    else
    {
        getcwd(path, PATH_MAX);
        args[nbargs] = path;
    }
    fork_ls(cli, args);
    free(args);
    return (cli);
}
