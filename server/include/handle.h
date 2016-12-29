/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 14:12:20 by barbare           #+#    #+#             */
/*   Updated: 2016/12/28 14:47:07 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_H
# define HANDLE_H

#ifndef PATH_MAX
    #define PATH_MAX        4096
#endif
#define PATH_DIR_MAX        4000

#define QUIT    10

#include "config.h"

typedef struct      s_cli           t_cli;

struct      s_cli
{
    int                 fd;
    char                *user;
    char                *pass;
    char                *path;
    char                *path_global;
    char                *auth;
    int                 quit;
};


typedef t_cli           (*t_fct_cmd)(t_cli cli, char *str);

void                    init_id(unsigned long id_cmd[]);

void                    init_fct(t_fct_cmd *cmd);
void                    handle_cli(t_cli cli);
t_cli                   handle_cmd(t_cli cli, char *str);
t_cli                   handle_syst(t_cli cli, char *param);
t_cli                   handle_ls(t_cli cli, char *param);
t_cli                   handle_cd(t_cli cli, char *param);
t_cli                   handle_user(t_cli cli, char *param);
t_cli                   handle_pass(t_cli cli, char *param);
t_cli                   handle_get(t_cli cli, char *param);

unsigned long           getcommand(char *str);


#endif
