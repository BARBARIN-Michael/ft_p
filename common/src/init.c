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
#include "error.h"
#include "message.h"
#include "config.h"
#include "libft.h"

t_env           initsocket_server(t_env env, t_config config)
{
    if ((env.proto = getprotobyname("tcp")) == NULL)
    {
        ft_putendl_fd("Cannot open socket !", STDERR_FILENO);
        exit (SOCKET_ERROR);
    }
    ft_bzero(&env.srv_addr, sizeof(env.srv_addr));
    env.srv_addr.sin_family = AF_INET;
    env.srv_addr.sin_port = htons(config.port);
    env.srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((bind(env.srv_fd, (struct sockaddr *)&env.srv_addr,
                sizeof(struct sockaddr_in))) == ERROR)
    {
        ft_putendl_fd("Cannot bind socket !", STDERR_FILENO);
        exit (HOST_ERROR);
    }
    listen(env.srv_fd, config.backlog);
    return (env);
}

void            init(t_config conf, t_env env)
{
    env = initsocket(conf);
    env.isrun = TRUE;
    getcwd(conf.path, PATH_MAX);
    if ((ft_strlen(conf.path) + ft_strlen("/dir/")) > PATH_DIR_MAX)
        ft_putendl_fd("Size path to long", STDERR_FILENO);
    run(conf, env);
}
