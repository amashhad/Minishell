/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exeution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:20:44 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/15 03:15:01 by amashhad         ###   ########.fr       */
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

int	piper_ops(t_read *line)
{
	int	pipe_fd[2];
	pid_t pid[line->piper_len - 2];
	int	little;
	int	status;

	little = 0;
	while (little < (line->piper_len - 2))
	{
		if (pipe(pipe_fd) == -1)
			ft_errmsg(line, "Pipe Failed\n", 32);
		pid[little] = fork();
		if (pid[little] == -1)
			ft_errmsg(line, "Fork Failed\n", -1);
		if (pid[little] == 0)
		{
			ft_putendl_fd("first", 1);
			ft_cmd1_operation(line, pipe_fd);
		}
		little++;
		pid[little] = fork();
		if (pid[little] == +-1)
			ft_errmsg(line, "Fork Failed\n", -1);
		if (pid[little] == 0)
		{
			ft_putendl_fd("second", 1);
			ft_cmd2_operation(line, pipe_fd);
		}
		little++;
		close_fds(pipe_fd, 2);
	}
	while (1)
	{
		if (waitpid((pid[line->piper_len - 2]), &status, 0))
			break;
	}
	return (status);
}

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
	else if ((line->piper_len - 2) % 2)
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
