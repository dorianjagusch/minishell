/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:07:32 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/12 16:39:07 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#define N_PARAMS 5

void	print_parser(t_command *command)
{
	if (!command)
	{
		ft_printf("END\n");
		return ;
	}
	ft_printf("command: %s\n", command->command);
	ft_printf("ID: %d\n", command->id);
	ft_printf("-----------------------\n");
	ft_printf("PARAMS:\n");
	ft_print_array(command->params, STDOUT_FILENO);
	ft_printf("n_params: %d\n", command->n_params);
	ft_printf("-----------------------\n");
	ft_printf("infile:\t%s\n", command->infile);
	ft_printf("infile fd:\t%d\n", command->fds[0]);
	ft_printf("redirect:\t%d\n", command->in_redirect);
	ft_printf("-----------------------\n");
	ft_printf("outfile:\t%s\n", command->outfile);
	ft_printf("outfile fd:\t%d\n", command->fds[1]);
	ft_printf("redirect:\t%d\n", command->out_redirect);
	ft_printf("success:\t%d\n", command->success);
	ft_printf("=======================\n");
	print_parser(command->next);
}
