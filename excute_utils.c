/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:01:14 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 19:05:23 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_single(t_data *data, int *stdio)
{
	if (isatty(data->cmd[0].fd_list[0]) == 0)
		ft_close(data->cmd[0].fd_list[0]);
	if (isatty(data->cmd[0].fd_list[1]) == 0)
		ft_close(data->cmd[0].fd_list[1]);
	ft_close(stdio[0]);
	ft_close(stdio[1]);
}

void	multi_child(t_data *data, t_token *tmp, int index)
{
	change_termios(data);
	close_multichild(data, index);
	if (get_cmd(&data->cmd[index], tmp, data))
	{
		if (!tmp->next)
			exit(0);
		exit(1);
	}
	dup2(data->cmd[index].fd_list[0], 0);
	dup2(data->cmd[index].fd_list[1], 1);
	making_envp(data);
	exe_or_builtin(data, index);
	exit(data->return_code);
}

void	init_for_excute(t_data *data)
{
	dup2(data->cmd[0].fd_list[0], 0);
	dup2(data->cmd[0].fd_list[1], 1);
	making_envp(data);
	if (ft_strcmp(data->cmd[0].cmd_param[0], "exit") == 0)
		printf("exit\n");
}

void	close_multichild(t_data *data, int idx)
{
	if (idx == 0)
		ft_close(data->pipe1[0]);
	else if (idx != data->pipe_count)
	{
		if (idx % 2 == 1)
			ft_close(data->pipe2[0]);
		else
			ft_close(data->pipe1[0]);
	}
}

void	single_child(t_data *data)
{
	change_termios(data);
	if (execve(data->cmd[0].cmd_param[0], \
	data->cmd[0].cmd_param, data->renew_envp))
	{
		error_arg_msg(data->cmd[0].cmd_param[0]);
		if (errno == 13 || errno == 20)
			exit(126);
		else
			exit(127);
	}
}
