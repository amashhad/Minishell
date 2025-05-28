/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:03:03 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/28 22:32:40 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

static int	check_name_of_key_number(char **arr, char *fetch)
{
	int	i;

	i = 0;
	if (!fetch)
		return (0);
	if (!arr)
		return (0);
	while (arr[i])
	{
		if (check_name(arr[i], fetch, ft_strlen(fetch)))
			return (i);
		i++;
	}
	return (0);
}

char	**rplc_env(char *fnd, char **old_arr, char *rplc)
{
	char	**new_arr;
	int		i;

	i = 0;
	if (!old_arr || *old_arr == NULL)
		return (NULL);
	if (!fnd || !rplc)
		return (old_arr);
	i = check_name_of_key_number(old_arr, fnd);
	if (!i)
		return (old_arr);
	free(old_arr[i]);
	copy_without_quoted(rplc, i, old_arr);
	new_arr = ft_cpyarr(old_arr);
	if (!new_arr)
		return (NULL);
	ft_farray(old_arr);
	return (new_arr);
}

char	**rplc_export(char *fnd, char **old_arr, char *rplc)
{
	char	**new_arr;
	int		i;

	i = 0;
	if (!old_arr || *old_arr == NULL)
		return (NULL);
	if (!fnd || !rplc)
		return (old_arr);
	i = check_name_of_key_number(old_arr, fnd);
	if (!i)
		return (old_arr);
	free(old_arr[i]);
	copy_without_quoted(rplc, i, old_arr);
	add_quoted_for_value(old_arr, i);
	new_arr = ft_cpyarr(old_arr);
	if (!new_arr)
		return (NULL);
	ft_farray(old_arr);
	return (new_arr);
}

char	*check_name(const char *big, const char *little, size_t len)
{
	size_t	c;

	c = 0;
	if (!big)
	{
		ft_putendl_fd("(get_value_of_export error)", 2);
		exit(1);
	}
	if (!*little)
		return (NULL);
	if (len == 0)
		return (NULL);
	while (little[c] != '\0')
	{
		if (big[c] == little[c])
			c++;
		else if (big[c] != little[c])
			return (NULL);
	}
	if (big[c] == '=' || big[c] == '\0')
		return ((char *)(big));
	return (NULL);
}

char	*check_name_of_key(char **arr, char *fetch)
{
	int	i;

	i = 0;
	if (!fetch)
		return (NULL);
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		if (check_name(arr[i], fetch, ft_strlen(fetch)))
			return (check_name(arr[i], fetch, ft_strlen(fetch)));
		i++;
	}
	return (NULL);
}
