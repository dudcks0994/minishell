/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 05:43:26 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all_pid(t_data *data, t_cmd *cmd, int proc_cnt)
{
	int	i;
	int	cnt;
	int	*ret_code;

	i = 0;
	cnt = 0;
	data = (t_data *)data;
	cmd = (t_cmd *)cmd;
	ret_code = (int *)ft_malloc(sizeof(int) * proc_cnt);
	while (1)
	{
		if (cmd[i].pid && waitpid(cmd[i].pid, &ret_code[i], WNOHANG))
		{
			cmd[i].pid = 0;
			cnt++;
		}
		i++;
		if (cnt == proc_cnt)
			break ;
		if (i == proc_cnt)
			i = 0;
	}
	data->return_code = WEXITSTATUS(ret_code[proc_cnt - 1]);
	free(ret_code);
}
