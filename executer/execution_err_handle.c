/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_err_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:06:32 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/15 10:46:03 by amashhad         ###   ########.fr       */
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

void	close_fds(int fds[2][2])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 2)
	{
		while (j < 2)
		{
			if (fds[i][j] != -1)
				close(fds[i][j]);
			j++;
		}
		i++;
	}
}
