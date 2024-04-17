/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:07:57 by juramos           #+#    #+#             */
/*   Updated: 2024/04/17 13:27:12 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *token_list) // borrar
{
	t_token *reference = token_list;

	while (reference)
	{
		token_list = reference;
	 	while (token_list)
		{
	 		printf("value:%s type:%d\n",token_list->value, token_list->type);
	 		token_list = token_list->next;
	 	}
		reference = reference->next_cmd;
		printf("\n");
	}
}

void	print_cmd_table(t_cmd_table *cmd_table) // borrar
{
	int i = 0; 

	while (cmd_table) 
	{
		printf("CMD:%s\n",cmd_table->cmd);
		while (cmd_table->args[i])
		{
			printf("ARG%d:%s\n", i, cmd_table->args[i]);
			i++;
		}
		printf("IN:%d\n", cmd_table->in);
		printf("OUT:%d\n", cmd_table->out);
		printf("ERR:%d\n", cmd_table->err);
		i = 0;
		while (i < cmd_table->n_redirections)
		{
			printf("redir: %d type: %d value: %s\n", i, cmd_table->redirections[i]->type, cmd_table->redirections[i]->value);
			i++;
		}
		printf("nbr redir: %d\n", cmd_table->n_redirections);
		if (cmd_table->new_cmd)
			printf("new cdm TRUE\n");
		else 
			printf("new cdm FALSE\n");
		cmd_table = cmd_table->next;
		printf("\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*data;

	if (argc != 1 || argv[1])
		exit(1);
	data = init(envp);
	get_past_history(envp, data);
	// signals(false); currently compilation fails
	minishell_loop(data);
}
