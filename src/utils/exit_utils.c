/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:13:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/12 11:24:57 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_value(t_env **env)
{
	char	*exit_str;

	exit_str = ft_itoa(g_info.exit_value);
	if (!exit_str)
	{
		ft_error(ENOMEM, "");
		free_env(env);
		exit(1);
	}
	replace_env(env, "?", exit_str);
	free(exit_str);
	g_info.exit_value = 0;
}

static int	num_invalid(char *line, size_t i, t_env **env)
{
	if (line[i] == '-' && line[i + 1] == '1' && (line[i + 2] == '\0'
			|| !ft_isdigit(line[2])))
		return (0);
	if (line[i] == '-' || line[i] == '+')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	if ((i > 19 && (line[i] != '+' && line[i] != '-' ))
		|| (i > 20 && (line[i] == '+' || line[i] == '-' ))
		|| ft_atoll(&line[i]) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "\033[1m\e[31mGayAsHell\x1b[m: ");
		ft_printf_fd(2, "exit: numeric argument required, sis 💅\n");
		free(line);
		free_env(env);
		ft_printf_fd(2, "\e[38;2;255;105;180mSashay away \x1b[m \n");
		return (1);
	}
	return (0);
}

int	handle_exit_num_arg(char *line, size_t i, t_env **env)
{
	if (num_invalid(line, i, env))
		exit (255);
	g_info.exit_value = ft_atoi(&line[i]);
	if (line[i] == '-' || line[i] == '+')
		i++;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i])
	{
		ft_printf_fd(STDERR_FILENO, "\033[1m\e[31mGayAsHell\x1b[m: ");
		ft_printf_fd(2, "exit: numeric argument required, sis 💅\n");
		g_info.exit_value = 1;
		return (1);
	}
	else
	{
		free(line);
		free_env(env);
		ft_printf_fd(2, "\e[38;2;255;105;180mSashay away \x1b[m \n");
		exit(g_info.exit_value);
	}
	return (0);
}

int	handle_exit_arg(char *line, size_t i, t_env **env)
{
	while (ft_isspace(line[i]))
				i++;
	if (line[i] == '\0')
	{
		free (line);
		free_env(env);
		ft_printf_fd(2, "\e[38;2;255;105;180mSashay away \x1b[m \n");
		exit (0);
	}
	if (ft_isdigit(line[i]) || line[i] == '-' || line[i] == '+')
	{
		return (handle_exit_num_arg(line, i, env));
	}
	else if (ft_isalpha(line[i]))
	{
		ft_printf_fd(STDERR_FILENO, "\033[1m\e[31mGayAsHell\x1b[m: ");
		ft_printf_fd(2, "exit: numeric argument required, sis 💅\n");
		free_env(env);
		ft_printf_fd(2, "\e[38;2;255;105;180mSashay away \x1b[m \n");
		exit(255);
	}
	return (0);
}

int	handle_exit(char *line, t_env **env)
{
	if (!line)
	{
		free_env(env);
		ft_printf_fd(2, "\e[38;2;255;105;180mSashay away 💃\x1b[m \n");
		exit(0);
	}
	if (line[4] != '\0')
		return (handle_exit_arg(line, 4, env));
	free(line);
	free_env(env);
	ft_printf_fd(2, "\e[38;2;255;105;180mSashay away 💃\x1b[m \n");
	exit(0);
	return (0);
}
