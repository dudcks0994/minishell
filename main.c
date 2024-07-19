/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:37:33 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/24 15:01:33 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int c, char **s, char **envp)
{
	t_data				data;

	if (c != 1)
		return (-1);
	s = (void *)s;
	data_init(&data, envp);
	rl_clear_history();
	loop_minishell(&data);
	exit(data.return_code);
}

void	loop_minishell(t_data *data)
{
	char	*sentence;

	while (1)
	{
		signal_minishell(data);
		sentence = readline("minishell %% ");
		signal_ignore(data);
		if (check_sentence(data, sentence))
			continue ;
		if (parse_string(sentence, data))
			continue ;
		list_iter(&data->head, merge_redirection);
		list_iter(&data->head, quote_merge);
		if (check_syntax_error(sentence, data))
			continue ;
		cmd_init(data);
		here_doc(data, data->head.next);
		merge_return_code(data);
		excute(data);
		free(sentence);
		free_full_sentence(data);
	}
}

int	check_sentence(t_data *data, char *sentence)
{
	if (!sentence)
	{
		merge_return_code(data);
		printf("exit\n");
		exit(data->return_code);
	}
	else if (sentence[0])
		add_history(sentence);
	else if (sentence[0] == '\0')
	{
		free(sentence);
		return (1);
	}
	return (0);
}

void	data_init(t_data *data, char **envp)
{
	data->renew_envp = 0;
	data->head.str = 0;
	data->head.next = 0;
	data->head.before = 0;
	data->head.type = 0;
	data->env_head.next = 0;
	data->env_head.before = 0;
	data->env_head.key = 0;
	data->env_head.value = 0;
	data->syntax_error = 0;
	data->pipe_count = 0;
	data->tail = &data->head;
	data->cmd = 0;
	data->return_code = 0;
	data->heredoc_name = 0;
	data->pipe1[0] = 0;
	data->pipe1[1] = 1;
	data->pipe2[0] = 0;
	data->pipe2[1] = 1;
	g_ret_code = -1;
	making_env_list(data, envp);
	minishell_termios(data);
	signal_init(data);
}

void	cmd_init(t_data *data)
{
	int	i;

	i = 0;
	data->cmd = (t_cmd *)ft_malloc(sizeof(t_cmd) * (data->pipe_count + 1));
	data->cmd[0].fd_list[0] = 0;
	while (i < data->pipe_count + 1)
	{
		data->cmd[i].cmd_param = 0;
		i++;
	}
	data->cmd[data->pipe_count].fd_list[1] = 1;
}
