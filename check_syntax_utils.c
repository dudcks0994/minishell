/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:13:10 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/13 16:59:01 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirection_syntax(t_data *data)
{
	t_token	*cur;
	int		check;

	cur = data->head.next;
	while (cur)
	{
		check = check_redirection_syntax_v2(cur);
		if (check == 1)
		{
			data->syntax_error = 1;
			break ;
		}
		cur = cur->next;
	}
}

int	check_redirection_syntax_v2(t_token *cur)
{
	int	flag;

	flag = 0;
	if (!is_redirection(cur))
		return (0);
	else if (cur->next == 0)
		flag = 1;
	else if (cur->next->type == TYPE_PIPE || \
	is_redirection(cur->next))
		flag = 1;
	else if (cur->next->type == TYPE_WHITE_SPACE)
	{
		if (cur->next->next == 0)
			flag = 1;
		else if (cur->next->type == TYPE_PIPE || \
		is_redirection(cur->next->next))
			flag = 1;
	}
	return (flag);
}

void	check_pipe_syntax(t_data *data)
{
	t_token	*cur;
	int		check;

	cur = data->head.next;
	while (cur)
	{
		check = check_pipe_syntax_v2(cur);
		if (check != 0)
		{
			data->syntax_error = 1;
			data->pipe_count = 0;
			break ;
		}
		cur = cur->next;
	}
}

int	check_pipe_syntax_v2(t_token *cur)
{
	int	flag;

	flag = 0;
	if (cur->type != TYPE_PIPE)
		return (flag);
	else if (cur->next == 0)
		flag = 1;
	else if (cur->next->type == TYPE_PIPE)
		flag = 1;
	else if (cur->next->type == TYPE_WHITE_SPACE)
	{
		if (cur->next->next == 0)
			flag = 1;
		else if (cur->next->next->type == TYPE_PIPE)
			flag = 1;
	}
	return (flag);
}

int	check_syntax_error(char *s, t_data *data)
{
	check_pipe_syntax(data);
	check_redirection_syntax(data);
	if (data->syntax_error)
	{
		print_syntax_error(s, data);
		return (1);
	}
	return (0);
}
