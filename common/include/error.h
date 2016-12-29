/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 17:17:03 by barbare           #+#    #+#             */
/*   Updated: 2016/12/27 18:15:48 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ERROR_H
# define ERROR_H

# define ERROR           -1
# define SOCKET_ERROR    -2
# define HOST_ERROR      -3
# define FORK_ERROR      -4
# define DIR_ERROR       -5

# define ERR_NOTACCESS -6
# define ERR_BADPATH -7
# define ERR_UNKNOWERROR -8
# define ERR_CMDNOTFOUND -9
# define ERR_USERNOTEXIST -10

# define STR_NOTACCESS C_RED"ERROR: You don't have permission for this file"
# define STR_BADPATH C_RED"ERROR: No such file or directory"
# define STR_UNKNOWERROR C_RED"ERROR: not defined"
# define STR_CMDNOTFOUND C_RED"ERROR: Command not found"
# define STR_USERNOTEXIST C_RED"ERROR: User not exist"

# define ERROR_NOTACCESS -1
# define ERROR_PATH -2

#endif
