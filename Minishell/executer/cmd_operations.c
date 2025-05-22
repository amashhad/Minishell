/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 02:36:32 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/19 15:16:28 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

//The command chain and condition
//if the cmd is an odd number, it opens the 2nd FD
//if the cmd is an even number, it opens the 1st FD
//counts from CMD{0}, as it is indexed
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
	execute(line, line->piper[cmd], line->enviro, cmd);
	exit(1);
}
