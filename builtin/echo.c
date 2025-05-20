/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/13 20:10:14 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

static	int	check_quoted(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	i = 0;
	len = ft_strlen(str);
	if (str[i] == '"' && str[len - 1] == '"')
	{
		i++;
		while (i < (len - 1))
		{
			ft_putchar(str[i]);
			i++;
		}
		return (0);
	}
	return (1);
}

static int	is_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
	{
		i++;
		while (str[i] != '\0')
		{
			while (str[i] == 'n')
				i++;
			if (str[i] == '\0')
				return (1);
			return (0);
		}
	}
	return (0);
}

void	ft_handle_echo(char **cmd)
{
	int i;
	int	endl;

	i = 1;
	endl = 0;
	if (!cmd[i])
	{
		ft_putchar('\n');
		return ;
	}
	while (cmd[i] && is_n(cmd[i]) == 1)
	{
		i++;
		endl++;
	}
	while (cmd[i])
	{
		if (check_quoted(cmd[i]))
			ft_putstr(cmd[i]);
		i++;
		if (cmd[i])
			ft_putchar(' ');
	}
	if (endl == 0)
		ft_putchar('\n');
}
