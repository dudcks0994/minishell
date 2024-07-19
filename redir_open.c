/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:43:04 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/21 16:08:47 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	left_angle_open(int *fd_list, t_token *to_open)
{
	if (fd_list[0] != 0)
		ft_close(fd_list[0]);
	fd_list[0] = open(to_open->str, O_RDONLY, 0);
	if (fd_list[0] == -1)
	{
		perror(to_open->str);
		return (1);
	}
	return (0);
}

int	d_left_angle_open(int *fd_list, t_token *to_open)
{
	if (fd_list[0] != 0)
		ft_close(fd_list[0]);
	fd_list[0] = open(to_open->str, O_RDONLY, 0);
	if (fd_list[0] == -1)
	{
		perror(to_open->str);
		return (1);
	}
	unlink(to_open->str);
	return (0);
}

int	right_angle_open(int *fd_list, t_token *to_open)
{
	if (fd_list[1] != 1)
		ft_close(fd_list[1]);
	fd_list[1] = open(to_open->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_list[1] == -1)
	{
		perror(to_open->str);
		return (1);
	}
	return (0);
}

int	d_right_angle_open(int *fd_list, t_token *to_open)
{
	if (fd_list[1] != 1)
		ft_close(fd_list[1]);
	fd_list[1] = open(to_open->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_list[1] == -1)
	{
		perror(to_open->str);
		return (1);
	}
	return (0);
}
