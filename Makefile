CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
OBJS = $(addprefix objs/, $(SRCS:.c=.o))
OBJ_DIR = objs
LIBFT = libft/libft.a
NAME = minishell
SRCS = token_node_utils.c \
	token_parse1.c \
	token_parse2.c \
	utils.c \
	env_utils1.c \
	env_utils2.c \
	error_utils1.c \
	error_utils2.c \
	builtin_func1.c \
	builtin_func2.c \
	builtin_utils1.c \
	builtin_utils2.c \
	parse.c \
	quote.c \
	env_list_utils1.c \
	env_list_utils2.c \
	env_list_node_utils.c \
	remove_white_space_utils.c \
	list_iter.c \
	check_syntax_utils.c \
	cmd_utils1.c \
	cmd_utils2.c \
	cmd_utils3.c \
	cmd_utils4.c \
	delete_node.c \
	free_utils.c \
	redirection.c \
	excute_func.c \
	excute_utils.c \
	main.c \
	export_no_arg.c \
	heredoc_utils.c \
	change_signal_utils.c \
	wait_utils.c \
	termios_utils.c \
	ft_atol.c \
	redir_open.c \
	token_ctl_redir.c \
	heredoc_tmp_utils.c \
	heredoc_func.c \
	signal_func.c \
	trans_env_utils1.c \
	trans_env_utils2.c

all: $(NAME)

$(NAME): $(OBJ_DIR) mandatory

$(OBJ_DIR):
	@mkdir objs

mandatory: $(OBJS) $(LIBFT)
	@rm -f mandatory bonus $(NAME)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@touch $@
	$(info  )
	$(info               d8b          d8b          888               888 888 )
	$(info               Y8P          Y8P          888               888 888 )
	$(info                                         888               888 888 )
	$(info 88888b.d88b.  888 88888b.  888 .d8888b  88888b.   .d88b.  888 888 )
	$(info 888 "888 "88b 888 888 "88b 888 88K      888 "88b d8P  Y8b 888 888 )
	$(info 888  888  888 888 888  888 888 "Y8888b. 888  888 88888888 888 888 )
	$(info 888  888  888 888 888  888 888      X88 888  888 Y8b.     888 888 )
	$(info 888  888  888 888 888  888 888  88888P' 888  888  "Y8888  888 888  by youngcki and yeonwkan)
	$(info  )
libft/libft.a:
	@make -C libft

objs/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)
	@rm -f $(MAIN_MAND:.c=.o)
	@rm -f $(MAIN_BONUS:.c=.o)
	@rm -f mandatory bonus
	@make -C libft fclean
	@rm -rf $(OBJ_DIR)

re: fclean 
	@make all

.PHONY: all clean fclean re
