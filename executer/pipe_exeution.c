/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exeution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:20:44 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/22 23:03:12 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_cmd1_operation(t_read *line, int pipe_fd[])
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute(line, line->piper[0], line->enviro);
}

void	ft_cmd2_operation(t_read *line, int pipe_fd[])
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute(line, line->piper[1], line->enviro);
}

int	no_pipe(t_read *line)
{
	pid_t	pid;
	int	status;

	if (builtin_part1(line, line->piper[0]) != 1)
		return (line->exit_status);
	pid = fork();
	if (pid == -1)
		ft_errmsg(line, "Fork Failed\n", -1);
	if (pid == 0)
		execute(line, line->piper[0], line->enviro);
	waitpid(pid, &status, 0);
	return (WIFEXITED(status));
}
//piper ops utils

void	middle_cmd(t_read *line, int write[2], int read[2], int cmd)
{
	if (cmd != line->piper_len)
	{
		close(write[0]);
		dup2(write[1], STDOUT_FILENO);
		close(write[1]);
	}
	if (cmd != 0)
	{
		close(read[1]);
		dup2(read[0], STDIN_FILENO);
		close(read[0]);
	}
	execute(line, line->piper[cmd], line->enviro);
}
void	last_cmd(t_read *line, int read[2], int write[2], int cmd)
{
	if (!cmd%2 && line->piper_len != 1)
	{
		close(write[1]);
		dup2(write[0], STDIN_FILENO);
		close(write[0]);
		close(read[1]);
		close(read[0]);
	}
	else if (line->piper_len != 1)
	{
		close(read[1]);
		dup2(read[0], STDIN_FILENO);
		close(read[0]);
		close(write[1]);
		close(write[0]);
	}
	execute(line, line->piper[cmd], line->enviro);
	ft_putendl_fd("Command not found", 2);
}
void	middle(t_read *line, int track, int pingpong[2][2])
{
	int	pid;

	if (track >= 2)
		{
			close(pingpong[track % 2][0]);
			close(pingpong[track % 2][1]);
		}
		pipe(pingpong[track % 2]);
		pid = fork();
		if (pid == -1)
			ft_errmsg(line, "Fork Failed\n", 1);
		if (pid == 0)
			middle_cmd(line, pingpong[track % 2], pingpong[(track + 1) % 2], track);
}
int	piper_ops(t_read *line)
{
	int		pingpong[2][2];
	int		status;
	int		track;
	pid_t	pid;

	track = 0;
	while (track < (line->piper_len - 1))
		middle(line, track++, pingpong);
	pid = fork();
	if (pid == -1)
		ft_errmsg(line, "Fork Failed\n", 1);
	if (pid == 0)
		last_cmd(line, pingpong[(track + 1) % 2], pingpong[(track) % 2], track);
	close_fds(pingpong, line->piper_len);
	while (wait(&status) > 0)
		;
	return (status);
}
///end of piper ops

int	pipe_execution(t_read *line)
{
	piper_ops(line);
	return (line->exit_status);
}
