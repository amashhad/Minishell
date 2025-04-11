/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:06:44 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/11 19:34:10 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"
#include "sys/wait.h"

void	free_piper(t_read *line)
{
	int	len;

	len = 0;
	if (line->piper == NULL)
		return ;
	while (len < line->piper_len)
	{
		ft_farray(line->piper[len]);
		len++;
	}
	free(line->piper);
	line->piper = NULL;
	return ;
}

void	fill_piper(t_read *line)
{
	int		inner;
	int		outer;
	int		flag;

	inner = 0;
	outer = 0;
	flag = 0;
	while (line->tokens[inner])
	{
		if (!ft_strcmp(line->tokens[inner], "|"))
		{
			line->piper[outer] = ft_cpynarr(line->tokens + flag, (inner - flag));
			if (!line->piper[outer])
				ft_exit_with_error(line, "Malloc error", 2);
			flag = inner + 1;
			outer++;
		}
		inner++;
	}
	line->piper[outer] = ft_cpyarr(line->tokens + flag);
	if (!line->piper[outer])
		ft_exit_with_error(line, "Malloc error", 2);
	line->piper[outer + 1] = NULL;
}

int	prepare_piper(t_read *line)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (line->tokens[i])
	{
		if (ft_strcmp(line->tokens[i], "|") == 0)
			size++;
		i++;
	}
	line->piper = (char ***)malloc(sizeof(char **) * (size + 2)); //number of (pipes + 1) (+ 1 for NULL)
	if (!line->piper)
		ft_exit_with_error(line, "Piper Malloc Error", 2);
	line->piper_len = size + 2;
	fill_piper(line);
	return (size);
}
// void	close_pipes(int pipes[2][2])
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while(pipes[i])
// 	{
// 		if (pipes[i])
// 		{
// 			close(pipes[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }

int	execution(t_read *line)
{
	int	pipes[2][2];
	int	pid;
	int iterate;

	iterate = 0;
	while (line->piper[iterate])
	{
		if (iterate < line->piper_len)
			pipe(pipes[iterate%2]);
		pid = fork();
		if (pid == 0)
		{
			if (iterate > 0)
			{
				dup2(pipes[(iterate + 1)%2][0], STDERR_FILENO);
				close(pipes[(iterate + 1) % 2][0]);
			}
			if (line->piper[iterate + 1])
			{
				dup2(pipes[iterate % 2][1], STDOUT_FILENO);
				close(pipes[iterate % 2][1]);
			}
			//close_pipes(pipes);
			execve(line->piper[iterate][0], line->piper[iterate], line->enviro);
		}
		iterate++;
	}
	return (line->exit_status);
}
