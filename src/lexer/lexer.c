/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/27 16:47:11 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_content(t_token **token, int start, t_env **env)
{
	int		end;
	int		i;
	char	*str;
	char	*new;

	end = start;
	i = 0;
	while (ft_isalnum(token->content[end]) && token->content[end])
	{
		str[i] = token->content[end];
		end++;
	}
	str = find_env(env, str); //return null if it is not found in env
	if (str)
	{
		i = ft_strlen(token->content) + 1;
		new = ft_calloc(i * 1);
		if (!new)
			return (NULL);
		new = replace_content(token->content, start, &new, str);
		free(token->content);
		token->content = new;
	}
	return (content);
}

int	expander(t_token **tokens, t_env **env)
{
	t_token	*temp;
	int		i;

	temp = *tokens;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '$')
			{
				if (tmp->content[0] != '\'')
				{
					tmp->content = expand_content(&tmp, i, env);
					if (tmp->content == NULL)
						return (EXIT_FAILURE);
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	init_lexer(char *line, t_token	**tokens)
{
	int		i;
	int		indicator;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		indicator = i;
		else if (line[i] == '\"')
			i += get_string(&tokens, &line[i], '\"');
		else if (line[i] == '\'')
			i += get_string(&tokens, &line[i], '\'');
		else if (line[i] == '|')
			i += add_token(&tokens, new_token("|", PIPE));
		else if (line[i] == '>')
			i += add_token(&tokens, new_token(">", GREATER_THAN));
		else if (line[i] == '<')
			i += add_token(&tokens, new_token("<", LESS_THAN));
		else if (ft_isprint(line[i]) && line[i] != '|' && line[i] != ';')
			i += get_command(&tokens, &line[i]);
		if (indicator > i)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	retokenizer(t_token **tokens, t_env **env)
{
	expander(tokens, envp);
	//get rid of extra quotes
	return (EXIT_SUCCESS);
}
