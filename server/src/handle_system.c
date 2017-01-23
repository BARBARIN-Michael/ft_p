/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 10:26:33 by barbare           #+#    #+#             */
/*   Updated: 2017/01/16 17:50:53 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle.h"
#include "message.h"
#include "config.h"

t_cli       handle_syst(t_env UNUSED(env), t_cli cli, char *param)
{
    (void)param;
    S_MESSAGE(215, cli.fd);
    return (cli);
}
