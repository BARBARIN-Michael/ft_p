/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_server.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:30:43 by barbare           #+#    #+#             */
/*   Updated: 2016/12/19 17:55:11 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include "config.h"
#include "options.h"

t_servconfig        config_zero(void)
{
    return ((t_servconfig){0});
}

t_servconfig       get_short_options(char opt, char **data, t_servconfig conf)
{
    static char             options[] = {'p', 'a', '\0'};
    static unsigned char    id_options[] = {OPT_P, OPT_A, OPT_NULL};
    static unsigned char    is_params[] = {OPT_P, OPT_A, OPT_NULL};
    int                     i;

    i = -1;
    while (options[++i] != '\0')
    {
        if (options[i] == opt)
        {
            conf.options.opts |= id_options[i];
            if ((conf.options.isparam |= is_params[i]) != OPT_NULL)
                conf.options.parameters[id_options[i]] = *data;
        }
        else
        {
            ft_putstr_fd("Cannot find options ", STDERR_FILENO);
            ft_putchar_fd(opt, STDERR_FILENO);
            ft_putendl_fd("!\nValide options : -p [Port] -a [addr]", STDERR_FILENO);
            return ((t_servconfig){.err = INVALIDE_OPTION});
        }
    }
    return conf;
}

t_servconfig    set_short_options(char **data)
{
    t_servconfig        config;
    unsigned int        a;

    config = config_zero();
    while (*data != NULL)
    {
        if (data[0][0] == '-' && data[0][1] != '-')
        {
            a = 1;
            while (data[0][a] != ' ' || data[0][a] != '\0')
            {
                config = get_short_options(data[0][a], &data[a], config);
                if (config.err != 0)
                    exit(config.err);
                ++a;
            }
            data = &data[a];
        }
        ++data;
    }
    return (config);
}

t_servconfig    configure_server(char **data)
{
    t_servconfig    config;

    config = set_short_options(data);
    return (config);
}
