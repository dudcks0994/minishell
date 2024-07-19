/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_node_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:35:08 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_data *data, char *key, char *value)
{
	t_env_list	*new;

	new = ft_malloc(sizeof(t_env_list));
	new->key = key;
	new->value = value;
	new->next = 0;
	if (data->env_head.next == 0)
	{
		data->env_head.next = new;
		new->before = &data->env_head;
	}
	else
	{
		new->before = data->env_tail;
		data->env_tail->next = new;
	}
	data->env_tail = new;
}

void	delete_env_node(t_data *data, char *key)
{
	t_env_list	*cur;

	cur = data->env_head.next;
	while (cur)
	{
		if (ft_strcmp(key, cur->key) == 0)
		{
			cur->before->next = cur->next;
			if (cur->next)
				cur->next->before = cur->before;
			else
				data->env_tail = cur->before;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		cur = cur->next;
	}
}
