/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:45:19 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 18:53:35 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_signal_v1(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_ret_code = 101;
	}
}

void	change_signal_v2(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		g_ret_code = 2;
	}
	else if (signo == SIGQUIT)
	{
		printf("Quit: 3\n");
		g_ret_code = 3;
	}
}

void	change_signal_v3(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		exit(signo);
	}
}

void	merge_return_code(t_data *data)
{
	if (g_ret_code >= 0)
	{
		if (g_ret_code != 0)
		{
			if (g_ret_code < 100)
				data->return_code = g_ret_code + 128;
			else
				data->return_code = g_ret_code - 100;
		}
		else
			data->return_code = 0;
		g_ret_code = -1;
	}
}
