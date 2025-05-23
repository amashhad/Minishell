/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:56:16 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 09:04:41 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

//Removes Heredoc and Delimiter from cmd line
char	**remove_heredoc(char **fetch)
{
	char	**temp;

	temp = NULL;
	while (ft_fetcharr(fetch, "<<"))
	{
		fetch = del_arr(fetch, fetch[ft_arr_srch("<<", fetch)]);
		fetch = del_arr(fetch, "<<");
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
