/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 03:26:33 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/05 18:41:42 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	syntax_error_heredoc(t_read *line, int fill)
{
	if (line->heredocs[fill] > 0)
		close(line->heredocs[fill]);
	printf("Minishell: syntax error near unexpected token `<<'\n");
	errno = 2;
	return (-1);
}

//checks for null condition of the line read by heredoc
int	null_condition_heredoc(t_read *line, char *fnd)
{
	if (ft_strcmp(line->line, fnd) == 0 || !line->line)
	{
		if (!line->line)
		{
			printf("minishell: warning: here-document"
				" delimited by end-of-file (wanted `%s')\n", fnd);
			return (1);
		}
		else
		{
			free(line->line);
			line->line = NULL;
			line->pand->result = NULL;
			return (1);
		}
	}
	else
		return (0);
}

void	dup2_close_heredoc(int dup_fd, int fd2)
{
	dup2(dup_fd, STDIN_FILENO);
	close(dup_fd);
	close(fd2);
}

//fills heredoc
void	fill_heredoc(int fd, int fd2, char *fnd, t_read *line)
{
	int	dup_fd;

	dup_fd = dup(STDIN_FILENO);
	setup_signals(4);
	ft_putstr_fd("Delimiter is: ", dup_fd);
	ft_putendl_fd(fnd, dup_fd);
	while (1)
	{
		free_line(line);
		line->line = readline(">");
		line->line = ft_expander(line,
				ft_itoa(line->exit_status), "./minishell");
		if (g_sig == 2)
		{
			dup2_close_heredoc(dup_fd, fd2);
			return ;
		}
		if (null_condition_heredoc(line, fnd))
			break ;
		ft_putendl_fd(line->line, fd);
		free(line->line);
		line->line = NULL;
	}
	close(dup_fd);
}

//searches the 'specific' argument for << (heredoc), assumes no syntax err
//then opens a pipe at the very last << (heredoc) available
int	search_heredoc(t_read *line, char **heredoc, int fill)
{
	int			i;
	int			fd[2];
	int			count;

	i = 0;
	count = 0;
	while (heredoc[i])
	{
		if (ft_strcmp(heredoc[i], "<<") == 0 && heredoc[i + 1])
		{
			if (ft_strcmp(heredoc[i + 1], "<<") == 0)
				return (syntax_error_heredoc(line, fill));
			if (pipe(fd) == -1)
			{
				perror("Pipe");
				return (-1);
			}
			readheredoc(line, fd, heredoc[i + 1], count++);
			if (g_sig == 2)
				break ;
			line->heredocs[fill] = fd[0];
		}
		i++;
	}
	return (0);
}
