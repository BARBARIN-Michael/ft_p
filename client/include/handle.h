/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 11:56:53 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 19:07:59 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_H
# define HANDLE_H

#include "config.h"

#define MAX_CMD 20

typedef void           (*t_fct_cmd)(char *cmd, int fd);
t_cli                   handle_cmd(t_cli cli, t_env env, char *cmd);
void                    handle_control(char *cmd, int fd);
t_env                   init(t_cli config, t_env env);
int                     server_isOK(t_env env);
void                    server(t_cli config, t_env env);
void                    run(t_cli cli, t_env env);

#endif
