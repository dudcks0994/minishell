/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:55:04 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_listnew(void *content, void (*del)(void *))
{
	t_list	*ret;

	if (!content)
		return (0);
	ret = (t_list *)ft_malloc(sizeof(t_list));
	if (ret == 0)
	{
		del(content);
		return (0);
	}
	ret->next = 0;
	ret->content = content;
	return (ret);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*tmp;

	if (lst == 0)
		return (0);
	ret = 0;
	while (lst)
	{
		tmp = ft_listnew(f(lst->content), del);
		if (tmp == 0)
		{
			ft_lstclear(&ret, del);
			return (0);
		}
		ft_lstadd_back(&ret, tmp);
		lst = lst->next;
	}
	return (ret);
}
