/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_chk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:59:08 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/20 07:29:05 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void line_atoi(t_read *line, char *str, int *fill)
{
	char *ptr;

	ptr = str;
	if (!str)
		return ;
	if (*ptr == '+' || *ptr == '-')
		ptr++;
	if (!ft_isdigit(*ptr))
		ft_exit_with_error(line, ft_joinstrjoin("minishell: exit: ",
				str, "numeric argument required"), NULL, 2);
	while (*ptr)
	{
		if (!ft_isdigit(*ptr))
			ft_exit_with_error(line, ft_joinstrjoin("minishell: exit: ",
				str, " numeric argument required"), NULL, 2);
		ptr++;
	}
	*fill = ft_atoi(str);
}

static int	ft_numeric(int i, t_read *line)
{
	int	numeric;

	numeric = 1;
	line_atoi(line, line->tokens[i], &numeric);
	if (line->tokens[i] && line->tokens[i + 1])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		line->exit_status = 1;
		return (-1);
	}
	if (numeric >= 0)
	{
		line->exit_status = (numeric%256);
		return (1);
	}
	else
	{
		line->exit_status = ((numeric + 256)%256);
		return (1);
	}
}

int	ft_exit_shell(t_read *line)
{
	int	i;

	i = 0;
	if (!line->line)
	{
		ft_putendl_fd("exit", 1);
		free(line->line);
		return (1);
	}
	if (!line->tokens)
		return (0);
	if ((ft_strcmp(line->tokens[i], "exit") == 0
			|| ft_strcmp(line->tokens[i], "'exit'") == 0)
		&& !ft_fetcharr(line->tokens, "|"))
	{
		i++;
		i = ft_numeric(i, line);
		if (i < 1)
			return (0);
		ft_putendl_fd("exit", 1);
		return (i);
	}
	return (0);
}
