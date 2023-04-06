/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/05 16:33:55 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ev	*new_ev(char *key, char *value)
{
	t_ev	*new;

	new = malloc(sizeof(t_ev));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	add_ev(t_ev **env, t_ev *new)
{
	t_ev	*tmp;

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

void	set_envp(char **envp, t_ev **env)
{
	int		i;
	char	**temp;

	i = 0;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		add_ev(env, new_ev(temp[0], temp[1]));
		free(temp[0]);
		free(temp[1]);
		free(temp);
		i++;
	}
}
