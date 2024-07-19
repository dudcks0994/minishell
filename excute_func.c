/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:27:20 by youngcki          #+#    #+#             */
/*   Updated: 2024/07/03 14:41:37 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excute(t_data *data)
{
	if (data->heredoc_flag == 1)
	{
		data->heredoc_flag = 0;
		remove_tmplist(data);
		free_token(data->head.next);
		return ;
	}
	if (data->pipe_count == 0)
		excute_single(data);
	else
		excute_multi(data);
}

void	excute_single(t_data *data)
{
	// int	stdio[2];

	if (get_cmd(&data->cmd[0], &data->head, data))
	{
		free_token(data->head.next);
		return ;
	}
	// stdio[0] = dup(0);
	// stdio[1] = dup(1);
	init_for_excute(data);
	if (is_builtin(data->cmd[0].cmd_param[0]))
		run_builtin(data, data->cmd[0].cmd_param[0], \
		data->cmd[0].cmd_param, data->renew_envp);
	else
	{
		data->cmd[0].pid = fork();
		if (data->cmd[0].pid == 0)
			single_child(data);
		wait_all_pid(data, data->cmd, 1);
		restore_termios(data);
	}
	// dup2(stdio[0], 0);
	// dup2(stdio[1], 1);
	// close_single(data, stdio);
	free_token(data->head.next);
}

void	excute_multi(t_data *data)
{
	t_token	*cur;
	t_token	*tmp;
	int		i;

	i = 0;
	cur = data->head.next;
	while (cur)
	{
		tmp = cur;
		cur = get_list(&tmp);
		tmp = make_head_node(tmp);
		recycle_pipe(data, i);
		data->cmd[i].pid = fork();
		if (data->cmd[i].pid == 0)
			multi_child(data, tmp, i);
		free_token(tmp);
		i++;
	}
	if (i % 2 == 0)
		ft_close(data->pipe1[0]);
	else
		ft_close(data->pipe2[0]);
	wait_all_pid(data, data->cmd, data->pipe_count + 1);
	restore_termios(data);
}

void	recycle_pipe(t_data *data, int index)
{
	if (index % 2 == 0)
	{
		if (index != 0)
		{
			ft_close(data->pipe2[1]);
			ft_close(data->pipe1[0]);
		}
		if (index != data->pipe_count)
			ft_pipe(data->pipe1);
		if (index != 0)
			data->cmd[index].fd_list[0] = data->pipe2[0];
		data->cmd[index].fd_list[1] = data->pipe1[1];
	}
	else if (index % 2 == 1)
	{
		if (index != 1)
			ft_close(data->pipe2[0]);
		ft_close(data->pipe1[1]);
		if (index != data->pipe_count)
			ft_pipe(data->pipe2);
		data->cmd[index].fd_list[0] = data->pipe1[0];
		data->cmd[index].fd_list[1] = data->pipe2[1];
	}
	if (index == data->pipe_count)
		data->cmd[index].fd_list[1] = 1;
}

void	exe_or_builtin(t_data *data, int index)
{
	if (is_builtin(data->cmd[index].cmd_param[0]))
		run_builtin(data, data->cmd[index].cmd_param[0], \
		data->cmd[index].cmd_param, data->renew_envp);
	else
	{
		if (execve(data->cmd[index].cmd_param[0], \
			data->cmd[index].cmd_param, data->renew_envp))
		{
			error_arg_msg(data->cmd[index].cmd_param[0]);
			if (errno == 13 || errno == 20)
				exit(126);
			else
				exit(127);
		}
	}
}
