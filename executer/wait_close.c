/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:53:43 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 03:28:24 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	wait_children(t_read *line, int *status, int pingpong[2][2], pid_t pid)
{
	int		sig;
	pid_t	wpid;

	wpid = 1;
	sig = WTERMSIG(*status);
	close_fds(pingpong, line->piper_len);
	close_heredocs(line->heredocs, line->piper_len);
	while (wpid > 0)
	{
		wpid = wait(status);
		if (wpid == pid)
		{
			if (WIFSIGNALED(*status))
			{
				sig = WTERMSIG(*status);
				if (sig == SIGQUIT)
					write(1, "Quit (core dumped)\n", 20);
				line->exit_status = 128 + sig;
			}
			else if (WIFEXITED(*status))
				line->exit_status = WEXITSTATUS(*status);
		}
	}
}
