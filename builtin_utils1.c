/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 01:44:24 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/13 17:32:21 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	if (!ft_strcmp(cmd_name, "echo"))
		return (1);
	else if (!ft_strcmp(cmd_name, "env"))
		return (1);
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd_name, "cd"))
		return (1);
	else if (!ft_strcmp(cmd_name, "exit"))
		return (1);
	else if (!ft_strcmp(cmd_name, "export"))
		return (1);
	else if (!ft_strcmp(cmd_name, "unset"))
		return (1);
	return (0);
}

void	run_builtin(t_data *data, char *cmd_name, char **cmd_param, char **envp)
{
	if (!ft_strcmp(cmd_name, "echo"))
		echo_sh(data, cmd_param);
	else if (!ft_strcmp(cmd_name, "env"))
		env_sh(data, envp);
	else if (!ft_strcmp(cmd_name, "pwd"))
		pwd_sh(data);
	else if (!ft_strcmp(cmd_name, "cd"))
		cd_sh(data, cmd_param[1]);
	else if (!ft_strcmp(cmd_name, "exit"))
		exit_sh(data, cmd_param);
	else if (!ft_strcmp(cmd_name, "export"))
		export_sh(data, cmd_param);
	else if (!ft_strcmp(cmd_name, "unset"))
		unset_sh(data, cmd_param);
}

void	pwd_process(char *path, t_env_list *pwd, char *new_path)
{
	if (new_path)
	{
		free(pwd->value);
		pwd->value = new_path;
	}
	else
	{
		print_not_access_parent();
		if (pwd->value[ft_strlen(pwd->value) - 1] != '/')
			pwd->value = ft_strjoin(pwd->value, "/");
		pwd->value = ft_strjoin3(pwd->value, path);
	}
}

void	check_free(char *key, char *value, char *make)
{
	if (key)
		free(key);
	if (value)
		free(value);
	if (make)
		free(make);
}

void	env_process(t_data *data, char *key, char *value, char *param)
{
	char		*old;
	t_env_list	*find;

	if (ft_strcmp(key, "_"))
	{
		find = ft_getenv_ptr(data, key);
		if (find)
		{
			old = find->value;
			find->value = ft_strdup(value);
			if (old)
				free(old);
		}
		else
		{
			if (!value && param[ft_strlen(param) - 1] == '=')
				add_env_node(data, ft_strdup(key), ft_strdup(""));
			else
				add_env_node(data, ft_strdup(key), ft_strdup(value));
		}
	}
}
