/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:34:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/05 23:50:34 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initalization(t_read *line, char **envp)
{
	line->line = NULL;
	line->prompt = NULL;
	line->tokens = NULL;
	line->cwd = NULL;
	line->enviro = ft_cpyarr(envp);
	if (!line->enviro)
	{
		ft_putendl_fd("Enviro err: no ENV variable", 2);
		exit (1);
	}
	line->expo = ft_cpyarr(line->enviro);
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
	if (line->cwd)
		free(line->cwd);
	if (line->prompt)
		free(line->prompt);
	line->cwd = ft_strdup(temp);
	line->prompt = ft_joinstrjoin("Minishell>: ~", temp, "$ ");
	if (!line->prompt)
	{
		ft_putendl_fd("Unable to get prompt", 2);
		free(line->line);
		free(line->cwd);
		ft_farray(line->enviro);
		exit(0);
	}
}

int		main(int argc,char **argv, char **envp)
{
	t_read	line;
	char	**new_arr;

	(void) new_arr;
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
		line.tokens = history_tokenize(line.line);
		builtin(&line);
		//line.expo = ft_subarr("USER", line.expo);
		//ft_printarr(line.expo);
		ft_farray(line.tokens);
		free(line.line);
	}
	rl_clear_history();
	free(line.prompt);
	free(line.cwd);
	ft_farray(line.expo);
	ft_farray(line.enviro);
	return (0);
}
