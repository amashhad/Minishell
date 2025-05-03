/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/03 14:05:55 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"
int	check_quoted(char *str)
{
	int	i;
	int	j;
	int	len;

	if (!str)
		return (0);
	j = 0;
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
	if (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
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
