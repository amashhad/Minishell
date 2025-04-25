/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:04:43 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/24 06:17:02 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	ft_extra_chk(t_read *line, char *fcommand)
{
	if (!fcommand)
		ft_errmsg(line, "MT", 2);
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
	char	*path;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i];
			break ;
		}
		i++;
	}
	if (!env[i])
	{
		ft_errmsg(line, "No Path Variable.\n", -1);
		exit(-1);
	}
	paths = ft_split((path + 5), ':');
	if (!paths)
		ft_errmsg(line, "Could not find path.\n", -1);
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
char **remove_redirect(char **cmd)
{
	char	**redirect;
	int		srch;

	srch = 0;
	if (!ft_fetcharr(cmd, ">") || !ft_fetcharr(cmd, ">>")
		|| !ft_fetcharr(cmd, "<") || !ft_fetcharr(cmd, "<<"))
	{
		redirect = ft_cpyarr(cmd);
		return (redirect);
	}
	srch = ft_arr_srch(">", cmd);
	redirect = ft_cpynarr(cmd, srch);
	ft_printarr(redirect);
	return (redirect);
}

int	execute(t_read *line, char **cmd, char **env)
{
	char	*exve;
	char	**redirect;

	redirect = remove_redirect(cmd);
	if (!ft_extra_chk(line, redirect[0]))
		exve = ft_strdup(redirect[0]);
	else
		exve = ft_find_executable(line, env, redirect[0]);
	if (!exve)
		ft_errmsg(line, "Command not found || Invalid Command\n", 127);
	line->exit_status = execve(exve, redirect, env);
	ft_farray(redirect);
	free(exve);
	execution_free(line);
	exit(1);
}
