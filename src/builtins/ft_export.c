/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:17 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/09 15:41:53 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export(t_env **env, t_command *cmd, int out_fd)
{
	t_env	*tmp;

	(void) cmd;
	tmp = *env;
	while (tmp)
	{
		if (tmp->key[0] != '?' && tmp->print)
		{
			ft_printf_fd(out_fd, "declare -x %s", tmp->key);
			if (tmp->value)
			{
				if (tmp->value[0])
					ft_printf_fd(out_fd, "=\"%s\"", tmp->value);
				if (!tmp->value[0])
					ft_printf_fd(out_fd, "=\"\"", tmp->value);
			}
			ft_printf_fd(out_fd, "\n");
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	valid_env(char *arg)
{
	int	i;
	int	eq_pos;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (-1);
	i = 0;
	eq_pos = 0;
	while (arg[eq_pos] && arg[eq_pos] != '=')
		eq_pos++;
	while (i < eq_pos && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (i == eq_pos)
		return (i);
	return (-1);
}

int	replace_value(t_env *env, char *value)
{
	if (value)
	{
		if (env->value)
			free(env->value);
		env->value = ft_strdup(value);
		if (!env->value && value)
		{
			ft_clear_everything(&g_info);
			return (1);
		}
	}
	return (0);
}

int	replace_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	if (!env || !*env
		|| !key || !*key)
		return (-1);
	tmp = find_env(env, key, 0);
	if (!tmp)
	{
		tmp = new_env(key, value);
		if (!tmp)
			return (-1);
		add_env(env, tmp);
	}
	else
		if (replace_value(tmp, value))
			return (1);
	tmp->print = 1;
	return (0);
}

int	ft_export(t_env **env, t_command *cmd, int out_fd)
{
	size_t	i;
	size_t	elems;
	char	**env_str;
	int		ret;

	if (!cmd || !cmd->params)
		return (1);
	i = 0;
	elems = ft_count_elements(cmd->params);
	if (elems == 1)
		return (print_export(env, cmd, out_fd));
	while (++i < elems)
	{
		env_str = split_env(cmd->params[i], 0);
		if (!env_str)
			return (1);
		if (valid_env(cmd->params[i]) >= 0)
			ret = replace_env(env, env_str[0], env_str[1]);
		else
			ft_error(ARGERR, env_str[0]);
		ft_free_array(&env_str, 2);
	}
	return (ret);
}
