/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 00:51:48 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/13 15:55:54 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_no_arg(t_env_list *cur)
{
	char	*prt;
	int		i;

	i = 0;
	ft_list_sort(&cur, ft_strcmp);
	while (cur)
	{
		prt = ft_strdup("declare -x ");
		prt = ft_strjoin3(prt, cur->key);
		if (cur->value)
		{
			prt = ft_strjoin3(prt, "=\"");
			prt = ft_strjoin3(prt, cur->value);
			prt = ft_strjoin3(prt, "\"");
		}
		if (ft_strcmp(cur->key, "_"))
			printf("%s\n", prt);
		free (prt);
		i++;
		cur = cur->next;
	}
}

void	ft_list_sort(t_env_list **begin_list, int (*cmp)())
{
	t_env_list	*cur;
	void		*temp;
	int			size;

	size = ft_list_size(*begin_list);
	while (size--)
	{
		cur = (*begin_list);
		while (cur->next)
		{
			if (cmp(cur->key, cur->next->key) > 0)
			{
				temp = cur->key;
				cur->key = cur->next->key;
				cur->next->key = temp;
				temp = cur->value;
				cur->value = cur->next->value;
				cur->next->value = temp;
			}
			cur = cur->next;
		}
	}
}

int	ft_list_size(t_env_list *begin_list)
{
	int	i;

	i = 0;
	while (begin_list)
	{
		i++;
		begin_list = begin_list->next;
	}
	return (i);
}
