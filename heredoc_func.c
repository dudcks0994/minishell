/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:30:25 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 15:28:57 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_data *data, t_token *cur)
{
	char	*delimiter;

	while (cur)
	{
		if (cur->type == TYPE_D_LEFT_ANGLE)
		{
			if (cur->next->type == TYPE_WHITE_SPACE)
			{
				delimiter = cur->next->next->str;
				cur->next->next->str = heredoc_single(data, delimiter);
			}
			else
			{
				delimiter = cur->next->str;
				cur->next->str = heredoc_single(data, delimiter);
			}
		}
		cur = cur->next;
		if (data->heredoc_flag == 1)
			break ;
	}
	return (0);
}

char	*heredoc_single(t_data *data, char *delimiter)
{
	int		fd;
	int		i;
	int		trans;
	char	*file_num;
	char	*temp;

	i = 0;
	trans = is_in_quote(delimiter);
	if (trans)
		delimiter = del_quote(delimiter);
	while (1)
	{
		file_num = ft_itoa(i++);
		temp = ft_strjoin("tmp", file_num);
		free(file_num);
		if (access(temp, F_OK))
			break ;
		free(temp);
	}
	fd = ft_open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	add_tmplist(temp, data);
	heredoc_readline(data, delimiter, trans, fd);
	ft_close(fd);
	free(delimiter);
	return (temp);
}

void	heredoc_readline(t_data *data, char *delimiter, int trans, int fd)
{
	char	*line;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal_heredoc(data);
		while (1)
		{
			line = readline("> ");
			if (!ft_strcmp(line, delimiter) || !line)
				break ;
			if (!trans)
				line = change_env_var(line, data);
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
			free(line);
		}
		free(line);
		exit(0);
	}
	signal_ignore_heredoc(data);
	wait_for_heredoc(data, pid);
	signal_minishell(data);
	check_heredoc_signal(data);
}
