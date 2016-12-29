/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:50:33 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 19:00:46 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>

# define PATH_MAX 4096

# define SOCKADDR_IN struct sockaddr_in
# define SOCKADDR struct sockaddr
# define IN_ADDR struct in_addr

typedef struct s_env    t_env;
typedef struct s_cli    t_cli;

struct      s_cli
{
    char                *addr;
    unsigned short      port;
    char                path[PATH_MAX];
};

struct                  s_env
{
    int                 cli_fd;
    int                 srv_fd;
    unsigned int        isrun;
    struct sockaddr_in  cli_addr;
    struct hostent      *host;
    struct protoent     *proto;
};

#endif
