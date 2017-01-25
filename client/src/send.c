/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:43:08 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 14:01:41 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#
#include "libft.h"
#include "config.h"
#include "tool.h"
#include "read.h"
#include "message.h"

int			getheader(char *str)
{
	char	id[4];
	int		i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (!str || str[i] == '\0')
		return (-1);
	id[0] = str[i];
	id[1] = str[i + 1];
	id[2] = str[i + 2];
	id[3] = '\0';
	return (ft_atoi(id));
}

int			protocol(char *str)
{
	int		proto;

	proto = str[0] - '0';
	if (proto >= 4)
		dprintf(STDOUT, "%s%s%s\n", RED, str, C_NONE);
	else
		dprintf(STDOUT, "%s%s%s\n", C_GREEN, str, C_NONE);
	if (proto >= 4)
		return (FALSE);
	return (TRUE);
}

void		is_success(int isok)
{
	if (isok)
		dprintf(STDOUT, "%sSUCCESS !%s\n", C_GREEN, C_NONE);
	else
		dprintf(STDOUT, "%sERROR !%s\n", RED, C_NONE);
}

void		send_request(const char *cmd, char *args, int fd)
{
	char		buf[PATH_MAX];
	char		*str;

	buf[0] = '\0';
	if ((str = ft_strchr(args, '\n')))
		str[0] = '\0';
	if (args == NULL)
		snprintf(buf, PATH_MAX, "%s\r\n", cmd);
	else
		snprintf(buf, PATH_MAX, "%s %s\r\n", cmd, args);
	dprintf(fd, "%s", buf);
}
