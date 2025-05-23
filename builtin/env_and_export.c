/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 13:36:16 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

static int	get_length(char *str)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (!comper(str[i]))
	{
		if ((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
		{
			c = str[i];
			i++;
			count_in_side_quoted(str, c, &i, &j);
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

static char	*fill_string(char *str, char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (!comper(str[i]))
	{
		if ((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
		{
			fill_in_side_quoted(str, s, &i, &j);
		}
		else
		{
			s[j] = str[i];
			j++;
			i++;
		}
	}
	return (s);
}

void	*copy_without_quoted(char *str, int size, char **arr)
{
	char	*s;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	i = get_length(str);
	s = malloc((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s = fill_string(str, s);
	s[i] = '\0';
	arr[size] = ft_strdup(s);
	free (s);
	return (NULL);
}

char	**fill_env(char *str, char **old_arr)
{
	int		i;
	int		size;
	char	**arr;

	i = 0;
	size = ft_arrlen(old_arr);
	arr = malloc(sizeof(char *) * (size + 2));
	if (!arr)
		return (NULL);
	while (old_arr[i] != NULL)
	{
		arr[i] = ft_strdup(old_arr[i]);
		i++;
	}
	ft_farray(old_arr);
	copy_without_quoted(str, size, arr);
	arr[size + 1] = NULL;
	return (arr);
}
