/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/02 20:03:51 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"
char	*check_quoted(char *str)
{
	char	*s;
	int	i;
	int	j;
	int	len;

	if (!str)
		return (NULL);
	j = 0;
	i = 0;
	len = ft_strlen(str);
	if (str[i] == '"' && str[len - 1] == '"')
	{
		s = malloc((len - 1) *sizeof(char));
		i++;
		while (j < (len - 1))
		{
			s[j] = str[i];
			i++;
			j++;
		}
		return (s);
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
	if (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
	{
		i++;
		endl++;
	}
	
	while (cmd[i])
	{
		ft_putstr(cmd[i]);
		i++;
	}
	if (endl == 0)
		ft_putchar('\n');
}
