/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/05 13:51:05 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *line;

	printf("%s",envp[0]);
	if (argc < 1)
		return (-1);
	//copy envp
	//add a level to shell
	while(1)
	{
		//handle signals
		line = readline("\e[34m""MiniShell$>""\x1b[m");
		//syntax check, tokenize, parse
		//expand, execute->if cmd is a buildtin execute builtin
		//handle history
		printf("%s\n",line);
	}
	return (0);
}
