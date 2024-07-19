/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonwkan <yeonwkan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:11:47 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/09/21 18:35:18 by yeonwkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*delete_redir(t_token *cur)
{
	t_token	*ret;

	if (is_redirection(cur))
	{
		if (cur->next->type == TYPE_WHITE_SPACE)
		{
			ret = delete_node(cur);
			ret = delete_node(ret->next);
			ret = delete_node(ret->next);
			ret = ret->next;
			return (ret);
		}
		else
		{
			ret = delete_node(cur);
			ret = delete_node(ret->next);
			ret = ret->next;
		}
		return (ret);
	}
	return (cur->next);
}
