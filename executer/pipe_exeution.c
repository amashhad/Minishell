/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exeution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:20:44 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/03 21:26:05 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	piper_ops(t_read *line)
{
	int		pingpong[2][2];
	int		status;
	int		track;
	pid_t	pid;

	track = 0;
	while (track < (line->piper_len - 1))
		cmd_loop(line, track++, pingpong);
	if (track > 1)
	{
		close(pingpong[track % 2][0]);
		close(pingpong[track % 2][1]);
	}
	pid = fork();
	if (pid == -1)
		ft_errmsg(line, pingpong, "Fork Failed\n", 1);
	if (pid == 0)
	{
		//setup_signals(2);
		last_cmd(line, pingpong[(track + 1) % 2], pingpong[(track) % 2], track);
	}
	setup_signals(3);
	wait_children(line, &status, pingpong, pid);
	return (line->exit_status);
}

int	key_loop(t_read *line)
{
	char	*srch;
	int		i;

	srch = NULL;
	i = 0;
	while (line->piper[0][i] != NULL)
	{
		srch = token_without_quoted(line->piper[0][i]);
		if (!srch)
			return (1);
		if (!ft_strcmp(srch, "echo") || !ft_strcmp(srch, "env")
			|| !ft_strcmp(srch, "pwd") || !ft_strcmp(srch, "export"))
		{
			free(srch);
			piper_ops(line);
			line->exit_status = 0;
			return (1);
		}
		free(srch);
		i++;
	}
	return (0);
}

int	is_there_redirection(t_read *line)
{
	int		i;

	i = 0;
	while (line->piper[0][i] != NULL)
	{
		if (check_redirections(line->piper[0][i]))
			break ;
		i++;
	}
	if (line->piper[0][i] == NULL)
		return (0);
	return (key_loop(line));
}

void	child_chk(t_read *line)
{
	if (is_there_redirection(line))
		return ;
	if (builtin_part1(line, line->piper[0]) == 10)
		line->exit_status = piper_ops(line);
}

int	pipe_execution(t_read *line)
{
	if (line->piper_len < 2)
		child_chk(line);
	else
		line->exit_status = piper_ops(line);
	close_heredocs(line->heredocs, line->piper_len);
	return (line->exit_status);
}
