/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_systemcall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:12:59 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 15:43:31 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

void	*ft_malloc(size_t size)
{
	void	*new;

	new = malloc(size);
	if (new == 0)
		exit(1);
	return (new);
}

int	ft_open(char *filename, int option1, int option2)
{
	int	ret;

	if (option1 == O_RDONLY)
		ret = open(filename, option1);
	else
		ret = open(filename, option1, option2);
	if (ret < 0)
		exit(1);
	return (ret);
}

void	ft_close(int fd)
{
	if (close(fd) < 0)
		exit(1);
}

void	ft_pipe(int *fd)
{
	if (pipe(fd) < 0)
		exit(1);
}
