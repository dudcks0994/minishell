/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:43:37 by youngcki          #+#    #+#             */
/*   Updated: 2023/09/20 16:56:26 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_iter(t_token *cur, t_token *(*f)(t_token *cur))
{
	while (cur)
	{
		cur = f(cur);
	}
}

void	translate_env_var(t_token *cur, t_data *data)
{
	while (cur)
	{
		cur = translate_dollar(cur, data);
	}
}
