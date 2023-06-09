/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/09 09:36:20 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	if (!key)
		return (NULL);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (NULL);
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free_env(&new);
			return (NULL);
		}
		new->print = 1;
	}
	new->next = NULL;
	return (new);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (*env == NULL)
	{
		*env = new;
		(*env)->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	**get_content(char *envp, char *eq)
{
	char	**tmp;

	tmp = ft_calloc(2, sizeof(char *));
	if (!tmp)
		return (NULL);
	if (eq)
	{
		tmp[0] = ft_substr(envp, 0, eq - envp);
		if (*(eq + 1))
			tmp[1] = ft_strdup(eq + 1);
		else
			tmp[1] = ft_strdup("");
	}
	else
	{
		tmp[0] = ft_strdup(envp);
		tmp[1] = NULL;
	}
	if (!tmp[0])
	{
		ft_free_array(&tmp, 2);
		return (NULL);
	}
	return (tmp);
}

char	**split_env(char *envp, int init)
{
	char	*temp;
	char	**tmp;
	int		shell_lvl;
	char	*eq;

	eq = ft_strchr(envp, '=');
	tmp = get_content(envp, eq);
	if (tmp && ft_strcmp(tmp[0], "SHLVL") == 0 && init)
	{
		temp = tmp[1];
		shell_lvl = ft_atoi(tmp[1]) + 1;
		if (shell_lvl <= 0)
			tmp[1] = ft_strdup("0");
		else
			tmp[1] = ft_itoa(shell_lvl);
		free(temp);
	}
	return (tmp);
}

void	init_env(char *envp[], t_env **env)
{
	char	**tmp;
	t_env	*new;

	while (*envp)
	{
		tmp = split_env(*envp, 1);
		if (!tmp)
			break ;
		if (!ft_strcmp(tmp[0], "OLDPWD"))
			add_env(env, NULL);
		else
		{
			new = new_env(tmp[0], tmp[1]);
			if (!new)
				break ;
			add_env(env, new);
		}
		ft_free_array(&tmp, 2);
		envp++;
	}
	new = new_env("?", "0");
	if (!new)
		ft_error(ENOMEM, "");
	add_env(env, new);
}
