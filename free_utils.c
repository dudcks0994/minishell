/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:37:29 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/20 17:57:42 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_full_sentence(t_data *data)
{
	int	i;

	i = 0;
	data->pipe_count = 0;
	data->head.next = 0;
	if (data->cmd != 0)
		free_cmd(data);
}

void	free_token(t_token *cur)
{
	t_token	*next;

	while (cur)
	{
		next = cur->next;
		if (cur->str)
			free(cur->str);
		free(cur);
		cur = next;
	}
}

void	free_cmd(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->pipe_count + 1)
	{
		if (data->cmd[i].cmd_param != 0)
		{
			j = 0;
			while (data->cmd[i].cmd_param[j])
			{
				free(data->cmd[i].cmd_param[j]);
				j++;
			}
			free(data->cmd[i].cmd_param);
			i++;
		}
		else
			break ;
	}
	free(data->cmd);
	data->cmd = 0;
}
