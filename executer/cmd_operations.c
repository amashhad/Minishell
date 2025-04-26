/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 02:36:32 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/26 03:15:48 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

// void	ft_cmd1_operation(t_read *line, int pipe_fd[])
// {
// 	dup2(pipe_fd[1], STDOUT_FILENO);
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// 	execute(line, line->piper[0], line->enviro);
// }

// void	ft_cmd2_operation(t_read *line, int pipe_fd[])
// {
// 	dup2(pipe_fd[0], STDIN_FILENO);
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// 	execute(line, line->piper[1], line->enviro);
// }
int	redirection_chk(t_read *line, int cmd)
{
	int	srch;
	int fd;

	fd = 0;
	srch = 0;
	if (ft_fetcharr(line->piper[cmd], ">"))
	{
		srch = ft_arr_srch(">", line->piper[cmd]);
		fd = open(line->piper[cmd][srch + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		return (fd);
	}
	return (fd);
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
	if (builtin_part1(line, line->piper[cmd]) == 1)
		execute(line, line->piper[cmd], line->enviro);
	
	exit(1);
}
