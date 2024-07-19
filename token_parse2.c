/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:06:50 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/13 15:50:47 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_token(const char *s, t_token *cur)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	str = ft_substr(s, 0, i);
	insert_node(cur, str, TYPE_WHITE_SPACE);
	return (0);
}

int	quote_token(const char *s, t_token *cur, char set)
{
	int		i;
	int		type;
	char	*str;

	i = 1;
	while (s[i] != set)
	{
		if (!s[i])
			return (1);
		i++;
	}
	if (set == '\'')
		type = TYPE_S_QUOTE;
	if (set == '\"')
		type = TYPE_D_QUOTE;
	str = ft_substr(s, 0, i + 1);
	insert_node(cur, str, type);
	return (0);
}

int	pipe_token(const char *s, t_token *cur, t_data *data)
{
	char	*str;

	str = ft_substr(s, 0, 1);
	insert_node(cur, str, TYPE_PIPE);
	data->pipe_count++;
	return (0);
}
