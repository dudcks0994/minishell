/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:20:42 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_var(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (1);
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		return (0);
	while (i < ft_strlen(str))
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

t_env_list	*ft_getenv_ptr(t_data *data, char *key)
{
	t_env_list	*cur;

	cur = data->env_head.next;
	while (cur)
	{
		if (ft_strcmp(key, cur->key) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

int	get_env_size(t_env_list *begin_list)
{
	int	i;

	i = 0;
	while (begin_list)
	{
		if (begin_list->value)
			i++;
		begin_list = begin_list->next;
	}
	return (i);
}

void	check_free_oldenvp(t_data *data)
{
	int	i;

	i = 0;
	while (data->renew_envp[i])
	{
		free(data->renew_envp[i]);
		i++;
	}
	free(data->renew_envp);
}

char	*separate_env_value(char *str)
{
	char	*new;
	int		i;
	int		s;
	int		len;

	i = 0;
	while (str[i] != 0 && str[i] != '=')
		i++;
	if (str[i] == 0)
		return (0);
	i++;
	s = i;
	len = ft_strlen(&str[i]);
	new = ft_malloc(sizeof(char) * (len + 1));
	new[len] = '\0';
	i = 0;
	while (i < len)
	{
		new[i] = str[s + i];
		i++;
	}
	return (new);
}
