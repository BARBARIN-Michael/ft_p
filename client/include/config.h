/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:50:33 by barbare           #+#    #+#             */
/*   Updated: 2017/01/23 15:15:17 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include "ft_stream.h"

# define PATH_MAX 4096

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
# define SOCKADDR struct	sockaddr
# define IN_ADDR struct		in_addr

# define STDOUT				STDOUT_FILENO
# define STDIN				STDIN_FILENO
# define STDERR				STDERR_FILENO

# define PROT				"\r\n"

typedef struct s_env    t_env;
typedef struct s_cli    t_cli;
typedef struct s_sock	t_sock;

struct					s_sock
{
	t_stream			pi;
	t_stream			dtp;
};

struct					s_cli
{
    char                *addr;
    unsigned short      port;
    char                *dtp_addr;
    unsigned short      dtp_port;
    char                path[PATH_MAX];
	t_sock				sock;
	int					istransferable;
	int					type_transfer;
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

int             server_isOK(t_cli cli);
t_env           init_client(t_cli cli, t_env env);
t_env           init_socket(t_cli cli, t_env env);
void            client(t_cli cli);
void            run(t_cli cli, t_env env);

#endif
