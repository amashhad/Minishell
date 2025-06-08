/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 23:02:20 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/08 23:17:02 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig;

void	big_o_banner(void)
{
	ft_putendl_fd("\033[38;5;240m ____    (0)   "
		"  __________                ", 1);
	ft_putendl_fd("\033[38;5;240m|    )    __  "
		"  (   _______)             _____", 1);
	ft_putendl_fd("\033[38;5;240m|  _/    (  ) "
		"  |  |        _    ___    (  _  )", 1);
	ft_putendl_fd("\033[38;5;240m|   \\    |  | "
		"  |  |_______| |  (___)   ( (_) )  ", 1);
	ft_putendl_fd("\033[38;5;240m|____)   (__) "
		"  |____________|          (_____)  ", 1);
	ft_putendl_fd("\033[0m                 "
		"(BIG - O Minishell)       \n", 1);
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
		line->cwd = ft_remove_str(line->cwd,
				(ft_fetcharr(line->enviro, "HOME=") + 5));
		line->prompt = ft_joinstrjoin("Minishell>: ~", line->cwd, "$ ");
	}
	else
		line->prompt = ft_joinstrjoin("Minishell>:", temp, "$ ");
	if (!line->prompt || !line->cwd)
		ft_exit_with_error(line, "Unable to get prompt", "NULL", 2);
}

void	go_to_work(t_read *line, char **argv)
{
	while (1)
	{
		setup_signals(1);
		line->line = readline(line->prompt);
		if (g_sig == 1)
			line->exit_status = 130;
		g_sig = 0;
		add_history(line->line);
		line->line = ft_expander(line, ft_itoa(line->exit_status), argv[0]);
		line->tokens = ft_tokenizer(line);
		if (ft_exit_shell(line))
			break ;
		terminal_shell(line);
		ft_farray(line->tokens);
		free_piper(line);
		initialize_tok(line->token);
		if (line->line && *line->line)
		{
			free (line->line);
			line->pand->result = NULL;
		}
		if (g_sig != 2)
			g_sig = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_read	*line;

	line = malloc(sizeof(t_read));
	if (!line)
		exit (0);
	(void) argc;
	(void) argv;
	big_o_banner();
	initalization(line, envp);
	ft_get_prompt(line);
	go_to_work(line, argv);
	ft_exit_with_error(line, NULL, "NULL", line->exit_status);
	return (line->exit_status);
}
