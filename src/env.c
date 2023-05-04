/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/03 17:35:40 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	if (!key)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (*env == NULL)
		*env = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*find_env(t_env **env, char *key, int predecessor)
{
	t_env	*tmp;

	if (!env || !*env || !key || !(*key))
		return (NULL);
	tmp = *env;
	if (!predecessor)
	{
		while (tmp)
		{
			if (ft_strcmp(key, tmp->key) == 0)
				break ;
			tmp = tmp->next;
		}
	}
	else
	{
		while (ft_strcmp(key, tmp->key) != 0 && tmp && tmp->next)
		{
			if (ft_strcmp(key, tmp->next->key) == 0)
				break ;
			tmp = tmp->next;
		}
	}
	return (tmp);
}

char	*find_value(t_env **env, char *variable)
{
	t_env	*tmp;

	if (!env || !*env || !variable || !(*variable))
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(variable, tmp->key) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp->value);
}

void	init_env(char **envp, t_env **env)
{
	int		i;
	char	**temp;
	char	*hold;

	i = 0;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		if (ft_strcmp(temp[0], "SHLVL") == 0)
		{
			hold = temp[1];
			temp[1] = ft_itoa(ft_atoi(temp[1]) + 1);
			free(hold);
		}
		add_env(env, new_env(temp[0], temp[1]));
		free(temp[0]);
		free(temp[1]);
		free(temp);
		i++;
	}
}
