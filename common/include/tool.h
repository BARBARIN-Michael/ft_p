/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:12:20 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 18:20:57 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOL_H
# define TOOL_H

unsigned long           djb2(const char *str, unsigned int size);
int                     lvl_dir(char *dir);
unsigned int            count_args(char *args, int c);
int                     is_server_status(char *response);

#endif
