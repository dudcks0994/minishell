/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:28:38 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_dollar(char *str, char **ret, t_index *index)
{
	before_dollar(str, ret, index);
	index->i += 2;
	index->s = index->i;
}

void	single_dollar(char *str, char **ret, t_index *index)
{
	char	*env;

	before_dollar(str, ret, index);
	env = ft_malloc(sizeof(char) * 2);
	env[0] = '$';
	env[1] = '\0';
	*ret = ft_strjoin3(*ret, env);
	free(env);
	index->i += 1;
	index->s = index->i;
}

void	before_dollar(char *str, char **ret, t_index *index)
{
	char	*add;

	add = ft_substr(str, index->s, index->i - index->s);
	*ret = ft_strjoin3(*ret, add);
	free(add);
}

void	env_dollar(char *str, char **ret, t_index *index, t_data *data)
{
	char	*env;
	char	*name;

	before_dollar(str, ret, index);
	name = separate_env_name(&str[index->i + 1]);
	env = ft_getenv(data, name);
	*ret = ft_strjoin3(*ret, env);
	index->i += ft_strlen(name) + 1;
	index->s = index->i;
	free(name);
}

void	return_code_dollar(char *str, char **ret, t_index *index, t_data *data)
{
	char	*tmp1;
	char	*tmp2;

	before_dollar(str, ret, index);
	tmp1 = ft_itoa(data->return_code);
	tmp2 = ft_strjoin(*ret, tmp1);
	free(tmp1);
	free(*ret);
	*ret = tmp2;
	index->i += 2;
	index->s = index->i;
}
