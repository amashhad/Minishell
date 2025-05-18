/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:09:59 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/13 21:34:47 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*go_to_get(char **arr, char *fetch)
{
	int	i;

	i = 0;
	if (!fetch)
		return (NULL);
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		if (get_value_of_export(arr[i], fetch, ft_strlen(fetch)))
			return (get_value_of_export(arr[i], fetch, ft_strlen(fetch)));
		i++;
	}
	return (NULL);
}

void	ft_handle_env(t_read *line, char **cmd)
{
	if (cmd[1] != NULL)
	{
		ft_putstr_fd("env: `", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
		line->exit_status = 127;
	}
	else
		ft_printarr(line->enviro);
}

char	*ft_getenv(char **enviro, char *env)
{
	char	*ret;

	ret = go_to_get(enviro, env);
	return (ret);
}
