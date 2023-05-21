/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/05/21 17:35:00 by djagusch         ###   ########.fr       */
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
	tokens = NULL;
	if (init_lexer(line, &tokens) == EXIT_FAILURE)
	{
		free_tokens(&tokens);
		return (EXIT_FAILURE);
	}
	if (retokenize(&tokens, env) == EXIT_FAILURE)
	{
		free_tokens(&tokens);
		return (EXIT_FAILURE);
	}
	commands = init_command(tokens); //maybe free tokens inside
	print_parser(commands);
	free_tokens(&tokens);
	//redirect(commands);
	//executer(env, commands);
	return (0); //added because og compaint
}

void	sigint_handler(int signo)
{
	if (signo)
		ft_printf("\n\e[34m""MiniShell$>""\x1b[m");
}

static	int	init_shell(t_env **env)
{
	char				*line;
	int					exit_value;
	struct sigaction	s;

	s.sa_handler = sigint_handler;
	sigemptyset(&s.sa_mask);
	s.sa_flags = SA_RESTART;
	while (1)
	{
		sigaction(SIGINT, &s, NULL);
		line = readline("\e[34m""MiniShell$>""\x1b[m");
		if (!line) // CTRL D
		{
			write(2, "exit\n", 5);
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
		//printf("%s\n",line);
		free(line);
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
	env = NULL;
	init_env(envp, &env); //copy envp
	//ft_env(&env, NULL);
	//add a level to shell
	//syntax check
	exit_value = init_shell(&env);
	//terminate: free, clear history
	//for the purpose of checking for leaks : system("leaks -q minishell");
	return (exit_value);
}
