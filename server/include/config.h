/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:30:51 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 18:54:37 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>

# ifndef PATH_MAX
    #define PATH_MAX        4096
# endif
# define PATH_DIR_MAX        4000

extern char **environ;
# if __WIN32__
    # define SYSTEM "WIN32"
# elif __linux__
    #define SYSTEM "LINUX"
# else
    #define SYSTEM "OSX"
# endif

# define EXEC(EXE, ARGS) execve(EXE, ARGS, environ);
# define SOCKADDR struct sockaddr_in
# define IN_ADDR struct in_addr

# define SALT                "UnFtpSecure"

# define MESS_USAGE          "usage : -b [backlog] -p [authorized_file] [port]"

typedef struct      s_serv          t_serv;
typedef struct      s_env           t_env;
typedef struct      s_options       t_options;

typedef unsigned char               t_opts;

struct      s_options
{
    t_opts                  opts;
    char                    *parameters[20];
    int                     error;
};

struct      s_serv
{
    unsigned short      port;
    char                path[PATH_MAX];
    char                *authorized;
    unsigned int        backlog;
};

struct  s_env
{
    char                **env;
    int                 cli_fd;
    int                 srv_fd;
    unsigned int        isrun;
    struct sockaddr_in  srv_addr;
    struct sockaddr_in  cli_addr;
    struct hostent      *host;
    struct protoent     *proto;
};

t_options               set_short_options(const char **args, int count);
t_options               parse_short_options(char opt, const char **data, t_options option);

#endif
