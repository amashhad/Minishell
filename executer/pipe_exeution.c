/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exeution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:20:44 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/24 04:52:38 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

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
void	cmd_loop(t_read *line, int track, int pingpong[2][2])
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
			cmd_chain(line, pingpong[track % 2], pingpong[(track + 1) % 2], track);
}
int	piper_ops(t_read *line)
{
	int		pingpong[2][2];
	int		status;
	int		track;
	pid_t	pid;

	track = 0;
	while (track < (line->piper_len - 1))
		cmd_loop(line, track++, pingpong);
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
