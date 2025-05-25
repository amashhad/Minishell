/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:40:08 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/25 23:03:25 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

//safetly disposes of the redirected cmd
char	**redirect_clear(char **func)
{
	ft_farray(func);
	func = NULL;
	return (NULL);
}

//searches for ">" && ">>" in the array (cmd)
//opens fds and dups the last one to STDOUT
char	**redirect_stdout(char **cmd)
{
	int		i;
	int		close_flag;
	char	**fetch;

	i = 0;
	close_flag = 0;
	fetch = ft_cpyarr(cmd);
	if (!fetch)
		return (NULL);
	while (ft_fetcharr(fetch, ">") || ft_fetcharr(fetch, ">>"))
	{
		if ((ft_strcmp(">", fetch[i]) == 0) || (ft_strcmp(">>", fetch[i]) == 0))
		{
			if (!ft_arr_srch(">", fetch + i) || !ft_arr_srch(">>", fetch + i))
				close_flag = 1;
			if (open_stdout(fetch + i, close_flag) == -1)
				return (redirect_clear(fetch));
			fetch = del_arr(fetch, fetch[i]);
			fetch = del_arr(fetch, fetch[i]);
			if (!fetch)
				return (NULL);
			continue ;
		}
		i++;
	}
	return (fetch);
}

void	stdin_arrow(t_read *line, int counter, char ***fetch)
{
	int	i;

	i = 0;
	while ((*fetch)[(i)])
	{
		if (ft_strcmp((*fetch)[(i)], "<") == 0)
		{
			if ((*fetch)[(i) + 1])
			{
				if (counter != 2 && line->old_fd > 0)
					close(line->old_fd);
				line->old_fd = open_stdin((*fetch)[i + 1]);
				if (line->old_fd < 0)
				{
					redirect_clear(*(fetch));
					return ;
				}
				*fetch = del_arr(*fetch, (*fetch)[i + 1]);
				*fetch = del_arr(*fetch, "<");
				continue ;
			}
		}
		i++;
	}
	return ;
}

int	chk_stdin(char **cmd, t_read *line)
{
	int	i;
	int	heredoc;
	int	redirect;

	heredoc = 0;
	redirect = 0;
	i = 0;
	line->old_fd = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<") == 0)
			redirect++;
		else if (ft_strcmp(cmd[i], "<<") == 0)
			heredoc++;
		i++;
	}
	if (heredoc > redirect)
		return (1);
	else if (redirect > heredoc)
		return (2);
	else if ((heredoc == redirect) && (redirect == 0))
		return (0);
	return (0);
}

//searches for "<" in the array (cmd)
//opens fds and dups the last one to STDIN
char	**redirect_stdin(t_read *line, char **cmd, int track)
{
	int		fd;
	int		counter;
	char	**fetch;

	counter = 0;
	fd = 0;
	fetch = NULL;
	if (!ft_fetcharr(cmd, "<"))
	return (cmd);
	fetch = ft_cpyarr(cmd);
	ft_farray (cmd);
	if (!fetch)
		return (NULL);
	counter = chk_stdin(fetch, line);
	stdin_arrow(line, counter, &fetch);
	if (line->old_fd == -1)
		return (NULL);
	fd = check_heredocs(line, counter, &fetch, track);
	if (fd == -1)
		return (redirect_clear(fetch));
	dup2(fd, STDIN_FILENO);
	close(fd);
	fd = -1;
	close_heredocs(line->heredocs, line->piper_len);
	return (fetch);
}
