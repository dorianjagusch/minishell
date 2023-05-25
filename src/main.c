/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/24 13:51:24 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	run_line(char *line, t_env **env)
{
	t_token		*tokens;
	t_command	*commands;

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
	//redirect_exe(commands, *env);
	//terminate: free, clear history
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
				free(line);
				exit(0);
			}
			if (line && *line)
				add_history(line);
			if (syntax_check(line))
				exit_value = run_line(line, env);
			else
				exit_value = 258;
			//if (exit_value == EXIT_FAILURE)
				//inform the user that malloc failed?;
		}
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
	init_env(envp, &env);
	exit_value = init_shell(&env);
	
	//for the purpose of checking for leaks : system("leaks -q minishell");
	return (exit_value);
}
