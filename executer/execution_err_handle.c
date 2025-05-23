/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_err_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:06:32 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 08:33:25 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_errmsg(t_read *line, int pingpong[2][2], char *msg, int err)
{
	ft_putstr_fd(msg, 2);
	close_heredocs(line->heredocs, line->piper_len);
	close_fds(pingpong, line->piper_len);
	ft_exit_with_error(line, NULL, "NULL", err);
}

void	close_fds(int fds[2][2], int piper_len)
{
	if (piper_len > 1)
	{
		close(fds[0][0]);
		close(fds[0][1]);
		if (piper_len > 2)
		{
			close(fds[1][0]);
			close(fds[1][1]);
		}
	}
}
