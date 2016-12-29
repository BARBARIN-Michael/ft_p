/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user_password.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 17:58:59 by barbare           #+#    #+#             */
/*   Updated: 2016/12/28 14:52:12 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include <string.h>
#include "config.h"
#include "handle.h"
#include "message.h"
#include "error.h"

static t_cli    reset_user(t_cli cli)
{
    if (cli.user)
        free(cli.user);
    if (cli.path)
        free(cli.path);
    if (cli.pass)
        free(cli.pass);
    return (cli);
}

t_cli           get_user(t_cli cli, char **users, char *param)
{
    int             find;
    char            **params;
    char            **user;
    unsigned int    i;

    i = -1;
    find = FALSE;
    params = ft_strsplit2(param, ' ');
    cli = reset_user(cli);
    while (find == FALSE && users[++i] != NULL)
    {
        user = ft_strsplit2(users[i], ':');
        if (ft_strncmp(user[0], params[1], ft_strlen(user[0])) == 0)
        {
            cli.user = ft_strdup(user[0]);
            cli.pass = ft_strdup(user[1]);
            cli.path = ft_strdup(user[2]);
            if (cli.pass)
                S_MESSAGE(331, cli.fd)
            else
                S_MESSAGE(230, cli.fd)
            find = TRUE;
        }
        free(user);
    }
    if (!find)
        E_MESSAGE(530, cli.fd)
    free(params);
    return (cli);
}

t_cli           handle_pass(t_cli cli, char *param)
{
    char        **params;

    params = ft_strsplit2(param, ' ');
    dprintf(1, "Lecture du pass : %s et de la commande : %s\n", cli.pass,
            params[1]);
    if (params[2] != NULL)
        E_MESSAGE(501, cli.fd)
    else if (ft_strncmp(cli.pass, params[1], ft_strlen(cli.pass)) == 0)
        S_MESSAGE(230, cli.fd)
    else
        S_MESSAGE(530, cli.fd)
    return (cli);
}

t_cli           handle_user(t_cli cli, char *param)
{
    char        path[PATH_MAX];
    char        users[PATH_MAX];
    char        **args;
    int         ret;
    int         fd;

    path[0] = '\0';
    ft_strcat(path, cli.path_global);
    ft_strcat(path, cli.auth);
    if (access(path, F_OK) == ERROR)
        dprintf(STDERR_FILENO, "Cannot have permission for file  %s\n", path);
    else
    {
        fd = open(path, O_RDONLY);
        ret = read(fd, users, PATH_MAX);
        users[ret - 1] = '\0';
        args = ft_strsplit2(users, '\n');
        cli = get_user(cli, args, param);
        free(args);
        close(fd);
    }
    return (cli);
}
