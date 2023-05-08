/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_printers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:17 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/08 14:43:54 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*copy_env(t_env **env)
{
	t_env	*tmp;
	t_env	*list;
	t_env	*new;

	if (!env || !*env)
		return (NULL);
	list = NULL;
	add_env(&list, new_env((*env)->key, (*env)->value));
	if (!list)
		return (list);
	tmp = list->next;
	while (tmp)
	{
		new = new_env(tmp->key, tmp->value);
		if (!new)
		{
			free_env(&list);
			return (NULL);
		}
		add_env(&list, new);
		tmp = tmp->next;
	}
	return (list);
}

t_env	**swap_env(t_env **env, t_env *e1, t_env *e2)
{
	t_env	*tmp;
	t_env	*tmp2;
	t_env	**head;

	if (!e1 || !e2 || e1 == e2)
		return (NULL);
	head = env;
	if (e1 == *head)
		head = &e2;
	tmp = find_env(env, e1->key, 1);
	tmp2 = find_env(env, e2->key, 1);
	tmp2->next = e1;
	tmp->next = e2;
	tmp2 = e2->next;
	e2->next = e1->next;
	e1->next = tmp2;
	return (head);
}

void	sort_env(t_env **env)
{
	t_env	*tmp1;
	t_env	*tmp2;
	t_env	**head;

	if (!env || !(*env) || !(*env)->next)
		return ;
	head = env;
	tmp1 = *env;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp1->key, tmp2->key) > 0)
				head = swap_env(head, tmp1, tmp2);
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

int	print_export(t_env **env, t_command *cmd)
{
	t_env	*cpy;

	cpy = copy_env(env);
	if (!cpy)
		return (EXIT_FAILURE);
	sort_env(&cpy);
	while (cpy)
	{
		ft_printf_fd(cmd->fds[1],
			"declare -x %s=\"%s\"\n", cpy->key, cpy->value);
		cpy = cpy->next;
	}
	free_env(&cpy);
	return (EXIT_SUCCESS);
}
