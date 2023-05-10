/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:29:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/10 15:51:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"

void	print_token(t_token *token);

int	main(int argc, char **argv, char *envp[])
{
	t_token	token1;
	t_token	token2;
	t_token	token3;
	t_token	token4;
	t_token	token5;
	t_token	token6;
	t_token	token7;
	t_token	token8;
	t_token	token9;
	t_token	token10;
	t_command	*head;

	token1.next = &token2;
	token2.next = &token3;
	token3.next = &token4;
	token4.next = &token5;
	token5.next = &token6;
	token6.next = &token7;
	token7.next = &token8;
	token8.next = &token9;
	token9.next = &token10;
	token10.next = NULL;

	token1.content = "echo";
	token1.token_type = COMMAND;
	token2.content = "-nnnn";
	token2.token_type = STRING;
	token3.content = "-nnn";
	token3.token_type = STRING;
	token4.content = "-n";
	token4.token_type = STRING;
	token5.content = "jhjfgjkosfkdfg";
	token5.token_type = STRING;
	token6.content = "jhjfgjkosfkdfg";
	token6.token_type = STRING;
	token7.content = "<";
	token7.token_type = LESS_THAN;
	token8.content = "src/main.c";
	token8.token_type = STRING;
	token7.content = "<";
	token7.token_type = LESS_THAN;
	token8.content = "src/ft_error.c";
	token8.token_type = STRING;
	token9.content = ">";
	token9.token_type = GREATER_THAN;
	token10.content = "test.txt";
	token10.token_type = STRING;

	argc = 1;
	argv = 0;

	print_token(&token1);
	ft_print_array(envp, 1);
	head = init_command(&token1);
	print_parser(&head);
	return (0);
}
