/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:59:30 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/11 16:52:26 by amashhad         ###   ########.fr       */
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
void	builtin_part1(t_read *line, char **cmd);
void	ft_handle_cd(t_read *line, char **cmd);
void	ft_handle_echo(char **cmd);
void	ft_handle_export(t_read *line, char **cmd);
void	ft_handle_unset(t_read *line, char **cmd);
void	ft_handle_env(t_read *line, char **cmd);

//execution
int		prepare_piper(t_read *line);
int		execution(t_read *line);
void	free_piper(t_read *line);
void	pipe_execution(t_read *line, char **cmd);
#endif
