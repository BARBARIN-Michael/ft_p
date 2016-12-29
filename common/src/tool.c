/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:33:22 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 18:26:47 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define "libft.h"
#define "tool.h"

unsigned long   hash(unsigned char *str)
{
    unsigned long hash;
    int c;

    hash = 5381;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return (hash);
}

int             lvl_dir(char *dir)
{
    int         lvl;
    int         i;

    i = -1;
    lvl = dir[0] != '.' && dir[0] != '/' ? 1 : 0;
    while(dir[++i])
    {
        if (dir[i + 1] == '.' && dir[i + 2] == '.')
            --lvl;
        else if (dir[i] == '/' && dir[i + 1] != '.')
            ++lvl;
    }
    return (lvl);
}

int             count_args(char *args, int c)
{
    int     count;
    int     debouncing;
    int     i;

    count = 0;
    debouncing = 0;
    while (args[i] != '\0')
    {
        if (debouncing == 0 && args[i] == c)
        {
            debouncing = 1;
            ++count;
        }
        else
            debouncing = 0;
    }
    return (++count);
}

int             is_server_status(char *response)
{
    return (ft_isdigit(response[0]));
}
