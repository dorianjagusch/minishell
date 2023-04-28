/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/27 13:18:01 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ev	*new_env(char *key, char *value)
{
	t_ev	*new;

	if (!key)
		return (-1);
	new = malloc(sizeof(t_ev));
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

void	add_env(t_ev **env, t_ev *new)
{
	t_ev	*tmp;

	if (!env)
		return ;
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

t_ev	*find_env(t_ev **env, char *variable)
{
	t_ev	*tmp;

	if (!env || !*env || !variable || !(*variable))
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(variable, tmp->key) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

char	*find_value(t_ev **env, char *variable)
{
	t_ev	*tmp;

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

void	init_env(char **envp, t_ev **env)
{
	int		i;
	char	**temp;
	char	hold;

	i = 0;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		if (ft_strcmp(temp[0], "SHLVL") == 0)
		{
			hold = temp[1];
			temp[1] = ft_itoa(ft_atoi(temp[1]) + 1);
			free (hold);
		}
		add_ev(env, new_ev(temp[0], temp[1]));
		free(temp[0]);
		free(temp[1]);
		free(temp);
		i++;
	}
}
