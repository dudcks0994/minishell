/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:27:11 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/12 18:32:11 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_atol(char *str, int *flag)
{
	int				minus;
	long			ret;
	unsigned long	cal;

	minus = 1;
	ret = 0;
	cal = 0;
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	multiply_num(&cal, str, flag, minus);
	if (*flag)
		return (0);
	ret = cal * minus;
	return (ret);
}

void	multiply_num(unsigned long *cal, char *str, int *flag, int minus)
{
	while (1)
	{
		if (!('0' <= *str && *str <= '9'))
		{
			*flag = 1;
			return ;
		}
		*cal *= 10;
		*cal += *str - '0';
		if (*cal > 9223372036854775808ULL || \
		(minus > 0 && *cal == 9223372036854775808ULL))
		{
			*flag = 1;
			return ;
		}
		str++;
		if (!*str)
			return ;
	}
}
