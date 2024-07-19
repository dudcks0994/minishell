/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:16:27 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 19:01:08 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd(t_cmd *cmd, t_token *cur, t_data *data)
{
	if (list_process(cur, data, cmd))
		return (1);
	if (param_process(data, cmd, cur))
		return (1);
	return (0);
}

int	list_process(t_token *cur, t_data *data, t_cmd *cmd)
{
	if (open_redirection(cur, cmd->fd_list, data))
		return (1);
	list_iter(cur, delete_redir);
	list_iter(cur, split_to_quote);
	translate_env_var(cur, data);
	list_iter(cur, quote_arrange);
	list_iter(cur, split_cmd);
	list_iter(cur, quote_merge);
	list_iter(cur, remove_whitespace);
	return (0);
}

int	param_process(t_data *data, t_cmd *cmd, t_token *cur)
{
	int			param_cnt;
	t_token		*start;
	char		**ret;
	int			flag;

	param_cnt = 0;
	cur = cur->next;
	if (!cur)
		return (1);
	start = cur;
	while (cur)
	{
		param_cnt++;
		cur = cur->next;
	}
	ret = (char **)ft_malloc(sizeof(char *) * (param_cnt + 1));
	ret[param_cnt] = 0;
	flag = make_cmd_param(ret, start, param_cnt, data);
	cmd->cmd_param = ret;
	if (flag)
		return (1);
	return (0);
}

t_token	*get_list(t_token **cur)
{
	t_token	*old;
	t_token	*ret;

	old = *cur;
	while ((*cur)->next && (*cur)->type != TYPE_PIPE)
		*cur = (*cur)->next;
	if (!((*cur)->next))
	{
		*cur = old;
		ret = 0;
		return (ret);
	}
	if ((*cur)->type == TYPE_PIPE)
		*cur = delete_node(*cur);
	ret = (*cur)->next;
	(*cur)->next->before = 0;
	(*cur)->next = 0;
	*cur = old;
	return (ret);
}

t_token	*split_cmd(t_token *cur)
{	
	char	**tmp;
	int		i;

	if (cur->type == TYPE_NORMAL)
	{
		if (is_str_has_whitespace(cur->str))
		{
			i = 0;
			tmp = ft_split_sh(cur->str);
			cur = delete_node(cur);
			while (tmp[i])
			{
				if (is_str_has_whitespace(tmp[i]))
					insert_node(cur, tmp[i], TYPE_WHITE_SPACE);
				else
					insert_node(cur, tmp[i], TYPE_NORMAL);
				cur = cur->next;
				i++;
			}
			free(tmp);
		}
	}
	return (cur->next);
}
