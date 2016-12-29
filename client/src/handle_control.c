/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 12:01:54 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 13:38:57 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "handle.h"
#include "config.h"

static char         **init_cmd_unix(char **cmd)
{
    cmd[0] = ft_strcpy(cmd[0], "ls");
    cmd[1] = ft_strcpy(cmd[1], "cd");
    cmd[2] = ft_strcpy(cmd[2], "get");
    cmd[3] = ft_strcpy(cmd[3], "put");
    cmd[4] = ft_strcpy(cmd[4], "pwd");
    cmd[5] = ft_strcpy(cmd[5], "quit");
    cmd[6] = ft_strcpy(cmd[6], "user");
    cmd[7] = ft_strcpy(cmd[7], "pass");
    cmd[8] = ft_strcpy(cmd[8], "syst");
    cmd[9][0] = '\0';
    return (cmd);
}

static char         **init_cmd_ftp(char **cmd)
{
    cmd[0] = ft_strcpy(cmd[0], "LIST");
    cmd[1] = ft_strcpy(cmd[1], "CWD");
    cmd[2] = ft_strcpy(cmd[2], "GET");
    cmd[3] = ft_strcpy(cmd[3], "PUT");
    cmd[4] = ft_strcpy(cmd[4], "PWD");
    cmd[5] = ft_strcpy(cmd[5], "QUIT");
    cmd[6] = ft_strcpy(cmd[6], "USER");
    cmd[7] = ft_strcpy(cmd[7], "PASS");
    cmd[8] = ft_strcpy(cmd[8], "SYST");
    cmd[9][0] = '\0';
    return (cmd);
}

static char         **init_cmd_ftp(t_fct_cmd *cmd)
{
    cmd[0] = &handle_ls;
    cmd[1] = &handle_cd;
    cmd[2] = &handle_get;
    cmd[3] = &handle_put;
    cmd[4] = &handle_pwd;
    cmd[5] = &handle_quit;
    cmd[6] = &handle_user;
    cmd[7] = &handle_pass;
    cmd[9][0] = '\0';
    return (cmd);
}

void                handle_control(char *cmd)
{
    static int          isInit = 0;
    static char         cmd_unix[5][MAX_CMD];
    static char         cmd_ftp[5][MAX_CMD];
    static t_fct_cmd    fct_ftp[5][MAX_CMD];

    if (isInit == 0)
    {
        cmd_unix = init_cmd_unix(cmd_unix);
        cmd_ftp = init_cmd_ftp(cmd_unix);
    }
}

