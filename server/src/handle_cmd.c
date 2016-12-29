/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 17:52:18 by barbare           #+#    #+#             */
/*   Updated: 2016/12/28 14:46:45 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "handle.h"
#include "error.h"
#include "message.h"
#include "tool.h"

void            init_id(unsigned long id_cmd[])
{
    id_cmd[0] = djb2("LIST", 4);
    id_cmd[1] = djb2("CWD", 4);
    id_cmd[2] = djb2("GET", 3);
    id_cmd[3] = djb2("PUT", 3);
    id_cmd[4] = djb2("PWD", 3);
    id_cmd[5] = djb2("QUIT", 4);
    id_cmd[6] = djb2("USER", 4);
    id_cmd[7] = djb2("PASS", 8);
    id_cmd[8] = djb2("SYST", 4);
    id_cmd[9] = 0;
}

void            init_fct(t_fct_cmd *cmd)
{
    cmd[0] = &handle_ls;
    cmd[1] = &handle_cd;
    cmd[6] = &handle_user;
    cmd[7] = &handle_pass;
    cmd[8] = &handle_syst;
}

unsigned long    getcommand(char *str)
{
    unsigned int    i;

    i = 0;
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '\r' && str[i] != '\n')
        ++i;
    return (djb2(str, i));
}

t_cli    handle_cmd(t_cli cli, char *str)
{
    static unsigned long        id_cmd[20];
    static t_fct_cmd            fct_cmd[20] = { (void *)0 };
    static int                  isInit = 0;
    unsigned int                i;

    if (isInit == 0)
    {
        init_id(id_cmd);
        init_fct(fct_cmd);
        isInit++;
    }
    i = 0;
    while (id_cmd[i] != 0 && i < 19)
    {
        if (getcommand(str) == id_cmd[i])
            return (fct_cmd[i](cli, str));
        ++i;
    }
    E_MESSAGE(502, cli.fd)
    return (cli);
}
