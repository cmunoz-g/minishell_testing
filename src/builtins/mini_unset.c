#include "minishell.h"

int	get_nbr_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	get_equal_sign(char *variable)
{
	int	i;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	return (i);
}

int	is_env(char *variable, char **env)
{
	int	i;
	int	equal_pos;

	i = 0;
	equal_pos = 0;
	while (env[i])
	{
		equal_pos = get_equal_sign(env[i]);
		if (!ft_strncmp(variable, env[i], equal_pos)) 
			return (0);
		i++;
	}
	return (1);
}

char	**unset_env(char *variable, char **env, t_minishell *data) 
{
	char	**new_env;
	int		nbr_env;
	int		i;
	int		j;
	int		equal_pos;

	i = 0;
	j = 0;
	nbr_env = get_nbr_env(env);
	new_env = (char **)malloc(sizeof(char *) * (nbr_env));
	if (!new_env)
		error(data, "Memory problems in mini_unset");
	while (i < nbr_env && env[i])
	{
		equal_pos = get_equal_sign(env[i]);
		if (ft_strncmp(variable, env[i], equal_pos))
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
				(free_arr(new_env), error(data, "Memory problems in mini_unset"));
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	mini_unset(t_minishell *data)
{
	int		i;
	char	**new_env;

	i = 0;
	while (data->cmd_table->args[i])
	{
		if (!is_env(data->cmd_table->args[i], data->env_vars))
		{
			new_env = unset_env(data->cmd_table->args[i], data->env_vars, data);
			free_arr(data->env_vars);
			data->env_vars = new_env;
		}
		// Gestionar variables locales

		// else
		// {

		// }
		i++;
	}
	return (0);
}
