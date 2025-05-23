/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 03:26:33 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 09:16:47 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

//checks for null condition of the line read by heredoc
int	null_condition_heredoc(char **line, char *fnd)
{
	if (ft_strcmp(*line, fnd) == 0 || !*line)
	{
		free(*line);
		return (1);
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
void	fill_heredoc(int fd, int fd2, char *fnd, char **line)
{
	int	dup_fd;

	dup_fd = dup(STDIN_FILENO);
	setup_signals(4);
	ft_putstr_fd("Delimiter is: ", dup_fd);
	ft_putendl_fd(fnd, dup_fd);
	while (1)
	{
		*line = readline(">");
		if (g_sig == 2)
		{
			dup2_close_heredoc(dup_fd, fd2);
			return ;
		}
		if (null_condition_heredoc(line, fnd))
			break ;
		ft_putendl_fd(*line, fd);
		free(*line);
		*line = NULL;
	}
	if (!*line)
		printf("minishell: warning: here-document"
			" delimited by end-of-file (wanted `%s')\n", fnd);
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
			if (pipe(fd) == -1)
			{
				perror("Pipe");
				return (-1);
			}
			readheredoc(fd, heredoc[i + 1], count++);
			if (g_sig == 2)
				break ;
			line->heredocs[fill] = fd[0];
		}
		i++;
	}
	return (0);
}
