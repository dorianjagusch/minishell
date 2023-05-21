/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/21 20:08:39 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens)
		return ;
	while (*tokens != NULL)
	{
		tmp = *tokens;
		(*tokens) = (*tokens)->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
	free ((*tokens));
}

void	free_command(t_command **commands)
{
	t_command	*tmp;

	if (!commands || !*commands)
		return ;
	tmp = *commands;
	while (tmp->next != NULL)
		free_command(&(tmp->next));
	if (tmp->command)
		free(tmp->command);
	if (tmp->params)
		ft_free_array(&tmp->params, tmp->n_params);
	if (tmp->infile)
		free(tmp->infile);
	if (tmp->outfile)
		free(tmp->outfile);
	free (*commands);
	*commands = NULL;
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	tmp = *env;
	while (tmp->next != NULL)
		free_env(&(tmp->next));
	if (tmp->key)
		free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	free(*env);
	*env = NULL;
}

void	ft_clear(t_command **command, int **pids, int **fds)
{
	free_command(command);
	ft_free(pids);
	ft_free(fds);
}