/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_env_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:37:37 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/13 17:55:26 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iter_str(char *str, t_data *data, char **ret, int *flag)
{
	t_index	index;

	index.i = 0;
	index.s = 0;
	while (str[index.i])
	{
		if (str[index.i] == '\'')
			join_s_quote(str, ret, &index);
		else if (str[index.i] == '\"')
			join_d_quote(str, ret, &index, data);
		else if (str[index.i] == '$')
		{
			*flag = 1;
			if (join_dollar(str, ret, &index, data))
				return (1);
		}
		else
			index.i++;
	}
	before_dollar(str, ret, &index);
	return (0);
}

char	*cut_quote(char *str, int type)
{
	int		i;
	char	*ret;

	i = 0;
	if (type == TYPE_S_QUOTE)
	{
		while (str[i] != '\'')
			i++;
		ret = ft_substr(str, 0, i);
	}
	else
	{
		while (str[i] != '\"')
			i++;
		ret = ft_substr(str, 0, i);
	}
	return (ret);
}

void	join_s_quote(char *str, char **ret, t_index *index)
{
	char	*tmp1;
	char	*tmp2;

	before_dollar(str, ret, index);
	tmp1 = cut_quote(&str[index->i + 1], TYPE_S_QUOTE);
	tmp2 = ft_strjoin(*ret, tmp1);
	free(*ret);
	*ret = tmp2;
	index->i += ft_strlen(tmp1) + 2;
	index->s = index->i;
	free(tmp1);
}

void	join_d_quote(char *str, char **ret, t_index *index, t_data *data)
{
	char	*tmp1;
	char	*tmp2;

	before_dollar(str, ret, index);
	tmp1 = cut_quote(&str[index->i + 1], TYPE_D_QUOTE);
	tmp2 = change_env_var(tmp1, data);
	index->i += ft_strlen(tmp1) + 2;
	index->s = index->i;
	free(tmp1);
	tmp1 = ft_strjoin(*ret, tmp2);
	free(*ret);
	*ret = tmp1;
	free(tmp2);
}

int	join_dollar(char *str, char **ret, t_index *index, t_data *data)
{
	if (str[index->i + 1] == '$')
		double_dollar(str, ret, index);
	else if (str[index->i + 1] == '?')
		return_code_dollar(str, ret, index, data);
	else
		if (change_env_dollar(str, ret, index, data))
			return (1);
	return (0);
}
