/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exeution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:20:44 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/28 15:23:17 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	handle_sigint1(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	setup_signals1(void)
{
	signal(SIGINT, handle_sigint1);
	signal(SIGQUIT, handle_sigint1);
}
void	last_cmd(t_read *line, int read[2], int write[2], int cmd)
{
	if (!cmd%2 && line->piper_len != 1)
	{
		close(write[1]);
		dup2(write[0], STDIN_FILENO);
		close(write[0]);
	}
	else if (line->piper_len != 1)
	{
		close(read[1]);
		dup2(read[0], STDIN_FILENO);
		close(read[0]);
	}
	execute(line, line->piper[cmd], line->enviro);
	//ft_putendl_fd("Command not found", 2);
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
	setup_signals1();
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
	if (line->piper_len < 2)
	{
		if (builtin_part1(line, line->piper[0]) == 1)
			piper_ops(line);
	}
	else
		piper_ops(line);
	return (line->exit_status);
}
