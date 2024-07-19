/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:03:28 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	char	*dup;

	if (!s1)
		return (0);
	dup = (char *)ft_malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (dup == 0)
		return (0);
	ret = dup;
	while (*s1)
		*dup++ = *s1++;
	*dup = '\0';
	return (ret);
}
