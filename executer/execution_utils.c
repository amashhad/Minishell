/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:04:43 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 03:27:26 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

//checks if the command exists in relative path
int	ft_extra_chk(t_read *line, char *fcommand)
{
	if (!fcommand)
		ft_errmsg(line, "Empty Command", 2);
	if (access(fcommand, F_OK) == 0)
		return (access(fcommand, X_OK | R_OK));
	else
		return (1);
}

char	**ft_get_paths(t_read *line, char **env)
{
	int		i;
	char	*path;
	char	**paths;

	i = -1;
	paths = NULL;
	path = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i];
			break ;
		}
	}
	if (!path)
		return (NULL);
	paths = ft_split((path + 5), ':');
	if (!env[i] || !paths)
	{
		if (paths != NULL)
			ft_farray(paths);
		execution_free(line, 2, "Err w/malloc");
	}
	return (paths);
}

char	*ft_find_executable(t_read *line, char **env, char *cmd)
{
	int		i;
	char	*full_path;
	char	*temp;
	char	**paths;

	i = 0;
	full_path = NULL;
	paths = NULL;
	temp = NULL;
	if (!env)
		return (NULL);
	paths = ft_get_paths(line, env);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		temp = ft_strjoin_gnl(paths[i], "/");
		full_path = ft_strjoin_gnl(temp, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	free(paths);
	return (NULL);
}

int	execute(t_read *line, char **cmd, char **env, int track)
{
	char	*exve;
	char	**redirect;
	int		exit_stat;

	exit_stat = 0;
	redirect = redirect_stdout(cmd);
	redirect = redirect_stdin(line, redirect, track);
	if (!redirect)
		exit(1);
	if (builtin_part1(line, redirect) != 1)
		exit(line->exit_status);
	if (!ft_extra_chk(line, redirect[0]))
		exve = ft_strdup(redirect[0]);
	else
		exve = ft_find_executable(line, env, redirect[0]);
	if (!exve)
		execution_free(line, exit_stat, ft_joinstrjoin("Minisehll: command ",
				redirect[0], " doesn't exist"));
	exit_stat = execve(exve, redirect, env);
	free_piper(line);
	ft_free_expander(line->pand);
	free(exve);
	execution_free(line, exit_stat, NULL);
	exit(exit_stat);
}
