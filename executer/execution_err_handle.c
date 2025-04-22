/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_err_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:06:32 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/22 23:00:01 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_errmsg(t_read *line, char *msg, int errno)
{

	if ((errno == 42) | (errno == 127))
		ft_exit_with_error(line, msg, errno);
	else
	{
		perror("");
		ft_exit_with_error(line, NULL, errno);
	}
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
