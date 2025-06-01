/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/30 18:28:50 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

static	void	print_arg(char *str)
{
	char	c;
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\''))
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

int	check_redirections(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, "<"))
		return (1);
	if (!ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

static	void	go_to_print(char **cmd, int i)
{
	while (cmd[i])
	{
		print_arg(cmd[i]);
		i++;
		if (cmd[i])
			ft_putchar(' ');
	}
}

void	ft_handle_echo(char **cmd)
{
	int		i;
	int		endl;

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
	go_to_print(cmd, i);
	if (endl == 0)
		ft_putchar('\n');
}
