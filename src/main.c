/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/28 18:35:56 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	run_line(char *line, t_env **env)
{
	t_token	*tokens;

	tokens = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!tokens)
		return (EXIT_FAILURE);
	if (!init_lexer(line, &tokens))
	{
		free_tokens(&tokens);
		return (EXIT_FAILURE);
	}
	if (!retokenize(&tokens, env))
	{
		free_tokens(&tokens);
		return (EXIT_FAILURE);
	}
	free_tokens(&tokens);

	//tokenize, parse expand,
	//-> if redeiretion is needed redirect
	//execute->if cmd is a buildtin execute builtin 
}


static	int	init_shell(t_env **env)
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
			if (ft_strcmp(line, "exit") == 0)
			{
				write(2, "exit\n", 5);
				exit_value = 0;
				exit(0);
			}
			//add_history(line);
			exit_value = run_line(line, env);
			//if (exit_value == EXIT_FAILURE)
				//inform the user that malloc failed?;
		}
		printf("%s\n",line);
		//free(line);
	}
	return (exit_value);
}

int	main(int argc, char **argv, char **envp)
{
	int		exit_value;
	t_env	*env;


	(void)argv;
	if (argc > 1)
		return (-1);
	init_env(envp, &env); //copy envp
	//add a level to shell
	//syntax check
	exit_value = init_shell(&env);

	
	//terminate: free, clear history
	//for the purpose of checking for leaks : system("leaks -q minishell");
	return (exit_value);
}
