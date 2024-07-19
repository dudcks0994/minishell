/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:47:46 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/13 15:50:13 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	left_angle_bracket_token(const char *s, t_token *cur)
{
	char	*str;

	str = ft_substr(s, 0, 1);
	insert_node(cur, str, TYPE_LEFT_ANGLE);
	return (0);
}

int	right_angle_bracket_token(const char *s, t_token *cur)
{
	char	*str;

	str = ft_substr(s, 0, 1);
	insert_node(cur, str, TYPE_RIGHT_ANGLE);
	return (0);
}

int	normal_token(const char *s, t_token *cur)
{
	int		i;
	char	*str;

	i = 0;
	while ((!ft_ismeta(s[i])) && s[i])
		i++;
	str = ft_substr(s, 0, i);
	insert_node(cur, str, TYPE_NORMAL);
	return (0);
}
