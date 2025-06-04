/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:40:08 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/04 18:52:24 by amashhad         ###   ########.fr       */
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
	int				i;
	static int		close_flag;
	char			**fetch;

	i = 0;
	fetch = ft_cpyarr(cmd);
	if (!fetch)
		return (NULL);
	while (ft_fetcharr(fetch, ">") || ft_fetcharr(fetch, ">>"))
	{
		if ((ft_strcmp(">", fetch[i]) == 0) || (ft_strcmp(">>", fetch[i]) == 0))
		{
			if (!ft_arr_srch(">", fetch + i) || !ft_arr_srch(">>", fetch + i))
				close_flag = 1;
			if (open_stdout(fetch + i, &close_flag) == -1)
				return (redirect_clear(fetch));
			fetch = del_arr(fetch, i);
			fetch = del_arr(fetch, i);
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
				if (counter != 2 || line->old_fd > 0)
					close(line->old_fd);
				line->old_fd = open_stdin((*fetch)[i + 1]);
				if (line->old_fd < 0)
				{
					redirect_clear(*(fetch));
					return ;
				}
				*fetch = del_arr(*fetch, i);
				*fetch = del_arr(*fetch, i);
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
	int	stdinput;

	heredoc = 0;
	stdinput = 0;
	i = 0;
	line->old_fd = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<") == 0)
			stdinput = i;
		else if (ft_strcmp(cmd[i], "<<") == 0)
			heredoc = i;
		i++;
	}
	if (heredoc > stdinput)
		return (1);
	else if (stdinput > heredoc)
		return (2);
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
	fetch = ft_cpyarr(cmd);
	ft_farray (cmd);
	if (!ft_fetcharr(fetch, "<"))
		return (fetch);
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
