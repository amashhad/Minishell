/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_executables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:40:08 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/13 19:10:30 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	**remove_heredoc(char **fetch)
{
	char	**temp;

	temp = NULL;
	while (ft_fetcharr(fetch, "<<"))
	{
		fetch = del_arr(fetch, fetch[ft_arr_srch("<<", fetch)]);
		fetch = del_arr(fetch, "<<");
	}
	temp = ft_cpyarr(fetch);
	ft_farray(fetch);
	return (temp);
}

int	fnd_fd(t_read *line)
{
	int	i;
	int rplc;

	i = 0;
	rplc = 0;
	while (i < 256)
	{
		if (line->heredocs[i] > 0)
		{
			rplc = line->heredocs[i];
			line->heredocs[i] = HEREDOC_SUCCESS;
			return (rplc);
		}
		else
			i++;
	}
	return (0);
}

//checks for heredocs, dup2s the ones that are ok
//pipes stop it, aka turn based pipes
int	check_heredocs(t_read *line, char **target)
{
	int	i;
	int	new_fd;
	int	prev_fd;

	i = 0;
	prev_fd = 0;
	new_fd = 0;
	while (target[i])
	{
		if (ft_strcmp("<<", target[i]) == 0)
		{
			if (prev_fd != 0)
				close(prev_fd);
			new_fd = fnd_fd(line);
			if ((new_fd + prev_fd) == 0)
				return (0);
			prev_fd = new_fd;
		}
		i++;
	}
	return (prev_fd);
}

//opens and closes fds, only dups when flag is != 0
int	open_stdin(t_read *line, char **cmd, int close_flag)
{
	int fd;
	int new_fd;

	new_fd = 0;
	fd = 0;
	if (ft_strcmp(cmd[0], "<<"))
		fd = open(cmd[1], O_RDONLY);
	if (fd < 0)
	{
		perror(cmd[1]);
		exit(1);
	}
	if (close_flag != 0)
	{
		new_fd = check_heredocs(line, cmd);
		if (new_fd == 0)
			dup2(fd, STDIN_FILENO);
		else
		{
			dup2(new_fd, STDIN_FILENO);
			close(new_fd);
		}
	}
	if (ft_strcmp(cmd[0], "<<"))
		close(fd);
	return (0);
}

//opens and closes fds, only dups when flag is != 0
int	open_stdout(char **cmd, int close_flag)
{
	int fd;

	fd = 0;
	if (ft_strcmp(">", cmd[0]) == 0)
		fd = open(cmd[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(cmd[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(cmd[1]);
		exit(1);
	}
	if (close_flag != 0)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

//searches for ">" && ">>" in the array (cmd)
//opens fds and dups the last one to STDOUT
char **redirect_stdout(char **cmd)
{
	int		i;
	int		close_flag;
	char	**fetch;

	i = 0;
	close_flag = 0;
	fetch = NULL;
	if (!ft_fetcharr(cmd, ">") && !ft_fetcharr(cmd, ">>"))
		return (cmd);
	fetch = ft_cpyarr(cmd);
	while (ft_fetcharr(fetch, ">") || ft_fetcharr(fetch, ">>"))
	{
		if ((ft_strcmp(">", fetch[i]) == 0) || (ft_strcmp(">>", fetch[i]) == 0))
		{
			if (!ft_fetcharr(fetch + i, ">") || !ft_fetcharr(fetch + i, ">>"))
				close_flag = 1;
			open_stdout(fetch + i, close_flag);
			fetch = del_arr(fetch, fetch[i]);
			fetch = del_arr(fetch, fetch[i]);
		}
		else
			i++;
	}
	return (fetch);
}

//searches for "<" in the array (cmd)
//opens fds and dups the last one to STDIN
char **redirect_stdin(t_read *line, char **cmd)
{
	int	i;
	int	close_flag;
	char	**fetch;

	i = 0;
	close_flag = 0;
	fetch = NULL;
	if (!ft_fetcharr(cmd, "<"))
		return (cmd);
	fetch = ft_cpyarr(cmd);
	while (fetch[i] && (ft_fetcharr(fetch, "<") || ft_fetcharr(fetch, "<<")))
	{
		if ((ft_strncmp("<", fetch[i], 1) == 0))
		{
			if (!ft_fetcharr(fetch + i + 1, "<"))
				close_flag = 1;
			open_stdin(line, fetch + i, close_flag);
			fetch = del_arr(fetch, fetch[i]);
			fetch = del_arr(fetch, fetch[i]);
		}
		else
			i++;
	}
	fetch = remove_heredoc(fetch);
	return (fetch);
}
