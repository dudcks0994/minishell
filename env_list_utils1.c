/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:44:03 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	making_env_list(t_data *data, char **envp)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		key = separate_env_key(envp[i]);
		j = 0;
		while (envp[i][j] != '=')
			j++;
		value = separate_env_value(envp[i]);
		add_env_node(data, key, value);
		i++;
	}
}

void	making_envp(t_data *data)
{
	t_env_list	*cur;
	char		*tmp;
	char		**envp;
	int			i;
	int			env_size;

	if (data->renew_envp != 0)
		check_free_oldenvp(data);
	env_size = get_env_size(data->env_head.next);
	envp = ft_malloc(sizeof(char *) * (env_size + 1));
	envp[env_size] = 0;
	i = 0;
	cur = data->env_head.next;
	while (i < env_size)
	{
		if (cur->value)
		{
			tmp = ft_strjoin(cur->key, "=");
			envp[i] = ft_strjoin(tmp, cur->value);
			free(tmp);
			i++;
		}
		cur = cur->next;
	}
	data->renew_envp = envp;
}

char	*separate_env_key(char *str)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	while (str[i] != 0 && str[i] != '=')
		i++;
	if (str[i] == 0)
		return (ft_strdup(str));
	len = i;
	new = ft_malloc(sizeof(char) * (len + 1));
	new[len] = '\0';
	i = 0;
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	return (new);
}

char	*ft_getenv(t_data *data, char *key)
{
	t_env_list	*cur;

	cur = data->env_head.next;
	while (cur)
	{
		if (ft_strcmp(key, cur->key) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}
