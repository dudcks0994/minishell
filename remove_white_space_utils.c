/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_white_space_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonwkan <yeonwkan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:32:33 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/09 14:51:33 by yeonwkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*remove_whitespace(t_token *cur)
{
	t_token	*ret;

	ret = cur;
	if (cur->type == TYPE_WHITE_SPACE)
		ret = delete_node(cur);
	return (ret->next);
}
