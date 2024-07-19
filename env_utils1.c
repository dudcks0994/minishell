/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:25:14 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin3(char *s1, char *s2)
{
	size_t	size;
	char	*ret;
	char	*make;
	char	*free_str;

	free_str = s1;
	size = ft_strlen(s1);
	size += ft_strlen(s2);
	make = (char *)ft_malloc(sizeof(char) * (size + 1));
	if (make == 0)
		exit(1);
	ret = make;
	while (s1 && *s1)
		*make++ = *s1++;
	while (s2 && *s2)
		*make++ = *s2++;
	*make = '\0';
	free(free_str);
	return (ret);
}

char	*separate_env_name(const char *s)
{
	char	*name;
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			break ;
		i++;
	}
	name = ft_malloc(sizeof(char) * (i + 1));
	name[i] = '\0';
	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			break ;
		name[i] = s[i];
		i++;
	}
	return (name);
}

char	*change_env_var(char *str, t_data *data)
{
	char	*ret;
	t_index	index;

	index.i = 0;
	index.s = 0;
	ret = ft_calloc(1, sizeof(char));
	while (str[index.i])
	{
		if (str[index.i] == '$' && str[index.i + 1] != '_' && \
		ft_isalpha(str[index.i + 1]) != 1)
		{
			if (str[index.i + 1] == '?')
				dollar_process(str, &ret, &index, data);
			else
				index.i += 2;
		}
		else if (str[index.i] == '$' && str[index.i + 1] == '?')
			dollar_process(str, &ret, &index, data);
		else if (str[index.i] == '$')
			dollar_process(str, &ret, &index, data);
		else
			index.i++;
	}
	before_dollar(str, &ret, &index);
	return (ret);
}

void	dollar_process(char *str, char **ret, t_index *index, t_data *data)
{
	if (str[index->i + 1] == '$')
		double_dollar(str, ret, index);
	else if (str[index->i + 1] == '?')
		return_code_dollar(str, ret, index, data);
	else if (ft_ismeta(str[index->i + 1]) || !str[index->i + 1])
		single_dollar(str, ret, index);
	else
		env_dollar(str, ret, index, data);
}
