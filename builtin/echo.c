/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/22 06:39:10 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*ft_findquote(t_read *line, char *token)
{
	//int	i;
	//int	count;
	char	*str;

	//i = 0;
	(void )line;
	if (!token)
		return (NULL);
	str = ft_strtrim(token, "\"");
	if (!str)
	{
		free(token);
		return (NULL);
	}
	free(token);
	return (str);
}

void	ft_handle_echo(t_read *line)
{
	int	i;
	int	mode;

	i = 1;
	mode = 0;
	if (ft_strcmp(line->tokens[i], "-n") == 0)
	{
		mode++;
		i++;
	}
	while (line->tokens[i] && ft_strcmp(line->tokens[i], "|") != 0)
	{
		line->tokens[i] = ft_findquote(line, line->tokens[i]);
		//ft_fill_echo(line, line->tokens[i]);
		ft_putstr(line->tokens[i]);
		ft_putchar(' ');
		i++;
	}
	if (mode == 0)
		ft_putchar_fd('\n', 1);
}
