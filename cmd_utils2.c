/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:30:48 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/19 17:53:22 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_has_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	make_cmd_param(char **cmd_param, t_token *cur, int param_cnt, t_data *data)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < param_cnt)
	{
		if (flag == 0)
		{
			if (is_builtin(cur->str))
				cmd_param[i] = ft_strdup(cur->str);
			else
			{
				cmd_param[i] = find_path(cur->str, data);
				if (cmd_param[i] == 0)
					return (1);
			}
			flag = 1;
		}
		else
			cmd_param[i] = ft_strdup(cur->str);
		cur = cur->next;
		i++;
	}
	return (0);
}

char	*find_path(char *cmd_name, t_data *data)
{
	char	*path_value;
	char	*tmp2;

	path_value = ft_getenv(data, "PATH");
	if (!path_value)
		return (ft_strdup(cmd_name));
	if (cmd_name[0] == '\0')
	{
		print_cnf_error(cmd_name);
		data->return_code = 127;
		return (0);
	}
	tmp2 = get_right_path(path_value, cmd_name);
	if (tmp2 == 0)
	{
		if (is_slash(cmd_name))
			return (ft_strdup(cmd_name));
		else
		{
			print_cnf_error(cmd_name);
			data->return_code = 127;
			return (0);
		}
	}
	return (tmp2);
}

char	*get_right_path(char *path_value, char *cmd_name)
{
	char	**path;
	char	*tmp;
	char	*tmp2;
	int		i;

	if (is_absolute_path(cmd_name))
		return (ft_strdup(cmd_name));
	path = ft_split(path_value, ':');
	tmp = ft_strjoin("/", cmd_name);
	i = 0;
	while (path[i])
	{
		tmp2 = ft_strjoin(path[i], tmp);
		if (access(tmp2, F_OK) != 0)
		{
			free(tmp2);
			tmp2 = 0;
		}
		else
			break ;
		i++;
	}
	free_split(path);
	free(tmp);
	return (tmp2);
}

int	is_absolute_path(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strlen(cmd_name) >= 2 && cmd_name[0] == '.' && cmd_name[1] == '/')
		return (1);
	if (cmd_name[0] == '/')
		return (1);
	return (0);
}
