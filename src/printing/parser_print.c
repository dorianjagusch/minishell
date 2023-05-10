/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:07:32 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/10 15:49:21 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#define PARAMS 5

void	print_parser(t_command **command)
{
	t_command	*tmp;

	if (!command || !*command)
	{
		ft_printf("END\n");
		return ;
	}
	tmp = *command;
	ft_printf("COMMAND: %s\n", tmp->command);
	ft_printf("-----------------------\n");
	ft_printf("PARAMS:\n");
	ft_print_array(tmp->params, STDOUT_FILENO);
	ft_printf("n_params: %d\n", tmp->n_params);
	ft_printf("-----------------------\n");
	ft_printf("infile:\t%s\n", tmp->infile);
	ft_printf("infile fd:\t%d\n", tmp->fds[0]);
	ft_printf("redirect:\t%d\n", tmp->in_redirect);
	ft_printf("-----------------------\n");
	ft_printf("outfile:\t%s\n", tmp->outfile);
	ft_printf("outfile fd:\t%d\n", tmp->fds[1]);
	ft_printf("redirect:\t%d\n", tmp->out_redirect);
	ft_printf("=======================\n");
	print_parser(&(tmp->next));
}

// int	main(void)
// {
// 	t_command	*test;
// 	int			i;	
// 	const char	str[] = "I eat children :D";

// 	test = ft_calloc(1, sizeof(t_command));
// 	test->command = "cat";
// 	test->infile = "src/main.c";
// 	test->outfile = "test.c";
// 	i = 0;
// 	test->params = ft_calloc(PARAMS + 1, sizeof(char *));
// 	while (i < PARAMS)
// 		test->params[i++] = (char *)str;
// 	test->n_params = ft_count_elements(test->params);
// 	test->in_redirect = 2;
// 	test->fds[0] = open(test->infile, O_RDONLY | O_APPEND);
// 	test->fds[1] = open(test->infile, O_WRONLY, 0644);
// 	print_parser(&test);
// 	return (0);
// }
