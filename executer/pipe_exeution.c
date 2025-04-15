/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exeution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:20:44 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/15 23:18:58 by amashhad         ###   ########.fr       */
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
void	first_cmd(t_read *line, int read[2], int write[2], int cmd)
{
	(void)read;
	dup2(write[1], STDOUT_FILENO);
	close(write[0]);
	close(write[1]);
	execute(line, line->piper[cmd], line->enviro);
}

void	middle_cmd(t_read *line, int read[2], int write[2], int cmd)
{
	dup2(read[0], STDIN_FILENO);
	dup2(write[1], STDOUT_FILENO);
	close(read[0]);
	close(read[1]);
	close(write[0]);
	close(write[1]);
	execute(line, line->piper[cmd], line->enviro);
}
void	last_cmd(t_read *line, int read[2], int write[2], int cmd)
{
	int	*in_pipe;

	if (cmd % 2 == 0)
		in_pipe = write;
	else
		in_pipe = read;
	dup2(in_pipe[0], STDIN_FILENO);
	close(read[0]);
	close(read[1]);
	close(write[0]);
	close(write[1]);
	execute(line, line->piper[cmd], line->enviro);
}

int	piper_ops(t_read *line)
{
	int		pingpong[2][2];
	int		status;
	int		track;
	pid_t	pid;

	track = 0;
	if (pipe(pingpong[0]) == -1 || pipe(pingpong[1]) == -1)
		ft_errmsg(line, "Pipe Failed\n", 1);
	pid = fork();
	if (pid == -1)
		ft_errmsg(line, "Fork Failed\n", 1);
	if (pid == 0)
		first_cmd(line, pingpong[0], pingpong[1], 0);
	track++;
	while (track < (line->piper_len - 1))
	{
		pid = fork();
		if (pid == -1)
			ft_errmsg(line, "Fork Failed\n", 1);
		if (pid == 0)
			middle_cmd(line, pingpong[(track + 1) % 2], pingpong[track % 2], track);
		track++;
	}
	pid = fork();
	if (pid == -1)
		ft_errmsg(line, "Fork Failed\n", 1);
	if (pid == 0)
		last_cmd(line, pingpong[(track + 1) % 2], pingpong[track % 2], track);
	close_fds(pingpong);
	while (wait(&status) > 0)
		;
	return (status);
}
///end of piper ops

int	pipe_execution(t_read *line)
{
	// int	pipe_fd[2];
	// int	pid[line->piper_len - 2];
	// int	status;
	int	little;

	little = 0;
	if (little == line->piper_len - 2)
	{
		no_pipe(line);
		return (line->exit_status);
	}
	else
		piper_ops(line);
	// if ((line->piper_len - 2) % 2)
	// {
	// 	line->exit_status = piper_ops(line);
	// 	return (line->exit_status);
	// }
	// if (pipe(pipe_fd) == -1)
	// 	ft_errmsg("Pipe Failed\n", 32);
	// pid[0] = fork();
	// if (pid[0] == -1)
	// 	ft_errmsg("Fork Failed\n", -1);
	// if (pid[0] == 0)
	// 	ft_cmd1_operation(line, pipe_fd);
	// pid[1] = fork();
	// if (pid[1] == -1)
	// 	ft_errmsg("Fork Failed\n", -1);
	// if (pid[1] == 0)
	// 	ft_cmd2_operation(line, pipe_fd);
	// close_fds(pipe_fd, 2);
	// waitpid(pid[1], &status, 0);
	// if (WIFEXITED(status))
	// 	return (WEXITSTATUS(status));
	// return (128 + WTERMSIG(status));
	return (0);
}
