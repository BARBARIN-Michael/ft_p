/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:50:33 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 14:06:13 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tool.h"
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
        handle_transfer(cli, env, cmd);
    else
        cli = handle_control(cli, env, cmd);
    return (cli);
}
