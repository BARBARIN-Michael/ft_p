/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:53:55 by mbarbari          #+#    #+#             */
/*   Updated: 2014/11/09 22:13:09 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memstrstr(const void *mem, const char *cmp, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		if (ft_memcmp(&mem[i], cmp, ft_strlen(cmp)) == 0)
			return ((void *)&mem[i]);
		++i;
	}
	return (NULL);
}

void	*ft_memchr(const void *src, int c, size_t len)
{
	unsigned char	*str;

	str = (unsigned char*)src;
	while (*str != (unsigned char)c && len > 0)
	{
		len--;
		str++;
	}
	if (len == 0)
		return (NULL);
	else
		return (str);
}
