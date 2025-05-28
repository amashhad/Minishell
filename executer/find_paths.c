/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:32:37 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/28 19:58:47 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

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

static char	*pathing(char **paths, char *cmd)
{
	char	*temp;
	char	*full_path;
	int		i;

	temp = NULL;
	full_path = NULL;
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin_gnl(paths[i], "/");
		full_path = ft_strjoin_gnl(temp, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(cmd);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*ft_find_executable(t_read *line, char **env, char *cmd)
{
	char	**paths;
	char	*final_path;

	paths = NULL;
	final_path = NULL;
	if (!env)
		return (NULL);
	paths = ft_get_paths(line, env);
	if (!paths)
	{
		free(cmd);
		return (NULL);
	}
	final_path = pathing(paths, cmd);
	if (final_path)
		return (final_path);
	free(cmd);
	free(paths);
	return (NULL);
}
