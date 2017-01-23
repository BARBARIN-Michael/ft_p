/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 11:23:47 by barbare           #+#    #+#             */
/*   Updated: 2017/01/20 09:37:08 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "handle.h"
#include "error.h"
#include "message.h"
#include "tool.h"

t_cli        handle_quit(t_env UNUSED(env), t_cli cli, char *str)
{
	(void)str;
	S_MESSAGE(221, cli.fd);
    dprintf(1, C_CYAN"Client %d : %sDISCONNECT\n"C_NONE, cli.fd, C_BLUE);
	close(cli.fd);
    exit(0);
}
