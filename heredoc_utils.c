/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:42:33 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 18:50:45 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_quote(char *str)
{
	char	*ret;
	char	*cur;
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			cnt++;
		i++;
	}
	i = 0;
	ret = (char *)ft_malloc(sizeof(char) * (ft_strlen(str) - cnt + 1));
	cur = ret;
	while (str[i])
	{
		if (!(str[i] == '\"' || str[i] == '\''))
			*cur++ = str[i];
		i++;
	}
	free(str);
	return (ret);
}

int	is_in_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	check_heredoc_signal(t_data *data)
{
	if (data->return_code == 2)
	{
		data->return_code = 1;
		data->heredoc_flag = 1;
	}
}

void	wait_for_heredoc(t_data *data, int pid)
{
	waitpid(pid, &data->return_code, 0);
	data->return_code = WEXITSTATUS(data->return_code);
}
