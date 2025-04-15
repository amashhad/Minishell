/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_err_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:06:32 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/14 05:22:01 by amashhad         ###   ########.fr       */
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

void	close_fds(int *fds, int fd_count)
{
	int	i;

	i = 0;
	while (i < fd_count)
	{
		if (fds[i] != -1)
			close(fds[i]);
		i++;
	}
}
