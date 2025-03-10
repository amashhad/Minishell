/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:51:07 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/10 21:16:42 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char *str, char **arr)
{
	int	i;
	char	*srch;

	i = 0;
	while (arr[i] != NULL)
	{
		srch = rev_strchr(arr[i], '=');
		if (ft_strnstr(srch, str + 1, ft_strlen(srch)))
			break;
		free(srch);
		i++;
	}
	if (arr[i] == NULL)
	{
		free(str);
		str = ft_strdup("");
	}
	else
	{
		free(srch);
		free(str);
		str = ft_strdup(ft_strchr(arr[i], '=') + 1);
		return (str);
	}
	return (str);
}

void	ft_expander(t_read *line, int exit_status)
{
	int	i;

	i = 0;
	(void) exit_status;
	if (!line->tokens)
		return ;
	while (line->tokens[i] != NULL)
	{
		if (ft_strncmp(line->tokens[i], "$", 1) == 0)
		{
			line->tokens[i] = ft_expand(line->tokens[i], line->expo);
			if (!line->tokens[i])
				ft_exit_with_error(line, "Error with Malloc");
		}
		i++;
	}
}
