/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 17:35:19 by barbare           #+#    #+#             */
/*   Updated: 2017/01/27 13:19:19 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "tool.h"

#ifndef MESSAGE_H
# define MESSAGE_H

# define PTIME(COL) print_time(COL);

# define S_MESSAGE(X, FD, ...) {CLI(X, FD, C_GREEN, ##__VA_ARGS__);}
# define F_MESSAGE(X, FD) {CLI(X, FD, C_GREEN); SRV(X, FD);}
# define E_MESSAGE(X, FD) {CLI(X, FD, C_RED); SRV(X, FD);}

# define GET_RESPONSE(X, CODE) ft_strncmp(X, MESS_ ## CODE, 3)

# define SEND_S() dprintf(STDERR_FILENO, C_GREEN"Success\n"C_NONE);
# define SEND_F() dprintf(STDERR_FILENO, C_RED"Failed\n"C_NONE);
# define SEND_E() dprintf(STDERR_FILENO, C_RED"Error\n"C_NONE);

# define CLI(X, FD, COL, ...) dprintf(FD, MESS_ ## X, ##__VA_ARGS__);
# define SRV(X, FD) CLIPRINT(FD); printf(C_RED"%s%s\n", MESS_ ## X, C_NONE);
# define CLIPRINT(FD) printf(C_CYAN"Client %d : ", FD);

# define PRINT(STR, SIZE, COL) {printf("%s%.*s%s\n", COL, SIZE, STR, C_NONE);}
# define OK(STR, SIZE) { PTIME(C_GREEN) PRINT(STR, SIZE, C_GREEN) }
# define KO(STR, SIZE) { PTIME(C_RED) PRINT(STR, SIZE, C_RED)}

# define RESPONSE(STR) { PTIME(C_GREEN) printf("%s%s\n", STR, C_NONE); }
# define FAILED(STR, ...) { PTIME(C_RED) dprintf(1, STR, ##__VA_ARGS__); }
# define STATUS(STR, ...) { PTIME(BLUE) dprintf(1, STR, ##__VA_ARGS__); }

# define MESS_110 "110 Restart marker reply.\r\n"
# define MESS_120 "120 Service ready in nnn minutes.\r\n"
# define MESS_125 "125 Data connection already open; transfer starting.\r\n"
# define MESS_150 "150 File status okay; about to open data connection.\r\n"

# define MESS_200 "200 OK.\r\n"
# define MESS_202 "202 Command not implemented, superfluous at this site.\r\n"
# define MESS_211 "211 System status, or system help reply.\r\n"
# define MESS_212 "212 Directory status.\r\n"
# define MESS_213 "213 File status.\r\n"
# define MESS_214 "214 Help message.\r\n"
# define MESS_215 "215 "SYSTEM" system type.\r\n"
# define MESS_220 "220 Service ready for new user.\r\n"
# define MESS_221 "221 Service closing control connection.\r\n"
# define MESS_225 "225 Data connection open; no transfer in progress.\r\n"
# define MESS_226 "226 Closing data connection.\r\n"
# define MESS_227 "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n"
# define MESS_229 "229 Entering Extended Passive Mode (|||%d|).\r\n"
# define MESS_230 "230 User logged in, proceed.\r\n"
# define MESS_250 "250 Requested file action okay, completed.\r\n"
# define MESS_257 "257 \"%s\".\r\n"

# define MESS_331 "331 User name okay, need password.\r\n"
# define MESS_332 "332 Need account for login.\r\n"
# define MESS_350 "350 Requested file action pending further information.\r\n"

# define MESS_421 "421 Service not available, closing control connection.\r\n"
# define MESS_425 "425 Use PASV.\r\n"
# define MESS_426 "426 Connection closed; transfer aborted.\r\n"
# define MESS_450 "450 Requested file action not taken.\r\n"
# define MESS_451 "451 Requested action aborted: local error in processing.\r\n"

# define MESS_500 "500 Syntax error, command unrecognized.\r\n"
# define MESS_501 "501 Syntax error in parameters or arguments.\r\n"
# define MESS_502 "502 Command not implemented.\r\n"
# define MESS_503 "503 Bad sequence of commands.\r\n"
# define MESS_504 "504 Command not implemented for that parameter.\r\n"
# define MESS_530 "530 Not logged in.\r\n"
# define MESS_532 "532 Need account for storing files.\r\n"
# define MESS_550 "550 Requested action not taken.\r\n"
# define MESS_551 "551 Requested action aborted: page type unknown.\r\n"
# define MESS_552 "552 Requested file action aborted.\r\n"
# define MESS_553 "553 Requested action not taken.\r\n"

#endif
