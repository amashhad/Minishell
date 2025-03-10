/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_chk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:59:08 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/10 22:34:34 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_shell(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (ft_isspace(line[i]))
		i++;
	return (ft_strcmp(line + i, "exit"));
}
