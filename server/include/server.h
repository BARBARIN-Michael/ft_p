/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 12:20:05 by barbare           #+#    #+#             */
/*   Updated: 2016/12/27 19:22:07 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SERVER_H
# define SERVER_H

#include "config.h"

t_env           init(t_serv conf);
void            server(t_serv conf, t_env env);
void            run(t_serv conf, t_env env);

#endif
