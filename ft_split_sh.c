/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:54:35 by  yeonwkan         #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	is_charset_sh(char w, char *set);
int	word_count_sh(char *str, char *charset);
int	word_len_sh(char *str, char *charset);

char	**ft_split_sh(char *str, char *charset)
{
	char	**ret;
	int		word;
	int		word_leng;
	int		i;
	int		j;

	i = 0;
	word = word_count_sh(str, charset);
	ret = (char **)ft_malloc(sizeof(char *) * (word + 1));
	ret[word] = 0;
	while (i < word)
	{
		j = 0;
		while (is_charset_sh(*str, charset))
			str++;
		word_leng = word_len_sh(str, charset);
		ret[i] = (char *)ft_malloc(sizeof(char) * (word_leng + 1));
		while (j < word_leng)
			ret[i][j++] = *str++;
		ret[i][j] = '\0';
		i++;
	}
	return (ret);
}

int	word_len_sh(char *str, char *charset)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (is_charset_sh(*str, charset))
			return (i);
		else
			i++;
		str++;
	}
	return (i);
}

int	word_count_sh(char *str, char *charset)
{
	int	ret;
	int	flag;

	ret = 0;
	flag = 1;
	while (*str)
	{
		if (is_charset_sh(*str, charset))
			flag = 1;
		else
		{
			if (flag == 1)
				ret++;
			flag = 0;
		}
		str++;
	}
	return (ret);
}

int	is_charset_sh(char w, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (w == set[i])
			return (1);
		i++;
	}
	return (0);
}
