/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:22:01 by yeonwkan          #+#    #+#             */
/*   Updated: 2024/07/15 14:44:58 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (((9 <= c && c <= 13) || (c == ' ')));
}

int	ft_ismeta(char c)
{
	int	ret;

	ret = 0;
	ret += ft_isspace(c);
	ret += (c == '\"' || c == '\'' || c == '<' || \
	c == '>' || c == '|');
	return (ret);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	if (s1 == 0 || s2 == 0)
		return (-1);
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			break ;
		i++;
	}
	if (s1[i] == s2[i] && s1[i] == '\0')
		return (0);
	else
		return (s1[i] - s2[i]);
}

int	is_merge_quote(t_token *cur)
{
	int	cur_t;
	int	next_t;

	cur_t = cur->type;
	next_t = cur->next->type;
	if (((cur_t == TYPE_D_QUOTE || cur_t == TYPE_S_QUOTE) && next_t == TYPE_NORMAL) || ((cur_t == TYPE_NORMAL) && \
		(next_t == TYPE_D_QUOTE || next_t == TYPE_S_QUOTE)) || \
		((cur_t == TYPE_D_QUOTE || cur_t == TYPE_S_QUOTE) && \
		(next_t == TYPE_D_QUOTE || next_t == TYPE_S_QUOTE)) || \
		(cur_t == TYPE_NORMAL && next_t == TYPE_NORMAL))
		return (1);
	return (0);
}

int	is_redirection(t_token *cur)
{
	int	cur_t;

	cur_t = cur->type;
	if (cur_t == TYPE_RIGHT_ANGLE || cur_t == TYPE_D_RIGHT_ANGLE \
		|| cur_t == TYPE_LEFT_ANGLE || cur_t == TYPE_D_LEFT_ANGLE)
		return (1);
	return (0);
}
