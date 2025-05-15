/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:04:43 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/15 22:22:40 by alhamdan         ###   ########.fr       */
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
}// if there is no any path for command or you delete path which check using it

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
	////////////////////////////////////////////////////////
	paths = ft_split((path + 5), ':');
	////////////////////fix this////////////////////////////
	if (!env[i] || !paths)
	{
		if (paths != NULL)
			ft_farray(paths);
		line->exit_status = -1;
		execution_free(line);
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
	// char	**redirect;

	// redirect = remove_redirect(cmd);
	if (!ft_extra_chk(line, cmd[0]))
		exve = ft_strdup(cmd[0]);
	else
		exve = ft_find_executable(line, env, cmd[0]);
	if (!exve)
	{
		line->exit_status = 127;
		ft_farray(cmd);
		execution_free(line);
		// free(line->pand);
		if (line->piper != NULL)
			free_piper(line);
		// printf("brah\n");
		exit(127);
	}
	line->exit_status = execve(exve, cmd, env);
	ft_farray(cmd);
	free(line->pand);
	free(exve);
	execution_free(line);
	exit(1);
}
