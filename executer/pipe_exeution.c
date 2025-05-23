/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exeution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:20:44 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 03:27:55 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	piper_ops(t_read *line)
{
	int		pingpong[2][2];
	int		status;
	int		track;
	pid_t	pid;

	track = 0;
	while (track < (line->piper_len - 1))
		cmd_loop(line, track++, pingpong);
	if (track > 1)
	{
		close(pingpong[track % 2][0]);
		close(pingpong[track % 2][1]);
	}
	pid = fork();
	if (pid == -1)
		ft_errmsg(line, "Fork Failed\n", 1);
	if (pid == 0)
	{
		setup_signals(2);
		last_cmd(line, pingpong[(track + 1) % 2], pingpong[(track) % 2], track);
	}
	ft_signal3(3);
	wait_children(line, &status, pingpong, pid);
	return (line->exit_status);
}

int	is_there_redirection(t_read *line)
{
	int		i;

	i = -1;
	while (line->piper[0][++i] != NULL)
	{
		if (check_redirections(line->piper[0][i]))
			break ;
	}
	if (line->piper[0][i] == NULL)
		return (0);
	i = 0;
	while (line->piper[0][i] != NULL)
	{
		if (!ft_strcmp(get_key(line->piper[0][i], 0), "echo")
			|| !ft_strcmp(get_key(line->piper[0][i], 0), "env")
			|| !ft_strcmp(get_key(line->piper[0][i], 0), "pwd"))
		{
			piper_ops(line);
			line->exit_status = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

void	child_chk(t_read *line)
{
	if (is_there_redirection(line))
		return ;
	if (builtin_part1(line, line->piper[0]) == 1)
		line->exit_status = piper_ops(line);
	else
	{
		line->exit_status = 0;
	}
}

int	pipe_execution(t_read *line)
{
	if (line->heredocs[255] < 0)
	{
		if (line->heredocs[255] == HEREDOC_FAIL)
		{
			line->exit_status = EXIT_FAILURE;
			errno = 0;
			close_heredocs(line->heredocs, line->piper_len + 1);
			return (line->exit_status);
		}
		else
		{
			line->exit_status = -2;
			return (line->exit_status);
		}
	}
	if (line->piper_len < 2)
		child_chk(line);
	else
		line->exit_status = piper_ops(line);
	close_heredocs(line->heredocs, line->piper_len);
	return (line->exit_status);
}
