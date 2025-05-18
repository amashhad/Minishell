/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exeution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:20:44 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/16 19:56:51 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	handle_sigint1(int sig)
{
	(void)sig;
	printf("ali\n");
	g_sig = 1;
	
}
void	handle_sigquit1(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_putendl_fd("\nQuit (core dumped)", 1);
	rl_redisplay();
}

void	setup_signals1(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	g_sig = 1;
	exit (1);
	//signal(SIGQUIT, handle_sigint1);
}
void	last_cmd(t_read *line, int read[2], int write[2], int cmd)
{
	//setup_signals1();
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, handle_sigquit1);
	if (!cmd%2 && line->piper_len != 1)
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
	execute(line, line->piper[cmd], line->enviro);
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
			if (fcntl(STDERR_FILENO, F_GETFL) == -1)
				write(STDOUT_FILENO, "⚠️ stderr is closed\n", 21);
			last_cmd(line, pingpong[(track + 1) % 2], pingpong[(track) % 2], track);
			cmd_chain(line, pingpong[track % 2], pingpong[(track + 1) % 2], track);
		}
		ft_signal3(3);
}
int	piper_ops(t_read *line)
{
	int		pingpong[2][2];
	int		status;
	int		track;
	pid_t	pid; 
	pid_t	wpid;

	track = 0;
	while (track < (line->piper_len - 1))
		cmd_loop(line, track++, pingpong);
	pid = fork();
	if (pid == -1)
		ft_errmsg(line, "Fork Failed\n", 1);
	if (pid == 0)
	{
		setup_signals(2);
		last_cmd(line, pingpong[(track + 1) % 2], pingpong[(track) % 2], track);
	}
	ft_signal3(3);
	close_fds(pingpong, line->piper_len);
	close_heredocs(line->heredocs, line);
	
	while ((wpid = wait(&status)) > 0)
	{
		if (wpid == pid)
		{
			if (WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);
				if (sig == SIGQUIT)
					write(1, "Quit (core dumped)\n", 20);
				line->exit_status = 128 + sig;
			}
			else if (WIFEXITED(status))
				line->exit_status = WEXITSTATUS(status);
		}
	}
	return (line->exit_status);
}

///end of piper ops

void	close_heredocs(int *heredocs, t_read *line)
{
	int	i;

	i = 0;
	while (heredocs[i] > 0)
	{
		close(heredocs[i]);
		i++;
	}
	ft_bzero(line->heredocs, sizeof(line->heredocs));
}

int	pipe_execution(t_read *line)
{
	if (line->heredocs[255] < 0)
	{
		if (line->heredocs[255] == HEREDOC_FAIL)
		{
			line->exit_status = EXIT_FAILURE;
			errno = 0;
			close_heredocs(line->heredocs, line);
			return (line->exit_status);
		}
		else
		{
			line->exit_status = -2;
			ft_printf("Malloc Error in Heredoc Reading\n");
			return (line->exit_status);
		}
	}
	if (line->piper_len < 2)
	{
		if (builtin_part1(line, line->piper[0]) == 1)
			piper_ops(line);
		else
			line->exit_status = 0;
	}
	else
		piper_ops(line);
	return (line->exit_status);
}
