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
	size_t	i;
	char	c;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
		{
			c = str[i];
			while (str[i] != '\0')
			{
				i++;
				if (str[i] == c)
					break;
				if (str[i] == '\0')
					return (0);
			}
		}
		i++;
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

static	void	print_arg(char *str)
{
	char	c;
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
		{
			c = str[i];
			i++;
			while (str[i] != c)
			{
				write(1, &str[i], 1);
				i++;
			}
		}
		else
			write(1, &str[i], 1);
		i++;
	}
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
			print_arg(cmd[i]);
		else
			ft_putstr_fd("syntax error", 2);
		i++;
		if (cmd[i])
			ft_putchar(' ');
	}
	if (endl == 0)
		ft_putchar('\n');
}
