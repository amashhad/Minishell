/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:04:43 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/16 11:07:20 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	ft_extra_chk(t_read *line, char *fcommand)
{
	if (!fcommand)
		ft_errmsg(line, "Empty Command", 2);
	if (access(fcommand, F_OK) == 0)
	{
		return (access(fcommand, X_OK | R_OK));
	}
	else
		return (1);
}

char	**ft_get_paths(t_read *line, char **env)
{
	int		i;
	int		exit_stat;
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
	////////////////////////////////////////////////////////
	paths = ft_split((path + 5), ':');
	////////////////////fix this////////////////////////////
	if (!env[i] || !paths)
	{
		if (paths != NULL)
			ft_farray(paths);
		exit_stat = -1;
		execution_free(line, exit_stat);
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

int	execute(t_read *line, char **cmd, char **env)
{
	char	*exve;
	char	**redirect;
	int		exit_stat;

	exit_stat = 0;
	redirect = redirect_stdout(cmd);
	redirect = redirect_stdin(line, redirect);
	close_heredocs(line->heredocs, line);
	if (!redirect)
		exit(1);
	if (!ft_extra_chk(line, redirect[0]))
		exve = ft_strdup(redirect[0]);
	else
		exve = ft_find_executable(line, env, redirect[0]);
	if (!exve)
		execution_free(line, exit_stat);
	exit_stat = execve(exve, redirect, env);
	ft_farray(redirect);
	free(exve);
	execution_free(line, exit_stat);
	exit(1);
}
//	export x1="abc"
