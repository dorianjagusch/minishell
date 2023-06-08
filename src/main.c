/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/08 15:50:02 by asarikha         ###   ########.fr       */
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
		redirect_exe(g_info.commands, *env);
	}
	ft_clear_everything(&g_info);
	if (g_info.exit_value == ENOMEM)
		exit(1);
}

static	int	handle_exit(char *line, t_env **env)
{
	size_t		i;
	char		str[5];

	i = 0;
	ft_strlcpy(str, "exit", 5);
	if (!line)
	{
		free_env(&g_info.env);
		ft_printf_fd(2, "\e[38;2;255;105;180mSashay away 💃\x1b[m \n");
		exit(0);
	}
	while (line[i] == str[i] && line[i] != '\0' && str[i] != '\0' && i < 4)
		i++;
	if (i == 4 && line[i] != '\0')
		return (handle_exit_arg(line, i, env));
	free(line);
	free_env(&g_info.env);
	ft_printf_fd(2, "\e[38;2;255;105;180mSashay away 💃\x1b[m \n");
	exit(0);
	return (0);
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
			continue ;
		}
		switch_echoctl(&t, ON);
		if (ft_strlen(g_info.line) > 0)
		{
			if (g_info.line && *g_info.line)
				add_history(g_info.line);
			if (syntax_check(g_info.line))
				run_line(g_info.line, env);
			else if (g_info.exit_value == SYN_ERR)
				free(g_info.line);
		}
		set_exit_value(env);
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
