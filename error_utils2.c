/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:16:35 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/20 20:33:11 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_numeric_error(char *param)
{
	char	*err_msg;

	err_msg = ft_strdup("bash: exit: ");
	err_msg = ft_strjoin3(err_msg, ft_strdup(param));
	err_msg = ft_strjoin3(err_msg, ": numeric argument required\n");
	write(2, err_msg, ft_strlen(err_msg));
	free(err_msg);
}

void	print_not_access_parent(void)
{
	char	*err_msg;

	err_msg = ft_strdup("cd: error retrieving current directory: getcwd:");
	err_msg = ft_strjoin3(err_msg, \
		"cannot access parent directories: No such file or directory\n");
	write(2, err_msg, ft_strlen(err_msg));
	free(err_msg);
}

void	print_syntax_error(char *s, t_data *data)
{
	ft_putstr_fd("syntax error\n", 2);
	free_token(data->head.next);
	free(s);
	data->head.next = 0;
	data->syntax_error = 0;
	data->return_code = 258;
}
