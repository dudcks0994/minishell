/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 04:04:30 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/13 19:26:43 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(void)
{
	perror("bash : ");
	return (1);
}

int	error_arg_msg(char *str)
{
	struct stat	st;
	char		*err_msg;

	stat(str, &st);
	err_msg = ft_strdup("bash : ");
	err_msg = ft_strjoin3(err_msg, str);
	err_msg = ft_strjoin3(err_msg, ": ");
	if ((st.st_mode & S_IFMT) == S_IFDIR)
		err_msg = ft_strjoin3(err_msg, "is a directory");
	else
		err_msg = ft_strjoin3(err_msg, strerror(errno));
	err_msg = ft_strjoin3(err_msg, "\n");
	write(2, err_msg, ft_strlen(err_msg));
	free(err_msg);
	return (1);
}

void	print_export_error(t_data *data, char *str)
{
	char	*err_msg;

	err_msg = ft_strdup("bash: export: `");
	err_msg = ft_strjoin3(err_msg, str);
	err_msg = ft_strjoin3(err_msg, "': not a valid identifier\n");
	write(2, err_msg, ft_strlen(err_msg));
	free(err_msg);
	data->return_code = 1;
}

void	print_toomany_arg_error(void)
{
	char	*err_msg;

	err_msg = "bash: exit: too many arguments\n";
	write(2, err_msg, ft_strlen(err_msg));
}

void	print_cnf_error(char *cmd_name)
{
	char	*err_msg;

	err_msg = ft_strdup("bash: ");
	err_msg = ft_strjoin3(err_msg, cmd_name);
	err_msg = ft_strjoin3(err_msg, " : command not found\n");
	write(2, err_msg, ft_strlen(err_msg));
	free(err_msg);
}
