/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_syntax_err.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:23:28 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/24 22:28:56 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	syntax_error_arrow(t_read *line)
{
	int	i;

	i = 0;
	while (line->line[i] != '\0')
	{
		if (line->line[i] == '<')
		{
			if (line->line[i + 1] == '>')
			{
				ft_putendl_fd("Syntax Error near token", 2);
				line->exit_status = 2;
				return ;
			}
		}
		i++;
	}
}

void	go_to_check_error_arrow(t_read *line)
{
	size_t	i;

	i = 0;
	while (line->line[i] != '\0')
	{
		if (line->line[i] == '>')
		{
			if (line->line[i + 1] == '<')
			{
				ft_putendl_fd("Syntax Error near token", 2);
				line->exit_status = 2;
				return ;
			}
		}
		i++;
	}
	syntax_error_arrow(line);
}

void	go_to_check_arrow_two(t_read *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line->line[i] != '\0')
	{
		if (line->line[i] == '<')
			j++;
		if (line->line[i] == ' ')
			j = 0;
		if (j > 2)
		{
			ft_putendl_fd("Syntax Error near token", 2);
			line->exit_status = 2;
			return ;
		}
		i++;
	}
}

void	go_to_check_arrow(t_read *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line->line[i] != '\0')
	{
		if (line->line[i] == '>')
			j++;
		if (line->line[i] == ' ')
			j = 0;
		if (j > 2)
		{
			ft_putendl_fd("Syntax Error near token", 2);
			line->exit_status = 2;
			return ;
		}
		i++;
	}
	go_to_check_arrow_two(line);
	go_to_check_error_arrow(line);
}
