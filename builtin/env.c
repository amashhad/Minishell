/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:09:59 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/20 00:42:18 by alhamdan         ###   ########.fr       */
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
		if (get_value_of_export(arr[i], fetch))
			return (get_value_of_export(arr[i], fetch));
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
