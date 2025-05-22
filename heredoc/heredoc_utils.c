/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 03:26:33 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/22 15:22:38 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

//closes heredocs, uses piper_len as the length for the opened heredocs/pipes
void	close_heredocs(int *heredocs, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (heredocs[i] > 0)
		{
			close(heredocs[i]);
			heredocs[i] = 0;
		}
		i++;
	}
}


void	fill_heredoc(int fd, int fd2, char *fnd, char **line)
{
	int dup_fd;

	dup_fd = dup(STDIN_FILENO);
	setup_signals(4);
	ft_putstr_fd("Delimiter is: ", dup_fd);
	ft_putendl_fd(fnd, dup_fd);
	while (1)
	{
		*line = readline(">");
		if (g_sig == 2)
		{
			dup2(dup_fd, STDIN_FILENO);
			close(dup_fd);
			close(fd2);
			return	;
		}
		if (ft_strcmp(*line, fnd) == 0 || !*line)
		{
			free(*line);
			break;
		}
		ft_putendl_fd(*line, fd);
		free(*line);
		*line = NULL;
	}
	if (!*line)
		printf("minishell: warning: here-document at\
			line 1 delimited by end-of-file (wanted `%s')\n", fnd);
	close(dup_fd);
}

//prints the delimiter and reads heredoc w/readline function
//then writes into the pipe, saves the prev fd in case of multi-heredoc
//inside the command line
int	readheredoc(int fd[2], char *fnd, int count)
{
	char *line;
	static	int	prev_fd;

	line = NULL;
	if (prev_fd > 0 && count > 0)
	{
		close(prev_fd);
		prev_fd = 0;
	}
	fill_heredoc(fd[1], fd[0], fnd, &line);
	close(fd[1]);
	prev_fd = fd[0];
	return (0);
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
				perror("pipe");
				return (-1);
			}
			readheredoc(fd, heredoc[i + 1], count++);
			if (g_sig == 2)
				break;
			line->heredocs[fill] = fd[0];
		}
		i++;
	}
	return (0);
}

//iterates through entire command line, including pipes
//then reroutes each pipeline into search_heredoc function
//detects error whenever something fails, returns (-255)
void	heredoc_handler(t_read *line)
{
	int	i;
	int chk;

	i = 0;
	chk = 0;
	while (line->piper[i])
	{
		chk = search_heredoc(line, line->piper[i], i);
		if (g_sig == 2)
			break;
		if (chk < 0)
		{
			line->heredocs[255] = HEREDOC_FAIL;
			return ;
		}
		i++;
	}
}
