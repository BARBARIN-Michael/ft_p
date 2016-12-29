/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 17:35:19 by barbare           #+#    #+#             */
/*   Updated: 2016/12/29 18:49:58 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "config.h"

#ifndef MESSAGE_H
# define MESSAGE_H

# define S_MESSAGE(X, FD) {CLI(X, FD, C_GREEN); SRV(X, FD); SEND_S();}
# define F_MESSAGE(X, FD) {CLI(X, FD, C_GREEN); SRV(X, FD); SEND_F();}
# define E_MESSAGE(X, FD) {CLI(X, FD, C_RED); SRV(X, FD); SEND_E();}
# define GET_RESPONSE(X, CODE) ft_strncmp(X, MESS_ ## CODE, 3)

# define SEND_S() dprintf(STDERR_FILENO, C_GREEN"Success\n"C_NONE);
# define SEND_F() dprintf(STDERR_FILENO, C_RED"Failed\n"C_NONE);
# define SEND_E() dprintf(STDERR_FILENO, C_RED"Error\n"C_NONE);

# define CLI(X, FD, COL) dprintf(FD, "%s\r\n", MESS_ ## X);
# define SRV(X, FD) printf(C_CYAN"Client %d : %s%s\n", FD, C_RED, MESS_ ## X);

#define RESPONSE(STR) TIME(C_GREEN) dprintf(1, STR);
#define FAILED(STR, ...) TIME(C_RED) dprintf(1, STR, ##__VA_ARGS__);
#define STATUS(STR, ...) TIME(C_GRAY) dprintf(1, STR, ##__VA_ARGS__);

#define TIME(COL) dprintf(1, "%s%s\t", COL, __TIME__);

/*
** ==== Etablissement de connexion ===
** 120
** 220
** 220
** 421

** === Ouverture de session ===
** USER
** 230
** 530
** 500, 501, 421
** 331, 332

** PASS
** 230
** 202
** 530
** 500, 501, 503, 421

** CWD
** 250
** 500, 501, 502, 421, 530, 550

** === Fermeture de session ===
** QUIT
** 221
** 500

** === Paramètres de transfert ===
** PORT
** 200
** 500, 501, 421, 530

** PASV
** 227
** 500, 501, 502, 421, 530

** MODE
** 200
** 500, 501, 504, 421, 530

** TYPE
** 200
** 500, 501, 504, 421, 530

** STRU
** 200
** 500, 501, 504, 421, 530

** === Commandes de service fichiers ===
** ALLO
** 200
** 202
** 500, 501, 504, 421, 530
** REST
** -- RFC959 45 --
** 500, 501, 502, 421, 530
** 350

** STOR
** 125, 150
** (110)
** 226, 250
** 425, 426, 451, 551, 552
** 532, 450, 452, 553
** 500, 501, 421, 530

** STOU
** 125, 150
** (110)
** 226, 250
** 425, 426, 451, 551, 552
** 532, 450, 452, 553
** 500, 501, 421, 530

** RETR
** 125, 150
** (110)
** 226, 250
** 425, 426, 451
** 450, 550
** 500, 501, 421, 530

** LIST
** 125, 150
** 226, 250
** 425, 426, 451
** 450
** 500, 501, 502, 421, 530

** NLST
** 125, 150
** 226, 250
** 425, 426, 451
** 450
** 500, 501, 502, 421, 530

** APPE
** 125, 150
** (110)
** 226, 250
** 425, 426, 451, 551, 552
** 532, 450, 550, 452, 553
** 500, 501, 502, 421, 530

** RNFR
** 450, 550
** 500, 501, 502, 421, 530
** 350

** RNTO
** 250
** 532, 553
** 500, 501, 502, 503, 421, 530

** -- RFC959 46 --
** DELE
** 250
** 450, 550
** 500, 501, 502, 421, 530
** RMD
** 250
** 500, 501, 502, 421, 530, 550
** MKD
** 257
** 500, 501, 502, 421, 530, 550
** PWD
** 257
** 500, 501, 502, 421, 550
** ABOR
** 225, 226
** 500, 501, 502, 421

** === Commandes d'information ===
** SYST
** 215
** 500, 501, 502, 421
** STAT
** 211, 212, 213
** 450
** 500, 501, 502, 421, 530
** HELP
** 211, 214
** 500, 501, 502, 421

** === Commandes diverses ===
** SITE
** 200
** 202
** 500, 501, 530
** NOOP
** 200
** 500, 421

** === Ouverture de session ===
** USER
** 230
** 530
** 500, 501, 421
** 331, 332
** PASS
** 230
** 202
** 530
** 500, 501, 503, 421

*/

# define MESS_110 "110 Restart marker reply."
# define MESS_120 "120 Service ready in nnn minutes."
# define MESS_125 "125 Data connection already open; transfer starting."
# define MESS_150 "150 File status okay; about to open data connection."
# define MESS_202 "202 Command not implemented, superfluous at this site."
# define MESS_211 "211 System status, or system help reply."
# define MESS_212 "212 Directory status."
# define MESS_213 "213 File status."
# define MESS_214 "214 Help message."
# define MESS_215 "215 "SYSTEM" system type."
# define MESS_220 "220 Service ready for new user."
# define MESS_221 "221 Service closing control connection."
# define MESS_225 "225 Data connection open; no transfer in progress."
# define MESS_226 "226 Closing data connection."
# define MESS_227 "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2)."
# define MESS_230 "230 User logged in, proceed."
# define MESS_250 "250 Requested file action okay, completed."
# define MESS_257 "257 \"PATHNAME\" created."

# define MESS_331 "331 User name okay, need password."
# define MESS_332 "332 Need account for login."
# define MESS_350 "350 Requested file action pending further information."

# define MESS_421 "421 Service not available, closing control connection."
# define MESS_425 "425 Can't open data connection."
# define MESS_426 "426 Connection closed; transfer aborted."
# define MESS_450 "450 Requested file action not taken."
# define MESS_451 "451 Requested action aborted: local error in processing."

# define MESS_500 "500 Syntax error, command unrecognized."
# define MESS_501 "501 Syntax error in parameters or arguments."
# define MESS_502 "502 Command not implemented."
# define MESS_503 "503 Bad sequence of commands."
# define MESS_504 "504 Command not implemented for that parameter."
# define MESS_530 "530 Not logged in."
# define MESS_532 "532 Need account for storing files."
# define MESS_550 "550 Requested action not taken."
# define MESS_551 "551 Requested action aborted: page type unknown."
# define MESS_552 "552 Requested file action aborted."
# define MESS_553 "553 Requested action not taken."

#endif
