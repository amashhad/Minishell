/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 02:36:32 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 01:26:59 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

//The command chain and condition
//if the cmd is an odd number, it opens the 2nd FD
//if the cmd is an even number, it opens the 1st FD
//counts from CMD{0}, as it is indexed
void	last_cmd(t_read *line, int read[2], int write[2], int cmd)
{
	if (!cmd % 2 && line->piper_len != 1)
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
	execute(line, line->piper[cmd], line->enviro, cmd);
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
	{
		ft_signal2(2);
		cmd_chain(line, pingpong[track % 2],
			pingpong[(track + 1) % 2], track);
	}
	ft_signal3(3);
}

void	cmd_chain(t_read *line, int write[2], int read[2], int cmd)
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
	execute(line, line->piper[cmd], line->enviro, cmd);
	exit(1);
}
