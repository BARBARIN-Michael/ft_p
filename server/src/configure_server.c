/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_server.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:30:43 by barbare           #+#    #+#             */
/*   Updated: 2016/12/27 13:50:34 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include <stdio.h>
#include "config.h"
#include "options.h"

t_options       parse_short_options(char opt, const char **data, t_options option)
{
    static char             options[] = {'b', 'p', '\0'};
    static unsigned char    id_options[] = {OPT_B, OPT_P, OPT_NULL};
    int                     i;

    i = -1;
    while (options[++i] != '\0')
    {
        if (options[i] == opt)
        {
            option.opts |= id_options[i];
            option.parameters[id_options[i]] = (char *)*data;
            return option;
        }
    }
    dprintf(STDERR_FILENO, "Cannot find options %c. ", opt);
    printf("%s", MESS_USAGE);
    exit (INVALIDE_OPTION);
    return (option);
}

t_options    set_short_options(const char **data, int count)
{
    int                     a;
    t_options               option;

    option = (t_options){0};
    a = 0;
    while (a < count && data[a] != NULL)
    {
        if (data[a][0] == '-' && data[a][1] != '-')
            option = parse_short_options(data[a][1], &data[a + 1], option);
        ++a;
    }
    return (option);
}
