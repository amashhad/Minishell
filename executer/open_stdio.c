/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_stdio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:03:29 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/20 01:35:24 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

//opens and closes fds, only dups when flag is != 0
int	open_stdin(char *cmd)
{
	char	*str;
	int		fd;

	str = token_without_quoted(cmd);
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		perror(str);
		free(str);
		return (-1);
	}
	free(str);
	return (fd);
}

//opens and closes fds, only dups when flag is != 0
int	open_stdout(char **cmd, int *close_flag)
{
	char	*str;
	int		fd;

	str = token_without_quoted(cmd[1]);
	fd = 0;
	if (ft_strcmp(">", cmd[0]) == 0)
		fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(str);
		free(str);
		return (-1);
	}
	if (*(close_flag) != 0)
	{
		dup2(fd, STDOUT_FILENO);
		*(close_flag) = 0;
	}
	close(fd);
	free(str);
	return (0);
}
