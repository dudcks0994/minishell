/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:32:50 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/13 17:33:09 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option(char *str, char *set)
{
	int	i;
	int	j;
	int	flag;

	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		j = 0;
		flag = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				flag = 1;
			j++;
		}
		if (!flag)
			return (0);
		i++;
	}
	return (1);
}
