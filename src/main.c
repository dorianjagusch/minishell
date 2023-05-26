/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/26 15:50:53 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	run_line(char *line, t_env **env)
{
	g_info.tokens = NULL;
	if (init_lexer(line, &g_info.tokens) == EXIT_FAILURE)
	{
		free_tokens(&g_info.tokens);
		return (EXIT_FAILURE);
	}
	if (retokenize(&g_info.tokens, env) == EXIT_FAILURE)
	{
		free_tokens(&g_info.tokens);
		return (EXIT_FAILURE);
	}
	g_info.commands = init_command(g_info.tokens, 0);
	print_parser(g_info.commands);
	ft_clear_everything(g_info);
	return (0);
}

static int	init_shell(t_env **env)
{
	while (1)
	{
		init_signal();
		g_info.line = readline("\e[34m""MiniShell$> ""\x1b[m");
		if (!g_info.line)
		{
			if (g_info.env)
				free_env(&g_info.env);
			write(2, "exit\n", 5);
			exit(1);
		}
		if (ft_strlen(g_info.line) > 0)
		{
			if (ft_strcmp(g_info.line, "exit") == 0)
			{
				if (g_info.env)
					free_env(&g_info.env);
				write(2, "exit\n", 5);
				g_info.exit_value = 0;
				free(g_info.line);
				exit(0);
			}
			if (g_info.line && *g_info.line)
				add_history(g_info.line);
			if (syntax_check(g_info.line))
				g_info.exit_value = run_line(g_info.line, env);
			else
			{
				g_info.exit_value = 258;
				free(g_info.line);
			}
		}
	}
	return (g_info.exit_value);
}


int	main(int argc, char **argv, char **envp)
{
	int		exit_value;

	ft_bzero(&g_info, sizeof(t_info));
	(void)argv;
	if (argc > 1)
		return (-1);

	g_info.env = NULL;
	init_env(envp, &g_info.env);
	exit_value = init_shell(&g_info.env);
	return (exit_value);
}
