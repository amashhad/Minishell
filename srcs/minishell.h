/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 23:02:49 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/30 14:30:43 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//heredoc identifiers enums
# define HEREDOC_FINISH -255
# define HEREDOC_FAIL -1
# define HEREDOC_SUCCESS -100

# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../expander/ft_expander.h"
# include "../tokenizer/tokenizer.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern volatile sig_atomic_t	g_sig;

typedef struct s_expander
{
	size_t	j;
	size_t	i;
	size_t	i_result;
	size_t	i_size;
	size_t	count;
	size_t	k;
	size_t	i_malloc;
	int		pand_error;
	char	*last_exit_code;
	char	*string;
	char	*argv;
	char	*quoted;
	char	*input;
	char	*var_name;
	char	*var_value;
	char	*result;
	char	**envment;
}			t_expand;

typedef struct s_token
{
	size_t	j;
	size_t	index;
	size_t	i;
	size_t	count;
	size_t	k;
	int		error_token;
	char	c;
	char	*input;
	char	**tokens;
}			t_tok;

typedef struct s_read
{
	int			exit_status;
	int			heredocs[256];
	int			old_fd;
	char		*prompt;
	char		*line;
	char		*cwd;
	char		**enviro;
	char		**tokens;
	char		**expo;
	char		***piper;
	int			piper_len;
	int			i_error;
	t_tok		*token;
	t_expand	*pand;
}				t_read;

//Minishell
int		ft_exit_shell(t_read *line);
void	ft_get_prompt(t_read *line);
void	ft_exit_with_error(t_read *line, char *str, char *exception, int err);
void	terminal_shell(t_read *line);

//Initialization
void	initalization_struct_pand(t_read *line);
void	initalization_struct_tok(t_read *line);
void	initalization(t_read *line, char **envp);

//execution
//execution->int
int		prepare_piper(t_read *line);
int		pipe_execution(t_read *line);
int		open_stdin(char *cmd);
int		open_stdout(char **cmd, int *close_flag);
//int		execution(t_read *line);
//execution->char
char	**redirect_stdout(char **cmd);
char	**redirect_stdin(t_read *line, char **cmd, int track);
char	**ft_get_paths(t_read *line, char **env);
char	*ft_find_executable(t_read *line, char **env, char *cmd);
//execution->void
void	ft_errmsg(t_read *line, int pingpong[2][2], char *msg, int err);
void	close_fds(int fds[2][2], int piper_len);
void	free_piper(t_read *line);
void	cmd_chain(t_read *line, int write[2], int read[2], int cmd);
void	execution_free(t_read *line, int exit_stat, char *msg);
void	free_piper(t_read *line);
void	wait_children(t_read *line, int *status, int pingpong[2][2], pid_t pid);
void	cmd_loop(t_read *line, int track, int pingpong[2][2]);
void	last_cmd(t_read *line, int read[2], int write[2], int cmd);
void	execute(t_read *line, char **cmd, char **env, int track);

//expander
//expander->int
int		comper_expander(char c);
int		string_expander(char c);
size_t	count_malloc(t_expand *pand);
//expander->char *
char	*ft_expander(t_read *line, char *last_exit_code, char *argv);
char	*get_string_expander(t_expand *pand);
//expander->void
void	ft_free_expander(t_expand *pand);
void	dollar_malloc_expander(t_expand *pand);
void	dollar_fill_expander(t_expand *pand);
void	single_quoted(t_expand *pand);
void	fill_value_expander(t_expand *pand, char *value);
void	var_expander(t_expand *pand);
void	initialize_pand(t_expand *pand);
void	go_to_check_arrow(t_read *line);
void	fill_arrow(t_expand *pand);
void	count_arrow(t_expand *pand);
void	go_to_check_error_arrow(t_read *line);
void	go_to_check_arrow_two(t_read *line);
void	go_to_check_arrow(t_read *line);

//tokenizer
//tokenizer->int
int		comper(char c);
//expander->char
char	**ft_tokenizer(t_read *line);
//expander->void
void	initialize_tok(t_tok *token);
void	ft_free_tokenizer(t_tok *token);
void	greater_tokenizer(t_tok *token);
void	pipe_tokenizer(t_tok *token);
void	dollar_tokenizer(t_tok *token);
void	string_tokenizer(t_tok *token);
void	double_quoted(t_expand *pand);
void	fill_double_quoted(t_expand *pand);
//heredoc
int		check_heredocs(t_read *line, int heredoc, char ***fetch, int track);
int		readheredoc(int fd[2], char *fnd, int count);
int		search_heredoc(t_read *line, char **heredoc, int fill);
char	**remove_heredoc(char **fetch);
void	heredoc_handler(t_read *line);
void	close_heredocs(int *heredocs, int len);
int		readheredoc(int fd[2], char *fnd, int count);
void	fill_heredoc(int fd, int fd2, char *fnd, char **line);

//builtin
//builtin->int
int		builtin_part1(t_read *line, char **cmd);
int		check_quoted(char *str);
int		is_n(char *str);
int		is_odd(char *str);
int		check_quoted_1(char *serch, int i);
int		check_quoted_2(char *serch, int i);
int		check_redirections(char *str);
int		chk_compare(char c);
int		is_valid_export_key(const char *str);
//builtin->char
char	*ft_getenv(char **enviro, char *env);
char	**fill_env(char *str, char **old_arr);
char	**fill_export(char *str, char **old_arr);
char	**rplc_env(char *fnd, char **old_arr, char *rplc);
char	**rplc_export(char *fnd, char **old_arr, char *rplc);
char	*get_key(char *str, int c);
char	*check_name_of_key(char **arr, char *fetch);
char	*get_serch(char *str, int c);
char	*check_name(const char *big, const char *little, size_t len);

//builtin->void
void	ft_handle_cd(t_read *line, char **cmd);
void	ft_handle_echo(char **cmd);
void	ft_handle_export(t_read *line, char **cmd);
void	ft_handle_unset(t_read *line, char **cmd);
void	ft_handle_env(t_read *line, char **cmd);
void	*copy_without_quoted(char *str, int size, char **arr);
void	*add_quoted_for_value(char **arr, int size);
void	count_in_side_quoted(char *str, char c, int *i, int *j);
void	fill_in_side_quoted(char *str, char *s, int *i, int *j);
void	add_rplc(t_read *line, char *srch, char *rplc);

//signals(void)
void	handle_sigint(int sig);
void	setup_signals(int mode);
void	ft_signal(int mod);
void	ft_signal2(int mod);
void	ft_signal3(int mod);
void	ft_signal4(int mod);

#endif
