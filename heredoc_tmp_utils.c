/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tmp_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:23:40 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_tmplist(char *filename, t_data *data)
{
	t_tmp	*new;
	t_tmp	*cur;

	cur = data->heredoc_name;
	new = (t_tmp *)ft_malloc(sizeof(t_tmp));
	new->filename = ft_strdup(filename);
	new->next = 0;
	if (!cur)
		data->heredoc_name = new;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

void	remove_tmplist(t_data *data)
{
	t_tmp	*cur;
	t_tmp	*next;

	cur = data->heredoc_name;
	while (cur)
	{
		next = cur->next;
		unlink(cur->filename);
		free(cur->filename);
		free(cur);
		cur = next;
	}
	data->heredoc_name = 0;
}
