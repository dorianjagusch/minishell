/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:29:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/08 14:53:32 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include "minishell.h"

# define EPATH 127 /* No such file or directory */
# define NOFILE 1
# define NOACCESS 1
# define NOCMMD 1
# define MEMERR 1

void	ft_error(int error, char *str);

#endif