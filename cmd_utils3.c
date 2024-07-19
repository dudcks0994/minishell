/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:31:28 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	count_white_space(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		{
			cnt++;
			while (str[i] && (str[i] == ' ' || (9 <= str[i] && str[i] <= 13)))
				i++;
		}
		else
		{
			cnt++;
			while (str[i] && (str[i] != ' ' && !(9 <= str[i] && str[i] <= 13)))
				i++;
		}
	}
	return (cnt);
}

char	*get_word(char **str)
{
	if (**str != ' ' && !(9 <= **str && **str <= 13))
		return (get_whitespace_word(str));
	else
		return (get_normal_word(str));
}

char	*get_whitespace_word(char **str)
{
	int		i;
	char	*new;

	i = 0;
	while ((*str)[i] && \
	(*str)[i] != ' ' && !(9 <= (*str)[i] && (*str)[i] <= 13))
			i++;
	new = (char *)ft_malloc(sizeof(char) * (i + 1));
	new[i] = '\0';
	i = 0;
	while (**str && **str != ' ' && !(9 <= **str && **str <= 13))
	{
		new[i] = **str;
		i++;
		(*str)++;
	}
	return (new);
}

char	*get_normal_word(char **str)
{
	int		i;
	char	*new;

	i = 0;
	while ((*str)[i] && \
	((*str)[i] == ' ' || (9 <= (*str)[i] && (*str)[i] <= 13)))
		i++;
	new = (char *)ft_malloc(sizeof(char) * (i + 1));
	new[i] = '\0';
	i = 0;
	while (**str && (**str == ' ' || (9 <= **str && **str <= 13)))
	{
		new[i] = **str;
		i++;
		(*str)++;
	}
	return (new);
}
