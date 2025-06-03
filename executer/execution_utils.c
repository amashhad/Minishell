/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:04:43 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/03 18:34:54 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

//checks if the command exists in relative path
int	ft_extra_chk(t_read *line, char *fcommand)
{
	if (!fcommand)
		execution_free(line, 0, NULL);
	if (access(fcommand, F_OK) == 0)
	{
		if (access(fcommand, X_OK) == -1)
			execution_free(line, 126,
				ft_joinstrjoin("minishell: ",
					fcommand, " : Permission denied"));
		return (access(fcommand, X_OK | R_OK));
	}
	return (1);
}

static char	**execute_utilns(t_read *line,
		char **redirect, char **cmd, int track)
{
	redirect = redirect_stdout(cmd);
	if (!redirect)
		ft_exit_with_error(line, NULL, NULL, 1);
	redirect = redirect_stdin(line, redirect, track);
	if (!redirect)
		ft_exit_with_error(line, NULL, NULL, 1);
	if (builtin_part1(line, redirect) != 10)
	{
		ft_farray(redirect);
		ft_exit_with_error(line, NULL, 0, 2);
	}
	return (redirect);
}

static char	*fill_exve(t_read *line, char **env, char **redirect)
{
	char	*exve;

	exve = NULL;
	if (!ft_extra_chk(line, redirect[0]))
		exve = token_without_quoted(redirect[0]);
	else
	{
		exve = token_without_quoted(redirect[0]);
		if (exve)
			exve = ft_find_executable(line, env, exve);
	}
	if (!exve)
	{
		ft_farray(redirect);
		ft_exit_with_error(line, ft_strjoin("Minisehll: command",
				" doesn't exist"), "NULL", 127);
	}
	return (exve);
}

void	execute(t_read *line, char **cmd, char **env, int track)
{
	char			*exve;
	char			**redirect;
	static int		exit_stat;

	redirect = NULL;
	exve = NULL;
	redirect = execute_utilns(line, redirect, cmd, track);
	if (!redirect)
		ft_exit_with_error(line, "NULL", "NULL", exit_stat);
	exve = fill_exve(line, env, redirect);
	close_heredocs(line->heredocs, line->piper_len);
	exit_stat = execve(exve, redirect, env);
	free(exve);
	ft_farray(redirect);
	ft_exit_with_error(line, NULL, "NULL", exit_stat);
}
