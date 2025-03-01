/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:34:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/01 20:04:01 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rev_str(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i == 0)
		return ;
	while (i >= 0)
	{
		write(1, &str[i], 1);
		i--;
	}
	write(1, "\n", 1);
	return ;
}
int		main()
{
	char	*line;
	char	*dir;
	char	*temp;

	dir = NULL;
	dir = getcwd(dir, 100);
	temp = ft_strjoin("Minishell>:", dir);
	ft_putstr_fd(temp, 1);
	line = get_next_line(0);
	while (ft_strncmp(line, "exit\n", 5) != 0)
	{
		ft_rev_str(line);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	free(dir);
	free(temp);
	return (0);
}
