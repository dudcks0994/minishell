/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ctl_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonwkan <yeonwkan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:50:07 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/09 14:51:27 by yeonwkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*merge_redirection(t_token *cur)
{
	if (!cur->next)
		return (cur->next);
	if (cur->type == TYPE_LEFT_ANGLE && cur->next->type == TYPE_LEFT_ANGLE)
		same_direction_merge(cur);
	else if (cur->type == TYPE_RIGHT_ANGLE && \
		cur->next->type == TYPE_RIGHT_ANGLE)
		same_direction_merge(cur);
	else
		cur = cur->next;
	return (cur);
}

void	same_direction_merge(t_token *cur)
{
	if (cur->type == TYPE_LEFT_ANGLE)
	{
		cur->str = ft_strjoin3(cur->str, cur->next->str);
		delete_node(cur->next);
		cur->type = TYPE_D_LEFT_ANGLE;
	}
	else if (cur->type == TYPE_RIGHT_ANGLE)
	{
		cur->str = ft_strjoin3(cur->str, cur->next->str);
		delete_node(cur->next);
		cur->type = TYPE_D_RIGHT_ANGLE;
	}
}
