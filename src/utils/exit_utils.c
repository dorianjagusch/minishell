/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:13:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/09 14:47:24 by djagusch         ###   ########.fr       */
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

int	handle_exit_num_arg(char *line, size_t i, t_env **env)
{
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
		ft_printf_fd(2, "exit: : too many arguments, sis 💅\n");
		free(line);
		g_info.exit_value = 1;
		set_exit_value(env);
		return (1);
	}
	else
	{
		free(line);
		free_env(&g_info.env);
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
		free_env(&g_info.env);
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
		free_env(&g_info.env);
		ft_printf_fd(2, "\e[38;2;255;105;180mSashay away \x1b[m \n");
		exit(255);
	}
	return (0);
}

int	handle_exit(char *line, t_env **env)
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
