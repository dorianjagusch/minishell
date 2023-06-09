/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:29:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/09 15:05:34 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include "minishell.h"

# define NOCMMD 127
# define CTRL_EXIT 130
# define BSLASH_EXIT 131
# define SYN_ERR 258
# define ARGERR 259

void	ft_error(int error, char *str);

#endif