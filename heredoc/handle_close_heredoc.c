/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_close_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 02:37:10 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 09:17:29 by amashhad         ###   ########.fr       */
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

//prints the delimiter and reads heredoc w/readline function
//then writes into the pipe, saves the prev fd in case of multi-heredoc
//inside the command line
int	readheredoc(int fd[2], char *fnd, int count)
{
	char		*line;
	static int	prev_fd;

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

//iterates through entire command line, including pipes
//then reroutes each pipeline into search_heredoc function
//detects error whenever something fails, returns (-255)
void	heredoc_handler(t_read *line)
{
	int	i;
	int	chk;

	i = 0;
	chk = 0;
	while (line->piper[i])
	{
		chk = search_heredoc(line, line->piper[i], i);
		if (g_sig == 2)
		{
			line->exit_status = 130;
			break ;
		}
		if (chk < 0)
		{
			line->exit_status = errno;
			errno = 0;
			return ;
		}
		i++;
	}
}
