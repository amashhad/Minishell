/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:34:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/22 11:08:18 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../builtin/builtin.h"

void	initalization(t_read *line, char **envp)
{
	line->line = NULL;
	line->prompt = NULL;
	line->tokens = NULL;
	line->cwd = NULL;
	line->enviro = ft_cpyarr(envp);
	line->exit_status = 0;
	if (!line->enviro)
	{
		ft_putendl_fd("Enviro err: no ENV variable or no memory", 2);
		exit (1);
	}
	line->expo = ft_cpyarr(line->enviro);
	if (!line->expo)
	{
		ft_putendl_fd("Expo err: no Memory for expo", 2);
		ft_farray(line->enviro);
		exit (1);
	}
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
	line->cwd = ft_remove_str(line->cwd ,(ft_fetcharr(line->enviro, "HOME=") + 5));
	line->prompt = ft_joinstrjoin("Minishell>: ~", line->cwd, "$ ");
	if (!line->prompt || !line->cwd)
		ft_exit_with_error(line, "Unable to get prompt", 1);
}

int		main(int argc, char **argv, char **envp)
{
	t_read	line;

	(void) argc;
	(void) argv;
	initalization(&line, envp);
	ft_get_prompt(&line);
	while (1)
	{
		line.line = readline(line.prompt);
		line.tokens = ft_tokenizer(line.line);
		if (ft_exit_shell(&line))
		{
			free(line.line);
			break;
		}
		add_history(line.line);
		//ft_expander(&line, line.exit_status);
		builtin(&line);
		//ft_executables();
		ft_farray(line.tokens);
		free(line.line);
	}
	ft_exit_with_error(&line , NULL, 0);
	return (line.exit_status);
}
