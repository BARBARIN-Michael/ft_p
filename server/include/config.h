/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 17:30:51 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 12:29:54 by barbare          ###   ########.fr       */
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
	# define CRLF "\r\n"
# elif __linux__
    # define SYSTEM "LINUX"
	# define CRLF "\n"
# else
    # define SYSTEM "OSX"
	# define CRLF "\n"
# endif
# define ASCII 'A'
# define BINARY 'I'

# define SOCKADDR_IN struct sockaddr_in
# define SOCKADDR struct sockaddr
# define IN_ADDR struct in_addr

# define EXEC(EXE, ARGS) execve(EXE, ARGS, environ);

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
    unsigned short      control_port;
    unsigned short      data_port;
    char                path[PATH_MAX];
    char                *authorized;
    unsigned int        backlog;
};

struct  s_env
{
    char                **env;
    int                 cli_fd; //Change to pi_fd
	int					dtp_fd;
    int                 control_fd;
    int                 data_fd;
    unsigned int        isrun;
    struct sockaddr_in  cli_addr;
    struct hostent      *host;
    struct protoent     *proto;
	t_serv				config;
};

t_options               set_short_options(const char **args, int count);
t_options               parse_short_options(char opt, const char **data, t_options option);

#endif
