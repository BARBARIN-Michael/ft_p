/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 16:56:25 by barbare           #+#    #+#             */
/*   Updated: 2016/12/23 17:11:17 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int         get_file(char **args)
{
    if (access(args[1], 0 | F_OK) != 0)
    {
        ft_putendl_fd(STR_BADPATH);
        return (ERR_BADPATH);
    }
    else if (access(args[1], 0 | F_OK | R_OK) != 0)
    {
        ft_putendl_fd(STR_NOTACCESS);
        return (ERR_NOTACCESS);
    }
    return (0);
}

int         handle_get(t_env env, t_servconfig conf, char *param)
{
    char **args;

    args = ft_strsplit2(param, ' ');
    get_file(args);
}
