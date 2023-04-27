/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/27 10:19:57 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_line(char *line, t_env **env)
{
	t_token	*token;

	if (init_lexer(line, &token))
	{
		if (retokenize(&token, env))
		{
			
		}
	}
	
}


int	init_shell(t_env **env)
{
	char	*line;
	int		exit_value;

	while (1)
	{
		//handle signals
		line = readline("\e[34m""MiniShell$>""\x1b[m");
		if (!line) // CTRL D
		{
			write(2, "exit\n", 5);
			exit(0);
		}
		if (ft_strlen(line) > 0)
		{
			if (ft_strcmp(line, "exit") == 0) //might need to trim white space first
			{
				write(2, "exit\n", 5);
				exit_value = 0;
				exit(0);
			}
			add_history(line);
			exit_value = run_line(line, env);
		}
		//tokenize, parse expand,
		//-> if redeiretion is needed redirect
		//execute->if cmd is a buildtin execute builtin 
		//handle history
		printf("%s\n",line);
		//if cmd == exit break
	}
	//free(line);
	return (exit_value);
}

int	main(int argc, char **argv, char **envp)
{
	int		exit_value;
	t_env	*env;


	(void)argv;
	if (argc > 1)
		return (-1);
	env = malloc(sizeof(t_env));
	set_envp(envp, &env); //copy envp
	//add a level to shell
	//syntax check
	exit_value = init_shell(&env);

	//terminate: free, clear history
	//for the purpose of checking for leaks : system("leaks -q minishell");
	return (exit_value);
}
