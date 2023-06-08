/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/08 13:43:30 by djagusch         ###   ########.fr       */
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
	*env = NULL;
}

void	ft_clear_everything(t_info *g_info)
{
	if ((*g_info).tokens)
		free_tokens(&((*g_info).tokens));
	(*g_info).tokens = NULL;
	if ((*g_info).commands)
		free_command(&((*g_info).commands));
	(*g_info).commands = NULL;
	if ((*g_info).line)
		free((*g_info).line);
	(*g_info).line = NULL;
	if ((*g_info).fds)
		ft_free_int_array(&((*g_info).fds), (*g_info).n_cmd);
	(*g_info).fds = NULL;
	if ((*g_info).pids)
		free((*g_info).pids);
	(*g_info).pids = NULL;
}
