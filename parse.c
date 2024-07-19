/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:55:08 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/20 15:08:42 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_string(char *s, t_data *data)
{
	int		i;
	int		check;
	t_token	*cur;

	i = 0;
	check = 0;
	cur = &data->head;
	while (s[i])
	{
		check = string_process(&s[i], cur, data);
		if (check == 0)
			cur = cur->next;
		else
			break ;
		i += cur->len;
	}
	if (check)
		print_syntax_error(s, data);
	return (check);
}

int	string_process(char *str, t_token *cur, t_data *data)
{
	int	check;

	check = 0;
	if (ft_isspace(*str))
		space_token(str, cur);
	else if (*str == '\'')
		check = quote_token(str, cur, '\'');
	else if (*str == '\"')
		check = quote_token(str, cur, '\"');
	else if (*str == '|')
		pipe_token(str, cur, data);
	else if (*str == '<')
		left_angle_bracket_token(str, cur);
	else if (*str == '>')
		right_angle_bracket_token(str, cur);
	else
		normal_token(str, cur);
	return (check);
}

t_token	*translate_dollar(t_token *cur, t_data *data)
{
	char	*old;

	if (!cur->str)
		return (cur->next);
	if (cur->type == TYPE_NORMAL || cur->type == TYPE_D_QUOTE)
	{
		old = cur->str;
		cur->str = change_env_var(old, data);
		if (cur->str && cur->str[0] == '\0')
			cur->type = TYPE_WHITE_SPACE;
		free(old);
	}
	return (cur->next);
}

t_token	*split_to_quote(t_token *cur)
{
	int		i;
	t_token	*to_cut;

	i = 0;
	to_cut = cur;
	if (cur->type == TYPE_NORMAL || \
	cur->type == TYPE_D_QUOTE || cur->type == TYPE_S_QUOTE)
	{
		while (to_cut->str[i])
		{
			if (to_cut->str[i] == '\'')
				quote_token(&to_cut->str[i], cur, '\'');
			else if (to_cut->str[i] == '\"')
				quote_token(&to_cut->str[i], cur, '\"');
			else
				normal_token(&to_cut->str[i], cur);
			cur = cur->next;
			i += cur->len;
		}
		delete_node(to_cut);
	}
	return (cur->next);
}

t_token	*nulstr_to_whitespace(t_token *cur)
{
	if (cur->str)
	{
		if ((cur->str)[0] == '\0')
			cur->type = TYPE_WHITE_SPACE;
	}
	return (cur->next);
}
