/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:17 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/27 11:38:43 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_env(char *arg)
{
	size_t	i;
	size_t	len;
	size_t	eq_pos;

	if (!ft_isalpha(arg[0]) || arg[0] != '_')
		return (-1);
	i = 0;
	len = ft_strlen(arg);
	eq_pos = 0;
	while (arg[eq_pos] && arg[eq_pos] != '=')
		eq_pos++;
	if (i < eq_pos && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	return (i);
}

int	replace_env(t_ev **env, char *key, char *value)
{
	t_ev	*tmp;

	if (!env || !*env
		|| !key || !*key)
		return (1);
	tmp = find_env(env, key);
	if (!tmp)
	{
		tmp = new_env(key, value);
		if (!tmp)
			return (1);
		add_env(env, tmp);
	}
	else
	{
		free(tmp->value);
		tmp->value = value;
	}
	return (0);
}

int	ft_export(t_ev **env, t_command *cmd)
{
	size_t	i;
	size_t	elems;
	size_t	eq_pos;
	char	**env_str;
	int		ret;

	if (!cmd->params)
		return (1);
	i = 0;
	elems = ft_count_elements(cmd->params);
	while (i < elems)
	env_str = ft_split(cmd->params[i], '=');
	if (!env_str)
		return (1);
	eq_pos = invalid_env(env_str);
	if (eq_pos < 0)
		return (1);
	ret = replace_env(env, env_str[0], env_str[1]);
	ft_free_array(&env_str, 2);
	return (ret);
}
