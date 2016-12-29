/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 14:53:44 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 19:04:41 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "error.h"
#include "message.h"
#include "handle.h"
#include "config.h"
#include "libft.h"

int            server_isOK(t_env env)
{
    char    path[PATH_MAX];
    int     ret;

    dprintf(STDIN_FILENO, "Waiting server response\n");
    ret = read(env.cli_fd, path, PATH_MAX);
    path[ret - 1] = '\0';
    if (GET_RESPONSE(path, 220) != 0)
    {
        FAILED("Could not connect to server !");
        return (FALSE);
    }
    ft_putendl_fd(path, STDIN_FILENO);
    return (TRUE);
}

t_env           init(t_cli cli, t_env env)
{
    if ((env.proto = getprotobyname("tcp")) == NULL ||
    (env.cli_fd = socket(PF_INET, SOCK_STREAM, env.proto->p_proto)) == ERROR)
    {
        FAILED("Cannot open socket !");
        exit (SOCKET_ERROR);
    }
    ft_bzero(&env.cli_addr, sizeof(env.cli_addr));
    STATUS("Resolving address of %s\n", cli.addr);
    if ((env.host = gethostbyname(cli.addr)) == NULL)
    {
        FAILED("Host %s not found !", cli.addr);
        exit (SOCKET_ERROR);
    }
    env.cli_addr.sin_family = AF_INET;
    env.cli_addr.sin_port = htons(cli.port);
    env.cli_addr.sin_addr = *(IN_ADDR *)env.host->h_addr;
    STATUS("Connecting to %s\n", env.host->h_addr);
    if (connect(env.cli_fd, (SOCKADDR*)&env.cli_addr, sizeof(SOCKADDR)) == ERROR)
    {
        FAILED("Connect error %s!", cli.addr);
        exit (SOCKET_ERROR);
    }
    return (env);
}

void            server(t_cli cli, t_env env)
{
    env = init(cli, env);
    server_isOK(env);
    env.isrun = TRUE;
    getcwd(cli.path, PATH_MAX);
    run(cli, env);
}

void    run(t_cli cli, t_env env)
{
    char            buff[PATH_MAX];
    int             ret;

    dprintf(STDIN_FILENO, C_BLUE"\nftp> ");
    ret = read(STDIN_FILENO, buff, PATH_MAX);
    if (ret >= (PATH_MAX - 1) || ret == ERROR)
    {
        FAILED("Error command, max lengh %d!\n", PATH_MAX - 1);
    }
    else if (!ft_isspace(buff[0]))
    {
        buff[ret - 1] = '\0';
        cli = handle_cmd(cli, env, buff);
    }
    run(cli, env);
}

