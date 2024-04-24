/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/24 12:23:56 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void		minishell_loop(t_minishell *data);
static void	create_main_fork(t_minishell *data);
void		reset_loop(t_minishell *data);
static void	parse_data(t_minishell *data);

static void	parse_data(t_minishell *data)
{
	t_token		*token_tmp;

	join_history(data->line, data, data->env_vars);
	lexer(data->line, &(data->token_list));
	token_tmp = data->token_list;
	parser(&(data->cmd_table), &(data->token_list));
	clean_token_list(&token_tmp);
}

static void	create_main_fork(t_minishell *data)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		executor(data);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status);
}

void	minishell_loop(t_minishell *data)
{
	data->line = readline("\e[1;34m""minishell> ""\e[m");
	if (!data->line)
		exit(EXIT_SUCCESS);
	else if (check_spaces(data->line) || ft_strlen(data->line) == 0)
		reset_loop(data);
	else
	{
		parse_data(data);
		local_variables(data);
		create_main_fork(data);
		reset_loop(data);
	}
}

void	reset_loop(t_minishell *data)
{
	if (data->cmd_table)
		clean_cmd_table_list(&(data->cmd_table));
	if (data->line || ft_strlen(data->line))
		free(data->line);
	minishell_loop(data);
}
