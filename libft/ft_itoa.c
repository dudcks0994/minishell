/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 05:18:07 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*make_str(char *ret, long long cal, int minus, int radix);

char	*ft_itoa(int n)
{
	int			minus;
	long long	cal;
	char		*ret;
	int			radix;

	radix = 0;
	minus = 0;
	cal = n;
	if (n < 0)
		minus = 1;
	while (cal != 0)
	{
		cal /= 10;
		radix++;
	}
	if (n == 0)
		radix = 1;
	cal = n;
	ret = (char *)ft_malloc(sizeof(char) * (radix + minus + 1));
	if (ret == 0)
		return (0);
	return (make_str(ret, cal, minus, radix));
}

static char	*make_str(char *ret, long long cal, int minus, int radix)
{
	if (!cal)
		ret[0] = '0';
	if (minus)
	{
		ret[0] = '-';
		cal *= -1;
	}
	ret[radix + minus] = '\0';
	while (cal != 0)
	{
		radix--;
		ret[minus + radix] = cal % 10 + '0';
		cal /= 10;
	}
	return (ret);
}
