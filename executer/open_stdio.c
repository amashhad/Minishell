/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_stdio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:03:29 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 03:28:51 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

//opens and closes fds, only dups when flag is != 0
int	open_stdin(char *cmd)
{
	int	fd;

	fd = open(cmd, O_RDONLY);
	if (fd < 0)
	{
		perror(cmd);
		exit(1);
	}
	return (fd);
}

//opens and closes fds, only dups when flag is != 0
int	open_stdout(char **cmd, int close_flag)
{
	int	fd;

	fd = 0;
	if (ft_strcmp(">", cmd[0]) == 0)
		fd = open(cmd[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(cmd[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(cmd[1]);
		exit(1);
	}
	if (close_flag != 0)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
