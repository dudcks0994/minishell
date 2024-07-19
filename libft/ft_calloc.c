/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:08:27 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ret;

	i = 0;
	ret = (void *)ft_malloc(sizeof(char) * size * count);
	if (ret == NULL)
		return (NULL);
	while (i < count * size)
		*(char *)(ret + i++) = 0;
	return (ret);
}
