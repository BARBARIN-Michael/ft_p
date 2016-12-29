/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:50:33 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 19:07:39 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"
#include "config.h"
#include "libft.h"
#include "handle.h"

static unsigned long       getcommand(char *str)
{
    unsigned int    i;
    char            command[20];

    i = 0;
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '\r' && str[i] != '\n')
    {
        command[i] = ft_toupper(str[i]);
        ++i;
    }
    command[i] = '\0';
    return (djb2(command, i));
}

t_cli                       handle_cmd(t_cli cli, t_env env, char *cmd)
{
    unsigned long   hash;

    hash = getcommand(cmd);
    if (hash == djb2("GET", 3) || hash == djb2("PUT", 3))
        return (cli);
        //handle_transfer(cmd);
    else
        handle_control(cmd, env.cli_fd);
    return (cli);
}
