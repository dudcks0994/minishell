/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonwkan <yeonwkan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:13:43 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/08 16:38:27 by yeonwkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*quote_arrange(t_token *cur)
{
	char	*old;

	if (cur->type == TYPE_D_QUOTE || cur->type == TYPE_S_QUOTE)
	{
		old = cur->str;
		cur->str = ft_substr(cur->str, 1, ft_strlen(cur->str) - 2);
		free(old);
	}
	cur = cur->next;
	return (cur);
}

t_token	*quote_merge(t_token *cur)
{
	if (!cur->next)
		return (cur->next);
	if (is_merge_quote(cur))
	{
		cur->str = ft_strjoin3(cur->str, cur->next->str);
		delete_node(cur->next);
	}
	else
		cur = cur->next;
	return (cur);
}
