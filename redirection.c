/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 04:23:48 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/19 17:46:51 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirection(t_token *cur, int *fd_list, t_data *data)
{
	int	flag;

	flag = 0;
	while (cur)
	{
		if (is_redirection(cur))
		{
			if (cur->next->type == TYPE_WHITE_SPACE)
				flag = set_fd(fd_list, cur->next->next, data, cur->type);
			else
				flag = set_fd(fd_list, cur->next, data, cur->type);
		}
		if (flag)
		{
			data->return_code = 1;
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int	set_fd(int *fd_list, t_token *to_open, t_data *data, int type)
{
	int	flag;

	flag = check_ambiguous(to_open, to_open->str, data);
	if (flag)
	{
		printf("%s : ambiguous redirection\n", to_open->str);
		return (1);
	}
	if (type == TYPE_LEFT_ANGLE)
		if (left_angle_open(fd_list, to_open))
			return (1);
	if (type == TYPE_D_LEFT_ANGLE)
		if (d_left_angle_open(fd_list, to_open))
			return (1);
	if (type == TYPE_RIGHT_ANGLE)
		if (right_angle_open(fd_list, to_open))
			return (1);
	if (type == TYPE_D_RIGHT_ANGLE)
		if (d_right_angle_open(fd_list, to_open))
			return (1);
	return (0);
}

int	check_ambiguous(t_token *to_open, char *str, t_data *data)
{
	char	*ret;
	int		flag;

	flag = 0;
	ret = calloc(1, 1);
	iter_str(str, data, &ret, &flag);
	if (flag && !ft_strlen(ret))
		return (1);
	free(to_open->str);
	to_open->str = ret;
	return (0);
}
