/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:34:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/19 23:25:53 by amashhad         ###   ########.fr       */
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
	if (!line->prompt || !line->cwd)
		ft_exit_with_error(line, "Unable to get prompt");
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
		line.tokens = ft_tokenizer(line.line);
		//ft_expander(&line, line.exit_status);
		builtin(&line);
		//ft_putnbr_fd(ft_arr_srch("|", line.tokens), 1);
		ft_farray(line.tokens);
		free(line.line);
	}
	ft_exit_with_error(&line ,NULL);
	return (0);
}
