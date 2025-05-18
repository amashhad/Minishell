/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 02:36:32 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/16 03:45:46 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

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
