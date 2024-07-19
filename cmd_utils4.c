/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:32:29 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 15:25:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_sh(char *str)
{
	int		ws;
	int		i;
	char	**new;

	ws = count_white_space(str);
	new = (char **)ft_malloc(sizeof(char *) * (ws + 1));
	new[ws] = 0;
	i = 0;
	while (i < ws)
	{
		new[i] = get_word(&str);
		i++;
	}
	return (new);
}
