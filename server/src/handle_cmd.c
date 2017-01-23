/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 17:52:18 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 18:50:03 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "handle.h"
#include "error.h"
#include "message.h"
#include "tool.h"

int				is_functionnal_fct(int fd, t_cli cli, int id)
{
	if (id < 9)
		return (TRUE);
	else if (!cli.isconnected)
	{
		E_MESSAGE(530, fd);
		return (FALSE);
	}
	else if (!cli.istransferable)
	{
		E_MESSAGE(425, fd);
		return (FALSE);
	}
	return (TRUE);
}

void            init_id(unsigned long id_cmd[])
{
    id_cmd[0]	= djb2("QUIT", 4);
    id_cmd[1] 	= djb2("USER", 4);
    id_cmd[2] 	= djb2("PASS", 4);
    id_cmd[3] 	= djb2("SYST", 4);
    id_cmd[4] 	= djb2("PWD", 3);
    id_cmd[5] 	= djb2("TYPE", 4);
    id_cmd[6] 	= djb2("PORT", 4);
    id_cmd[7] 	= djb2("PASV", 4);
    id_cmd[8] 	= djb2("EPSV", 4);
    id_cmd[9] 	= djb2("LIST", 4);
    id_cmd[10] 	= djb2("CWD", 3);
    id_cmd[11]	= djb2("RETR", 4);
    id_cmd[12] 	= djb2("PUT", 3);
    id_cmd[13] 	= 0;
}

void            init_fct(t_fct_cmd *cmd)
{
	cmd[0] = &handle_quit;
	cmd[1] = &handle_user;
	cmd[2] = &handle_pass;
	cmd[3] = &handle_syst;
	cmd[4] = &handle_pwd;
	cmd[5] = &handle_type;
	cmd[6] = &handle_port;
	cmd[7] = &handle_pasv;
	cmd[8] = &handle_epsv;
	cmd[9] = &handle_ls;
	cmd[10] = &handle_cd;
	cmd[11]	= &handle_get;
	cmd[12]	= &handle_get; //PUT
}

unsigned long    getcommand(char *str)
{
    unsigned int    i;

    i = 0;
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '\r' && str[i] != '\n')
        ++i;
    return (djb2(str, i));
}

t_cli    handle_cmd(t_env env, t_cli cli, char *str)
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
		{
			if (!is_functionnal_fct(cli.fd, cli, i))
					return (cli);
            return (fct_cmd[i](env, cli, str));
		}
        ++i;
    }
    E_MESSAGE(502, cli.fd)
    return (cli);
}
