/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:22:55 by juramos           #+#    #+#             */
/*   Updated: 2024/05/14 12:14:31 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signal_vars(void)
{
	g_global.stop_heredoc = 0;
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	g_global.reset_pipes = 1;
}

int	get_sh_lvl(char **envp)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (envp[i] && ft_strncmp(envp[i], "SHLVL=", 6))
		i++;
	if (envp[i])
	{
		res = ft_atoi(envp[i] + 6);
		return (res);
	}
	else 
		return (1);
}

t_minishell	*init(char **envp)
{
	t_minishell	*data;

	data = (t_minishell *)malloc(sizeof(t_minishell));
	data->token_list = NULL;
	data->cmd_table = NULL;
	data->line = NULL;
	data->pids = NULL;
	data->fd_in = dup(STDIN_FILENO);
	data->fd_out = dup(STDOUT_FILENO);
	data->sh_lvl = get_sh_lvl(envp);
	data->env_vars = ft_arrdup(envp);
	data->local_vars = NULL;
	data->export_vars = ft_arrdup(data->env_vars);
	if (!data->env_vars)
		error(data, "Could not alloc memory for env. vars.");
	data->pwd = ft_strdup(my_getenv("PWD", data->env_vars));
	if (!data->pwd)
		error(data, "Could not alloc memory for pwd");
	data->old_pwd = ft_strdup(my_getenv("OLDPWD", data->env_vars));
	if (!data->old_pwd)
		error(data, "Could not alloc memory for old pwd");
	g_global.error_num = 0;
	init_signal_vars();
	return (data);
}
