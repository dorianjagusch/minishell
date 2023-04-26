/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/26 13:04:20 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char 	*line;
	t_ev	*env;

	(void)argv;
	if (argc > 1)
		return (-1);
	init_env(envp, &env); //copy envp
	//add a level to shell
	while(1)
	{
		//handle signals
		line = readline("\e[34m""MiniShell$>""\x1b[m");
		//syntax check, tokenize, parse expand,
		//-> if redeiretion is needed redirect
		//execute->if cmd is a buildtin execute builtin 
		//handle history
		printf("%s\n",line);
		//if cmd == exit break
	}
	//terminate: free, clear history
	//for the purpose of checking for leaks : system("leaks -q minishell");
	return (0);
}
