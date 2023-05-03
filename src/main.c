/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/03 17:33:20 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	run_line(char *line, t_env **env)
{
	t_token		*tokens;
	t_command	*commands;

	tokens = (t_token *)ft_calloc(sizeof(t_token), 1);
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
	commands = init_command(tokens); //maybe free tokens inside
	free_tokens(&tokens);
	//redirect(commands);
	//executer(env, commands);
	return (0); //added because og compaint
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
			write(2, "\n", 1);
			exit(1);
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

void	sigint_handler(int signo)
{
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	int		exit_value;
	t_env	*env;
	struct sigaction s;

	s.sa_handler = sigint_handler;
	sigemptyset(&s.sa_mask);
	s.sa_flags = SA_RESTART;
	sigaction(SIGINT, &s, NULL);
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
