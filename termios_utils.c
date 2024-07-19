/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:25:20 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/11 17:20:00 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_termios(t_data *data)
{
	tcgetattr(STDIN_FILENO, &data->newsettings);
	data->newsettings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->newsettings);
}

void	change_termios(t_data *data)
{
	data->newsettings.c_lflag |= ECHOCTL;
	data->newsettings.c_lflag &= ~ECHONL;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->newsettings);
}

void	restore_termios(t_data *data)
{
	data->newsettings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->newsettings);
}
