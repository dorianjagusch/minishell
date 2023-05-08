/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/08 14:40:28 by djagusch         ###   ########.fr       */
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

static char	**split_env(char *envp)
{
	char	**tmp;
	char	*hold;
	char	*eq;

	eq = ft_strchr(envp, '=');
	*eq = 0;
	tmp = malloc(sizeof(char *) * 2);
	if (!tmp)
		return (NULL);
	tmp[0] = ft_strdup(envp);
	tmp[1] = ft_strdup(eq + 1);
	if (!tmp[0] || !tmp[1])
		return (NULL);
	if (tmp && ft_strcmp(tmp[0], "SHLVL") == 0)
	{
		hold = tmp[1];
		tmp[1] = ft_itoa(ft_atoi(tmp[1]) + 1);
		free(hold);
	}
	return (tmp);
}

void	init_env(char **envp, t_env **env)
{
	int		i;
	char	**tmp;
	t_env	*new;

	i = 0;
	while (envp[i])
	{
		tmp = split_env(envp[i]);
		if (!tmp)
			break ;
		new = new_env(tmp[0], tmp[1]);
		if (!new)
			break ;
		add_env(env, new);
		i++;
		ft_free_array(&tmp, 2);
	}
}
