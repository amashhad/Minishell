/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 03:26:33 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/11 20:40:47 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	readheredoc(int fd, char *fnd)
{
	char	*line;

	while ((line = get_next_line(0)))
	{
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		if (ft_strcmp(line, fnd) == 0)
		{
			free(line);
			break;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (0);
}

int	search_heredoc(t_read *line, char **heredoc)
{
	static	int fill;
	int			i;
	int			fd[2];

	i = 0;
	if (line->heredocs[fill] == HEREDOC_FINISH)
		fill++;
	if (ft_arr_srch("<<", heredoc + i) < 1)
		return (fill);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	readheredoc(fd[1], heredoc[ft_arr_srch("<<", heredoc)]);
	line->heredocs[fill] = fd[0];
	fill++;
	return (0);
}

void	heredoc_handler(t_read *line)
{
	int	i;
	int chk;

	i = 0;
	chk = 0;
	while (line->piper[i])
	{
		chk = search_heredoc(line, line->piper[i]);
		if (chk < 0)
		{
			line->heredocs[255] = HEREDOC_FAIL;
			return ;
		}
		if (chk < 255)
			line->heredocs[chk] = HEREDOC_FINISH;
		i++;
	}
}
