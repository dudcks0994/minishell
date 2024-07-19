/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_node_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:57:48 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*delete_node(t_token *cur)
{
	t_token	*ret;

	ret = cur->before;
	if (ret)
		cur->before->next = cur->next;
	if (cur->next)
		cur->next->before = cur->before;
	free(cur->str);
	free(cur);
	return (ret);
}

t_token	*make_node(char *s, int type)
{
	t_token	*ret;

	ret = ft_malloc(sizeof(t_token));
	ret->str = s;
	ret->type = type;
	ret->next = 0;
	ret->before = 0;
	ret->len = ft_strlen(s);
	return (ret);
}

void	insert_node(t_token *cur, char *str, int type)
{	
	t_token	*make;
	t_token	*tmp;

	make = make_node(str, type);
	tmp = cur->next;
	if (tmp)
		tmp->before = make;
	cur->next = make;
	make->before = cur;
	make->next = tmp;
}

t_token	*make_head_node(t_token *cur)
{
	t_token	*ret;

	ret = make_node(NULL, 0);
	ret->next = cur;
	cur->before = ret;
	return (ret);
}
