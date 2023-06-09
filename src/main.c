/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/09 16:15:00 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_line(char *line, t_env **env)
{
	g_info.tokens = NULL;
	if (init_lexer(line, &g_info.tokens) == EXIT_FAILURE)
		g_info.exit_value = ENOMEM;
	if (g_info.exit_value == ENOMEM
		|| retokenize(&g_info.tokens, env) == EXIT_FAILURE)
		g_info.exit_value = ENOMEM;
	if (g_info.exit_value == 0)
	{
		g_info.commands = init_command(g_info.tokens, 0);
		if (g_info.exit_value != SIGINT)
			redirect_exe(g_info.commands, *env);
		else
			g_info.exit_value = 1;
	}
	ft_clear_everything(&g_info);
	if (g_info.exit_value == ENOMEM)
		exit(1);
}

void	switch_echoctl(struct termios *t, int toggle)
{
	tcgetattr(STDIN_FILENO, t);
	if (toggle == OFF)
	{
		t->c_lflag &= ~(ECHOCTL);
		if (tcsetattr(STDIN_FILENO, TCSANOW, t) == -1)
			ft_putstr_fd("error in tcsetattr()\n", 2);
	}
	if (toggle == ON)
	{
		t->c_lflag |= ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSANOW, t) == -1)
			ft_putstr_fd("error in tcsetattr()\n", 2);
	}
}

static void	init_run(t_env **env)
{
	int	empty_line;

	add_history(g_info.line);
	empty_line = ft_empty_str(g_info.line);
	if (syntax_check(g_info.line))
		run_line(g_info.line, env);
	if (empty_line != 1)
		set_exit_value(env);
}

static void	init_shell(t_env **env)
{
	struct termios	t;

	while (1)
	{
		switch_echoctl(&t, OFF);
		global_signal(ON);
		g_info.line = readline(NAME);
		if ((!g_info.line || ft_strncmp(g_info.line, "exit", 4) == 0)
			&& (handle_exit(g_info.line, env) == 1))
		{
			add_history(g_info.line);
			set_exit_value(env);
			free(g_info.line);
			continue ;
		}
		switch_echoctl(&t, ON);
		if (ft_strlen(g_info.line) > 0 && g_info.line[0])
			init_run(env);
		if (g_info.line)
			free(g_info.line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	ft_bzero(&g_info, sizeof(t_info));
	(void)argv;
	if (argc > 1)
		return (-1);
	print_greeting();
	init_env(envp, &g_info.env);
	if (!g_info.env)
		return (1);
	init_shell(&g_info.env);
	return (0);
}
