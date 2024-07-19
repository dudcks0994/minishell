/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonwkan <yeonwkan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 02:02:26 by yeonwkan          #+#    #+#             */
/*   Updated: 2023/10/08 18:11:7 by yeonwkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_sh(t_data *data, char **param)
{
	int	i;
	int	opt;

	opt = 0;
	i = 1;
	while (is_option(param[i], "n"))
	{
		opt = is_option(param[i], "n");
		i++;
	}
	while (param[i])
	{
		write(1, param[i], ft_strlen(param[i]));
		if (param[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!opt)
		write(1, "\n", 1);
	data->return_code = 0;
}

void	env_sh(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	data->return_code = 0;
}

void	pwd_sh(t_data *data)
{
	t_env_list	*pwd;

	pwd = ft_getenv_ptr(data, "PWD");
	if (pwd)
	{
		if (pwd->value)
			printf("%s\n", pwd->value);
	}
	data->return_code = 0;
}

void	cd_sh(t_data *data, char *path)
{
	t_env_list	*pwd;
	char		*new_path;
	char		*err_msg;

	if (!path || !ft_strcmp(path, "-") || !ft_strcmp(path, "~"))
	{
		printf("cd: usage: only use a relative or absolute path\n");
		data->return_code = 1;
		return ;
	}
	if (chdir(path) == -1)
	{
		err_msg = ft_strjoin("cd: ", path);
		error_arg_msg(err_msg);
		free (err_msg);
		data->return_code = 1;
		return ;
	}
	pwd = ft_getenv_ptr(data, "PWD");
	new_path = getcwd(NULL, 1024);
	if (pwd)
		pwd_process(path, pwd, new_path);
	else
		free(new_path);
	data->return_code = 0;
}

void	exit_sh(t_data *data, char **param)
{
	int	arg_cnt;
	int	flag;

	flag = 0;
	arg_cnt = 0;
	while (param[arg_cnt])
		arg_cnt++;
	if (arg_cnt > 1)
	{
		data->return_code = ft_atol(param[1], &flag);
		if (flag)
		{
			print_numeric_error(param[1]);
			exit(255);
		}
		if (arg_cnt > 2)
		{
			print_toomany_arg_error();
			data->return_code = 1;
			return ;
		}
	}
	exit(data->return_code);
}
