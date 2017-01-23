/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:33:22 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 15:12:16 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "libft.h"
#include "tool.h"
#include "message.h"

void            print_time(char *color)
{
    time_t      t1;
    struct tm   *local;

    time(&t1);
    local = localtime(&t1);
    dprintf(1, "%s%02d:%02d:%02d\t", color,
            local->tm_hour, local->tm_min, local->tm_sec);
}

unsigned long   djb2(const char *str, unsigned int size)
{
    unsigned long hash;
    int c;

    hash = 5381;
    while (size && (c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
        --size;
    }
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

unsigned int    count_args(char *args, int c)
{
    int     count;
    int     debouncing;
    int     i;

    count = 0;
    i = 0;
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
        ++i;
    }
    return (count);
}
