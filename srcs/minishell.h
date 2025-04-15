/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:59:30 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/14 05:32:35 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../expander/ft_expander.h"
# include "../tokenizer/tokenizer.h"
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

# ifndef PATH_MAX
# define PATH_MAX 4096
# endif

typedef struct s_read
{
	int		exit_status;
	char	*prompt;
	char	*line;
	char	*cwd;
	char	**enviro;
	char	**tokens;
	char	**expo;
	char	***piper;
	int		piper_len;
}				t_read;

//Minishell
int		ft_exit_shell(t_read *line);
void	ft_get_prompt(t_read *line);
void	ft_exit_with_error(t_read *line, char *str, int errno);
void	terminal_shell(t_read *line);

//Builtin
int		builtin_part1(t_read *line, char **cmd);
void	ft_handle_cd(t_read *line, char **cmd);
void	ft_handle_echo(char **cmd);
void	ft_handle_export(t_read *line, char **cmd);
void	ft_handle_unset(t_read *line, char **cmd);
void	ft_handle_env(t_read *line, char **cmd);

//execution
int		prepare_piper(t_read *line);
int		execution(t_read *line);
void	free_piper(t_read *line);
int	pipe_execution(t_read *line);

//pipex_test
int	ft_extra_chk(char *fcommand);
char	**ft_get_paths(t_read *line, char **env);
char	*ft_find_executable(t_read *line, char **env, char *cmd);
int	execute(t_read *line, char **cmd, char **env);
void	ft_errmsg(t_read *line, char *msg, int errno);
void	close_fds(int *fds, int fd_count);
#endif
