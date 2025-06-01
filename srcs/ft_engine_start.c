/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_engine_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:32:22 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/28 22:42:53 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_exit_status(t_read *line, char *token, int exit_status, int std)
{
	line->exit_status = exit_status;
	if (token != NULL)
	{
		if (ft_strcmp(token, ">>") || ft_strcmp(token, "<<"))
		{
			ft_putendl_fd("bash: syntax error "
				"near unexpected token `newline'", std);
			return (line->exit_status);
		}
		ft_putstr_fd("bash: syntax error near unexpected token `", std);
		ft_putstr_fd(token, std);
		ft_putendl_fd("'", std);
	}
	return (line->exit_status);
}

void	ft_checktokens(t_read *line)
{
	int	i;
	int	srch;

	i = 0;
	srch = 0;
	if (ft_strcmp(line->tokens[0], "|") == 0
		|| ft_strcmp(line->tokens[ft_arrlen(line->tokens) - 1], "|") == 0)
	{
		syntax_exit_status(line, "|", 2, 2);
		return ;
	}
	while (line->tokens[i])
	{
		if (ft_strcmp(line->tokens[i], "|") == 0)
		{
			if (srch > 0 && i - srch == 1)
			{
				syntax_exit_status(line, "|", 2, 2);
				return ;
			}
			else
				srch = i;
		}
		i++;
	}
}

void	ft_checkredirect(t_read *line)
{
	static char	*redirections[] = {">", ">>", "<<", "<", NULL};

	if (ft_arr_srch(line->tokens[0], redirections)
		&& ft_arrlen(line->tokens) < 2)
	{
		syntax_exit_status(line, line->tokens[0], 2, 2);
		return ;
	}
	if (ft_arr_srch(line->tokens[ft_arrlen(line->tokens) - 1], redirections)
		|| (ft_arr_srch(line->tokens[ft_arrlen(line->tokens)
					- 1], redirections)))
	{
		syntax_exit_status(line, line->tokens[ft_arrlen(line->tokens)
			- 1], 2, 2);
		return ;
	}
}

static int	terminal_helper(t_read *line)
{
	if (line->exit_status != 0)
		return (1);
	if (!line->tokens || *line->tokens == NULL || line->tokens[0][0] == '\0')
	{
		free (line->line);
		line->pand->result = NULL;
		line->line = NULL;
		return (1);
	}
	return (0);
}

void	terminal_shell(t_read *line)
{
	int	exit_code;

	exit_code = line->exit_status;
	if (line->exit_status != 2 || line->line[0] == '\0')
	{
		if (terminal_helper(line))
			return ;
		ft_checktokens(line);
		if (exit_code != line->exit_status)
			return ;
		ft_checkredirect(line);
		if (exit_code != line->exit_status)
			return ;
		prepare_piper(line);
		if (exit_code != line->exit_status)
			return ;
		heredoc_handler(line);
		if (exit_code != line->exit_status)
			return ;
		pipe_execution(line);
	}
	else
		line->exit_status = 2;
}
