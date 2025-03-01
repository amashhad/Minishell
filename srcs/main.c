/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:34:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/01 23:06:17 by amashhad         ###   ########.fr       */
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

char	*ft_get_prompt(void)
{
	char	*prompt;
	char	temp[PATH_MAX];

	getcwd(temp, sizeof(temp));
	prompt = ft_joinstrjoin("Minishell>:", temp, "$ ");
	if (!prompt)
	{
		ft_putendl_fd("Unable to get prompt", 2);
		exit(0);
	}
	return (prompt);
}

int		main(void)
{
	char	*line;
	char	*prompt;

	prompt = ft_get_prompt();
	while (1)
	{
		line = readline(prompt);
		if (!ft_exit_shell(line))
		{
			free(line);
			break;
		}
		add_history(line);
		ft_rev_str(line);
		free(line);
	}
	free(prompt);
	return (0);
}
