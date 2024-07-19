/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_signal_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:24:49 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/19 17:25:00 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_init(t_data *data)
{
	data->newset.sa_handler = change_signal_v1;
	sigaction(SIGINT, &data->newset, 0);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_minishell(t_data *data)
{
	data->newset.sa_handler = change_signal_v1;
	sigaction(SIGINT, &data->newset, 0);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_heredoc(t_data *data)
{
	data->newset.sa_handler = change_signal_v3;
	sigaction(SIGINT, &data->newset, 0);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_ignore(t_data *data)
{
	data->newset.sa_handler = change_signal_v2;
	sigaction(SIGINT, &data->newset, 0);
	sigaction(SIGQUIT, &data->newset, 0);
}

void	signal_ignore_heredoc(t_data *data)
{
	data->newset.sa_handler = SIG_IGN;
	sigaction(SIGINT, &data->newset, 0);
	signal(SIGQUIT, SIG_IGN);
}
