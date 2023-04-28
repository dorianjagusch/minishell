/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_printers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:17 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/28 18:24:38 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*cpy_env(t_env **env)
{
	t_env	*new;
	t_env	*tmp;
	t_env	*list;

	if (!env || !*env)
		return (NULL);
	list = ft_calloc(1, sizeof(t_env));
	list->key = (*env)->key;
	list->value = (*env)->value;
	tmp = (*env)->next;
	while (tmp)
	{
		if (tmp->eq == 1)
		{
			new = ft_calloc(1, sizeof(t_env));
			if (!new)
				break ;
			new->key = tmp->key;
			new->value = tmp->value;
		}
		tmp = tmp->next;
	}
	if (!new)
		free(&list);
	return (list);
}

void	swap_env(t_env **env, t_env *e1, t_env *e2)
{
	t_env	*tmp;
	t_env	*tmp2;
	//What happens when e1 or e2 is at env?
	//What if they are adjacent?

	if (!e1 || !e2 || e1 == e2)
		return ;
	tmp = find_env(env, e1, 1);
	tmp2 = find_env(env, e2, 1);
	tmp2->next = e1;
	tmp->next = e2;
	tmp = tmp->next->next;
	e2->next = e1->next;
	e1->next = tmp;
}

void	sort_env(t_env **env)
{
	t_env	*tmp1;
	t_env	*tmp2;

	if (!env || !(*env) || !(*env)->next)
		return ;
	tmp1 = *env;
	while (tmp1)
	{
		tmp2 = (*env)->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp1->key, tmp2->key) > 0)
				swap_env(env, tmp1, tmp2);
			tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

int	print_export(t_env **env, t_command *cmd)
{
	t_env	*cpy;
	t_env	*tmp;

	cpy = copy_env(env);
	sort_env(&cpy);
	tmp = cpy;
	while (cpy)
	{
		ft_printf_fd(cmd->out_fd[1],
			"declare -x %s=\"%s\"\n", cpy->key, cpy->value);
		cpy = cpy->next;
	}
	ft_free(cpy);
	return (0);
}
