/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 13:40:02 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 18:29:23 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "config.h"

static void        read_server(void)
{
    char        buff[PATH_MAX];
    char        *response;
    int         loop;

    buff[0] = '\0';
    loop = 0;
    while (ret = read(fd, buff, PATH_MAX))
    {
        buff[ret - 1] = '\0';
        if (ft_isdigit(buff[0]) || (response = ft_strstr(buff, "\r\n") != NULL))
        {
            if (response)
            {
                response[0] = '\0';
                dprintf(1, buff);
                RESPONSE(&response[2]);
            }
            RESPONSE(buff);
            break ;
        }
        dprintf(1, buff);
    }
}

void        handle_ls(char *cmd, int fd)
{
    int         i;
    char        **args;
    char        buff[PATH_MAX];

    i = -1;
    while (cmd[++i] != ' ' || cmd[i] != ''\0')
        buff[i] = cmd[i];
    buff[i] = '\0';
    ft_strcat(buff, &cmd[i]);
    ft_strcat(buff, "\r\n");
    ft_putstr_fd(buff, fd);
    read_server(void);
}
