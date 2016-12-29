/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 19:14:19 by barbare           #+#    #+#             */
/*   Updated: 2016/12/28 14:26:15 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "error.h"
#include "message.h"
#include "handle.h"
#include "config.h"
#include "server.h"
#include "libft.h"


t_env           init(t_serv config)
{
    t_env   env;

    if ((env.proto = getprotobyname("tcp")) == NULL)
        exit(SOCKET_ERROR); //TODO
    if ((env.srv_fd = socket(PF_INET, SOCK_STREAM, env.proto->p_proto)) == ERROR)
    {
        ft_putendl_fd("Cannot open socket !", STDERR_FILENO);
        exit (SOCKET_ERROR);
    }
    ft_bzero(&env.srv_addr, sizeof(env.srv_addr));
    env.srv_addr.sin_family = AF_INET;
    env.srv_addr.sin_port = htons(config.port);
    env.srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((bind(env.srv_fd, (SOCKADDR *)&env.srv_addr,
                sizeof(SOCKADDR))) == ERROR)
    {
        ft_putendl_fd("Cannot bind socket !", STDERR_FILENO);
        exit (HOST_ERROR);
    }
    listen(env.srv_fd, config.backlog);
    return (env);
}

void            server(t_serv config, t_env env)
{
    env = init(config);
    env.isrun = TRUE;
    getcwd(config.path, PATH_MAX);
    if ((ft_strlen(config.path) + ft_strlen("/dir/")) > PATH_DIR_MAX)
        ft_putendl_fd("Size path to long", STDERR_FILENO);
    run(config, env);
}

//TODO setsocketattribute un truc dans le genre et regarde le reuse

void    run(t_serv config, t_env env)
{
    socklen_t   len;
    t_cli       cli;

    len = sizeof(SOCKADDR);
    cli = (t_cli){0};
    if ((cli.fd = accept(env.srv_fd, (SOCKADDR*)&env.cli_addr, &len)))
        if (fork() == 0)
        {
            S_MESSAGE(220, cli.fd);
            cli.auth = config.authorized;
            cli.path_global = config.path;
            chdir(config.path);
            handle_cli(cli);
        }
    run(config, env);
}

void    handle_cli(t_cli cli)
{
    char            str[PATH_MAX];
    int             i;
    char            **mess;
    int             ret;

    str[0] = '\0';
    ret = recv(cli.fd, str, PATH_MAX, 0);
    if (ret >= (PATH_MAX - 1) || ret == ERROR)
        E_MESSAGE(503, cli.fd)
    else if (str[0] != '\r' && str[0] != '\n' && str[0] != '\0')
    {
        str[ret - 1] = '\0';
        mess = ft_strsplit2(str, '\n');
        i = 0;
        while (mess[i])
        {
            dprintf(1, C_CYAN"Client %d : %sRSV CMD %s\n"C_NONE, cli.fd, C_BLUE,
                    mess[i]);
            cli = handle_cmd(cli, mess[i]);
            ++i;
            if (mess[i] == NULL)
            {
                free(mess);
                handle_cli(cli);
            }
        }
    }
}
