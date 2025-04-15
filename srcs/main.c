/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:34:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/15 02:20:28 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initalization(t_read *line, char **envp)
{
	line->line = NULL;
	line->prompt = NULL;
	line->tokens = NULL;
	line->cwd = NULL;
	line->piper = NULL;
	line->enviro = ft_cpyarr(envp);
	line->exit_status = 0;
	line->piper_len = 0;
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
	if (ft_fetcharr(line->enviro, "HOME="))
	{
		line->cwd = ft_remove_str(line->cwd ,(ft_fetcharr(line->enviro, "HOME=") + 5));
		line->prompt = ft_joinstrjoin("Minishell>: ~", line->cwd, "$ ");
	}
	else
		line->prompt = ft_joinstrjoin("Minishell>:", temp, "$ ");
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
	int	i;

	i = 0;
	while (1)
	{
		line.line = readline(line.prompt);
		add_history(line.line);
		line.line = ft_expander(line.line, ft_itoa(line.exit_status), argv[0]);
		line.tokens = ft_tokenizer(line.line);
		if (ft_exit_shell(&line))
			break;
		terminal_shell(&line);
		//ft_printarr(line.tokens);
		free(line.line);
		ft_farray(line.tokens);
	}
	ft_exit_with_error(&line , NULL, 0);
	return (line.exit_status);
}
