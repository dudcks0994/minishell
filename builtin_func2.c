/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:33:51 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/13 19:27:46 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_sh(t_data *data, char **param)
{
	int			i;
	char		*key;
	char		*value;
	char		*make;

	i = 1;
	if (!param[i])
	{
		export_no_arg(data->env_head.next);
		return ;
	}
	while (param[i])
	{
		make = ft_strdup(param[i]);
		key = separate_env_key(make);
		value = separate_env_value(make);
		if (is_env_var(key))
			env_process(data, key, value, param[i]);
		else
			print_export_error(data, param[i]);
		check_free(key, value, make);
		i++;
	}
}

void	unset_sh(t_data *data, char **param)
{
	int			i;
	t_env_list	*find;

	i = 0;
	while (param[i])
	{
		if (is_env_var(param[i]))
		{
			if (ft_strcmp(param[i], "_"))
			{
				find = ft_getenv_ptr(data, param[i]);
				if (find)
					delete_env_node(data, param[i]);
			}
		}
		else
			print_export_error(data, param[i]);
		i++;
	}
}
