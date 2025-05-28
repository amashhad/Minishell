/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:04:43 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/28 14:45:53 by alhamdan         ###   ########.fr       */
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

void	execute(t_read *line, char **cmd, char **env, int track)
{
	char			*exve;
	char			**redirect;
	static int		exit_stat;

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
	if (!ft_extra_chk(line, redirect[0]))
		exve = ft_strdup(redirect[0]);
	else
		exve = ft_find_executable(line, env, redirect[0]);
	if (!exve)
	{
		ft_farray(redirect);
		ft_exit_with_error(line, ft_joinstrjoin("Minisehll: command ",
				"is", " doesn't exist"), "NULL", 127);
	}
	exit_stat = execve(exve, redirect, env);
	free(exve);
	ft_farray(redirect);
	ft_exit_with_error(line, "NULL", "NULL", exit_stat);
}
