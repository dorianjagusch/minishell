/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:29:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/11 16:23:53 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "redirect.h"
#include "minishell.h"

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
	t_token	token11;
	t_token	token12;
	t_token	token13;
	t_command	*head;

	t_env *env;

	token1.next = &token2;
	token2.next = &token3;
	token3.next = &token4;
	token4.next = &token5;
	token5.next = &token6;
	token6.next = &token7;
	token7.next = &token8;
	token8.next = &token9;
	token9.next = &token10;
	token10.next = &token11;
	token11.next = &token12;
	token12.next = &token13;
	token13.next = NULL;

	token1.content = ft_strdup("echo");
	token1.token_type = COMMAND;
	token2.content = ft_strdup("-nnnn");
	token2.token_type = STRING;
	token3.content = ft_strdup("-nnn");
	token3.token_type = STRING;
	token4.content = ft_strdup("-n");
	token4.token_type = STRING;
	token5.content = ft_strdup(">");
	token5.token_type = GREATER_THAN;
	token6.content = ft_strdup("blabla.txt");
	token6.token_type = STRING;
	token7.content = ft_strdup("jhjfgjkosfkdfg");
	token7.token_type = STRING;
	token8.content = ft_strdup("|");
	token8.token_type = PIPE;
	token9.content = ft_strdup("<");
	token9.token_type = LESS_THAN;
	token10.content = ft_strdup("src/ft_error.c");
	token10.token_type = STRING;
	token11.content = ft_strdup("cat");
	token11.token_type = COMMAND;
	token12.content = ft_strdup(">>");
	token12.token_type = GREATER_THAN;
	token13.content = ft_strdup("test.txt");
	token13.token_type = STRING;

	argc = 1;
	argv = 0;

	print_token(&token1);
	ft_print_array(envp, 1);
	head = init_command(&token1);
	print_parser(head);
	init_env(envp, &env);
	redirect_exe(head, env);
	free_env(&env);
	free_command(&head);
	system("leaks a.out");
	return (0);
}
