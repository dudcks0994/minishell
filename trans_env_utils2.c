/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_env_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:55:29 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/13 17:55:42 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_env_dollar(char *str, char **ret, t_index *index, t_data *data)
{
	char	*tmp1;
	char	*tmp2;

	before_dollar(str, ret, index);
	tmp1 = separate_env_name(&str[index->i + 1]);
	tmp2 = ft_getenv(data, tmp1);
	if (is_str_has_whitespace(tmp2))
	{
		free(tmp1);
		free(*ret);
		return (1);
	}
	index->i += ft_strlen(tmp1) + 1;
	index->s = index->i;
	free(tmp1);
	tmp1 = ft_strjoin(*ret, tmp2);
	free(*ret);
	*ret = tmp1;
	return (0);
}
