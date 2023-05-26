/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:29:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/26 15:11:36 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "redirect.h"

void	print_token(t_token *token);

int	main(int argc, char **argv, char *envp[])
{
	t_token		token1;
	t_token		token2;
	t_token		token3;
	t_token		token4;
	t_token		token5;
	t_token		token6;
	t_token		token7;
	t_token		token8;
	t_token		token9;
	t_token		token10;
	t_token		token11;
	t_token		token12;
	t_token		token13;
	t_token		token14;
	t_token		token15;
	t_token		token16;
	t_token		token17;
	// t_token		token18;
	// t_token		token19;
	// t_token		token20;
	// t_token		token21;
	// t_token		token22;
	// t_token		token23;
	t_command	*head;

	t_env *env = NULL;

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
	token13.next = &token14;
	token14.next = &token15;
	token15.next = &token16;
	token16.next = &token17;
	token17.next = NULL ; //&token18;
	// token18.next = &token19;
	// token19.next = &token20;
	// token20.next = &token21;
	// token21.next = &token22;
	// token22.next = &token23;
	// token23.next = NULL;

	token1.content = ft_strdup("echo");
	token1.token_type = COMMAND;
	token2.content = ft_strdup("-nnnn");
	token2.token_type = STRING;
	token3.content = ft_strdup("-nmn");
	token3.token_type = STRING;
	token4.content = ft_strdup("-n");
	token4.token_type = STRING;
	token5.content = ft_strdup(">");
	token5.token_type = GREATER_THAN;
	token6.content = ft_strdup("test.txt");
	token6.token_type = STRING;
	token7.content = ft_strdup("jhjfgjkosfkdfg");
	token7.token_type = STRING;
	token8.content = ft_strdup("|");
	token8.token_type = PIPE;
	token9.content = ft_strdup("<");
	token9.token_type = LESS_THAN;
	token10.content = ft_strdup("Makefile");
	token10.token_type = STRING;
	token11.content = ft_strdup("cat");
	token11.token_type = COMMAND;
	token12.content = ft_strdup(">>");
	token12.token_type = GREATER_GREATER;
	token13.content = ft_strdup("test2.txt");
	token13.token_type = STRING;
	token14.content = ft_strdup("|");
	token14.token_type = PIPE;
	token15.content = ft_strdup("env");
	token15.token_type = COMMAND;
	token16.content = ft_strdup(">>");
	token16.token_type = GREATER_GREATER;
	token17.content = ft_strdup("test.txt");
	token17.token_type = STRING;
	// token18.content = ft_strdup("|");
	// token18.token_type = PIPE;
	// token19.content = ft_strdup("cat");
	// token19.token_type = COMMAND;
	// token20.content = ft_strdup(">>");
	// token20.token_type = GREATER_GREATER;
	// token21.content = ft_strdup("test1.txt");
	// token21.token_type = STRING;
	// token22.content = ft_strdup("<");
	// token22.token_type = LESS_THAN;
	// token23.content = ft_strdup("test.txt");
	// token23.token_type = STRING;


	argc = 1;
	argv = 0;

	head = init_command(&token1, 0);
	init_env(envp, &env);
	redirect_exe(head, env);
	printf("Left execution\n");
	free_env(&env);
	printf("Env freed\n");
	return (0);
}
