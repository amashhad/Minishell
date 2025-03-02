/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:34:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/02 23:57:51 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initalization(t_read *line, char **envp)
{
	line->line = NULL;
	line->prompt = NULL;
	line->pipes[0] = 0;
	line->pipes[1] = 0;
	line->enviro = ft_cpyarr(envp);
	if (!line->enviro)
	{
		ft_putendl_fd("Enviro err: no ENV variable", 2);
		exit (1);
	}
}

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

void	ft_get_prompt(t_read *line)
{
	char	temp[PATH_MAX];

	getcwd(temp, sizeof(temp));
	line->prompt = ft_joinstrjoin("Minishell>:", temp, "$ ");
	if (!line->prompt)
	{
		ft_putendl_fd("Unable to get prompt", 2);
		free(line->line);
		ft_farray(line->enviro);
		exit(0);
	}
}

int		main(int argc,char **argv, char **envp)
{
	t_read	line;

	(void) argc;
	(void) argv;
	initalization(&line, envp);
	ft_get_prompt(&line);
	while (1)
	{
		line.line = readline(line.prompt);
		if (!ft_exit_shell(line.line))
		{
			free(line.line);
			break;
		}
		add_history(line.line);
		ft_rev_str(line.line);
		minipipex();
		free(line.line);
	}
	rl_clear_history();
	free(line.prompt);
	ft_farray(line.enviro);
	return (0);
}
