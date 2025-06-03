/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:56:16 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/03 19:41:51 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

//Removes Heredoc and Delimiter from cmd line
char	**remove_heredoc(char **fetch)
{
	char	**temp;
	int		i;

	temp = NULL;
	i = 0;
	while (ft_fetcharr(fetch, "<<"))
	{
		if (!*fetch)
			return (NULL);
		if ((ft_strcmp("<<", fetch[i]) == 0))
		{
			fetch = del_arr(fetch, i);
			fetch = del_arr(fetch, i);
			if (!fetch)
				return (NULL);
			continue ;
		}
		i++;
	}
	temp = ft_cpyarr(fetch);
	ft_farray(fetch);
	return (temp);
}

//checks for heredocs, dup2s the ones that are ok
//pipes stop it, aka turn based pipes
int	check_heredocs(t_read *line, int heredoc, char ***fetch, int track)
{
	if (heredoc != 1)
	{
		(*fetch) = remove_heredoc(*fetch);
		return (line->old_fd);
	}
	close(line->old_fd);
	(*fetch) = remove_heredoc(*fetch);
	return (line->heredocs[track]);
}
