/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:59:30 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/06 23:57:39 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

# ifndef PATH_MAX
# define PATH_MAX 4096
# endif

typedef struct s_read
{
	char	*prompt;
	char	*line;
	char	*cwd;
	char	**enviro;
	char	**tokens;
	char	**expo;
}				t_read;

int	ft_exit_shell(char *line);
void	builtin(t_read *line);
void	ft_get_prompt(t_read *line);
void	ft_exit_with_error(char *str);
void	ft_handle_cd(t_read *line);

#endif
