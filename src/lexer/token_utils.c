/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/28 16:32:16 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//comments ?
char	*replace_content(char *content, int start, char *new, char *str)
{
	int		i;
	int		end;
	int		j;
	int		len;

	i = -1;
	j = -1;
	end = ft_strlen(str);
	len = -1;
	while (++i < start)
		new[i] = content[++len];
	while (++i < end)
		new[i] = str[++j];
	end = ft_strlen(content);
	while (++i < end)
		new[i] = content[++len];
	new[i] = 0;
  return (new);
}
//Possibly from here everthing below deleted. For some reason the following code was in develop but not in your parser branch


//strings include srounding single or double quotos
int	get_string(t_token **tokens, char *line, int quote)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] != quote)
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	if (!str)
		retun (EXIT_FAILURE);
	ft_strlcpy(str, line, i + 2);
	if (add_token(tokens, new_token(str, STRING)) == EXIT_FAILURE)
	{
		free(str);
		retun (EXIT_FAILURE);
	}
	free(str);
	return (i + 1);
}

int	get_command(t_token **tokens, char *line) //said "comment" I changed it to command
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] == '-')
		i++;
	while (line[i] && line[i] != '\t' && line[i] != ' ' && line[i] != '|'
		&& line[i] != '\"' && line[i] != '\'')
		i++;
	str = ft_calloc((i + 1), sizeof(char));
	if (!str)
		retun (EXIT_FAILURE);
	ft_strlcpy(str, line, i + 1);
	if (add_token(tokens, new_token(str, COMMAND)) == EXIT_FAILURE)
	{
		free(str);
		retun (EXIT_FAILURE);
	}
	free(str);
	return (i - 1);
}

t_token	*new_token(char *content, int token_type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!new->content)
	{
		return (NULL);
	}
	new->token_type = token_type;
	new->next = NULL;
	return (new);
}
