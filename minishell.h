/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcki <youngcki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:37:42 by youngcki          #+#    #+#             */
/*   Updated: 2023/10/21 19:04:38 by youngcki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft/libft.h"
# define TYPE_NORMAL 1
# define TYPE_D_QUOTE 2
# define TYPE_S_QUOTE 3
# define TYPE_PIPE 4
# define TYPE_LEFT_ANGLE 5
# define TYPE_RIGHT_ANGLE 6
# define TYPE_WHITE_SPACE 7
# define TYPE_VARIABLE 8
# define TYPE_CMD 9
# define TYPE_D_LEFT_ANGLE 10
# define TYPE_D_RIGHT_ANGLE 11
# define ALL_PIPE -10

typedef struct s_token
{
	char			*str;
	int				type;
	int				len;
	struct s_token	*next;
	struct s_token	*before;
}				t_token;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*before;
	struct s_env_list	*next;
}				t_env_list;

typedef struct s_index
{
	int				s;
	int				i;
}				t_index;

typedef struct s_cmd
{
	pid_t		pid;
	char		**cmd_param;
	int			fd_list[2];
}				t_cmd;

typedef struct s_tmp
{
	char			*filename;
	struct s_tmp	*next;
}				t_tmp;

typedef struct s_data
{
	char				**renew_envp;
	int					syntax_error;
	t_token				head;
	t_token				*tail;
	t_env_list			env_head;
	t_env_list			*env_tail;
	int					pipe_count;
	int					pipe1[2];
	int					pipe2[2];
	t_cmd				*cmd;
	int					return_code;
	struct sigaction	newset;
	struct termios		newsettings;
	t_tmp				*heredoc_name;
	int					heredoc_flag;
}				t_data;

int						g_ret_code;

//---------------node_utils--------------
t_token		*delete_node(t_token *cur);
t_token		*make_node(char *s, int type);
void		insert_node(t_token *cur, char *str, int type);
t_token		*make_head_node(t_token *cur);

//---------------token--------------
int			space_token(const char *s, t_token *cur);
int			quote_token(const char *s, t_token *cur, char set);
int			pipe_token(const char *s, t_token *cur, t_data *data);
int			left_angle_bracket_token(const char *s, t_token *cur);
int			right_angle_bracket_token(const char *s, t_token *cur);
int			normal_token(const char *s, t_token *cur);

//---------------utils--------------
int			ft_isspace(char c);
int			ft_ismeta(char c);
int			ft_strcmp(const char *s1, const char *s2);
int			is_merge_quote(t_token *cur);
int			is_redirection(t_token *cur);

//----------------env----------------
char		*separate_env_name(const char *s);
char		*change_env_var(char *str, t_data *data);
char		*ft_strjoin3(char *s1, char *s2);
void		before_dollar(char *str, char **ret, t_index *index);
void		single_dollar(char *str, char **ret, t_index *index);
void		double_dollar(char *str, char **ret, t_index *index);
void		return_code_dollar(char *str, char **ret, \
	t_index *index, t_data *data);
void		env_dollar(char *str, char **ret, t_index *index, t_data *data);
void		dollar_process(char *str, char **ret, t_index *index, t_data *data);

//--------------main-----------------------
void		data_init(t_data *data, char **envp);
int			check_sentence(t_data *data, char *sentence);
void		loop_minishell(t_data *data);
void		cmd_init(t_data *data);

//---------------signal_func----------------
void		change_signal_v1(int signo);
void		change_signal_v2(int signo);
void		change_signal_v3(int signo);
void		change_signal_v4(int signo);
void		merge_return_code(t_data *data);

//--------------builtin-----------------------
void		exit_sh(t_data *data, char **param);
void		pwd_sh(t_data *data);
void		env_sh(t_data *data, char **envp);
void		echo_sh(t_data *data, char **tokens);
void		cd_sh(t_data *data, char *path);
void		pwd_process(char *path, t_env_list *pwd, char *new_path);
void		export_sh(t_data *data, char **param);
void		env_process(t_data *data, char *key, char *value, char *param);
void		check_free(char *key, char *value, char *make);
void		unset_sh(t_data *data, char **param);
int			is_option(char *str, char *set);

//------------------error-----------------------
int			error_msg(void);
int			error_arg_msg(char *str);
void		print_export_error(t_data *data, char *str);
void		print_toomany_arg_error(void);
void		print_cnf_error(char *cmd_name);
void		print_numeric_error(char *param);
void		print_not_access_parent(void);
void		print_syntax_error(char *s, t_data *data);

//----------------parse------------------------
t_token		*translate_dollar(t_token *cur, t_data *data);
int			parse_string(char *s, t_data *data);
int			string_process(char *str, t_token *cur, t_data *data);
t_token		*split_to_quote(t_token *cur);
t_token		*nulstr_to_whitespace(t_token *cur);

//----------------quote-------------------------
t_token		*quote_arrange(t_token *cur);
t_token		*quote_merge(t_token *cur);

//----------------redirection--------------------
void		malloc_redir_fd_list(t_data *data);
int			open_redirection(t_token *cur, int fd_list[2], t_data *data);
int			set_fd(int *fd_list_n, t_token *to_open, \
	t_data *data, int type);
int			check_ambiguous(t_token *to_open, char *str, t_data *data);
int			iter_str(char *str, t_data *data, char **ret, int *flag);
void		init_check(t_index *index, int *flag, char **ret);
char		*cut_quote(char *str, int type);
void		join_s_quote(char *str, char **ret, t_index *index);
void		join_d_quote(char *str, char **ret, t_index *index, t_data *data);
int			join_dollar(char *str, char **ret, t_index *index, t_data *data);
int			change_env_dollar(char *str, char **ret, \
	t_index *index, t_data *data);

//------------------redir_open-------------------
int			left_angle_open(int *fd_list, t_token *to_open);
int			d_left_angle_open(int *fd_list, t_token *to_open);
int			right_angle_open(int *fd_list, t_token *to_open);
int			d_right_angle_open(int *fd_list, t_token *to_open);

//------------------token_ctl_redir-------------------
t_token		*merge_redirection(t_token *cur);
void		same_direction_merge(t_token *cur);

//--------------env_list_utils---------------------
void		making_env_list(t_data *data, char **envp);
void		making_envp(t_data *data);
void		check_free_oldenvp(t_data *data);
void		making_and_print_envp(t_data *data);
char		*separate_env_value(char *str);
char		*separate_env_key(char *str);
char		*ft_getenv(t_data *data, char *key);
t_env_list	*ft_getenv_ptr(t_data *data, char *key);
int			is_env_var(char *str);
int			get_env_size(t_env_list *begin_list);

//--------------env_list_node_utils----------------
void		add_env_node(t_data *data, char *key, char *value);
void		delete_env_node(t_data *data, char *key);

//--------------rermove_whitespace----------------
t_token		*remove_whitespace(t_token *cur);

//--------------list_iter----------------
void		list_iter(t_token *cur, t_token *(*f)(t_token *cur));
void		translate_env_var(t_token *cur, t_data *data);

//----------------check_syntax_utils-----------------
void		check_redirection_syntax(t_data *data);
int			check_redirection_syntax_v2(t_token *cur);
void		check_pipe_syntax(t_data *data);
int			check_pipe_syntax_v2(t_token *cur);
int			check_syntax_error(char *s, t_data *data);

//----------------free_utils------------------------
void		free_full_sentence(t_data *data);
void		free_token(t_token *cur);
void		free_cmd(t_data *data);

//---------------cmd_utils------------------------
int			get_cmd(t_cmd *cmd, t_token *cur, t_data *data);
int			list_process(t_token *cur, t_data *data, t_cmd *cmd);
int			param_process(t_data *data, t_cmd *cmd, t_token *cur);
t_token		*split_cmd(t_token *cur);
int			is_str_has_whitespace(char *str);
int			make_cmd_param(char **cmd_param, t_token *cur, \
int param_cnt, t_data *data);
t_token		*get_list(t_token **cur);
void		test_getcmd(t_cmd *cmd, t_data *data);
char		*find_path(char *cmd_name, t_data *data);
char		*get_right_path(char *path_value, char *cmd_name);
char		**ft_split_sh(char *str);
int			count_white_space(char *str);
char		*get_word(char **str);
char		*get_whitespace_word(char **str);
char		*get_normal_word(char **str);
int			is_slash(char *str);
int			is_absolute_path(char *cmd_name);

//----------------delete_node--------------------
t_token		*delete_redir(t_token *cur);

//-----------------excute---------------------
void		excute(t_data *data);
void		excute_single(t_data *data);
void		init_for_excute(t_data *data);
void		single_child(t_data *data);
void		excute_multi(t_data *data);
void		multi_child(t_data *data, t_token *tmp, int index);
void		recycle_pipe(t_data *data, int index);
void		close_single(t_data *data, int *stdio);
void		close_multichild(t_data *data, int idx);
void		exe_or_builtin(t_data *data, int index);

//-----------------builtin---------------------
int			is_builtin(char *cmd_name);
void		run_builtin(t_data *data, char *cmd_name, \
char **cmd_param, char **envp);

//-----------------except_locale_trans-------------
t_token		*except_locale_trans(t_token *cur);

//----------------export_no_arg-------------------
void		export_no_arg(t_env_list *cur);
void		ft_list_sort(t_env_list **begin_list, int (*cmp)());
int			ft_list_size(t_env_list *begin_list);

//-----------------here_doc-----------------------
int			here_doc(t_data *data, t_token *cur);
char		*heredoc_single(t_data *data, char *delimiter);
char		*del_quote(char *str);
int			is_in_quote(char *str);
void		heredoc_readline(t_data *data, char *delimiter, int trans, int fd);
void		check_heredoc_signal(t_data *data);
void		wait_for_heredoc(t_data *data, int pid);

//-----------------change_signal_utils--------------
void		signal_init(t_data *data);
void		signal_minishell(t_data *data);
void		signal_heredoc(t_data *data);
void		signal_default(t_data *data);
void		signal_ignore(t_data *data);
void		signal_ignore_heredoc(t_data *data);

//-----------------wait_utils--------------
void		wait_all_pid(t_data *data, t_cmd *cmd, int proc_cnt);

//-----------------termois_utils-------------
void		minishell_termios(t_data *data);
void		change_termios(t_data *data);
void		restore_termios(t_data *data);

//-----------------ft_atol-------------
long		ft_atol(char *str, int *flag);
void		multiply_num(unsigned long *cal, char *str, int *flag, int minus);

//----------------heredoc_tmp_utils---------
void		add_tmplist(char *filename, t_data *data);
void		remove_tmplist(t_data *data);

#endif
