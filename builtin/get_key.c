/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/30 18:15:38 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	check_quoted_1(char *serch, int i)
{
	if (is_odd(serch))
		return (1);
	i = 0;
	while (serch[i] != '\0')
	{
		if (chk_compare(serch[i]) && serch[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}

int	check_quoted_2(char *serch, int i)
{
	while (serch[i] != '\0')
	{
		if (serch[i] == '"')
		{
			i++;
			while (serch[i] != '"')
			{
				if (serch[i] == '\'')
					return (1);
				i++;
			}
		}
		if (serch[i] == '\'')
		{
			i++;
			while (serch[i] != '\'')
			{
				if (serch[i] == '"')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

static char	*fill_key(char *str, char *ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

static int	key_loop(char *serch)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (serch[i] != '\0')
	{
		if (serch[i] != '"' && serch[i] != '\'')
			j++;
		i++;
	}
	return (j);
}

char	*get_key(char *str, int c)
{
	char	*serch;
	char	*ret;
	int		j;

	j = 0;
	serch = get_serch(str, c);
	if (!serch)
		return (NULL);
	j = key_loop(serch);
	if (j == 0)
	{
		free (serch);
		return (NULL);
	}
	ret = malloc(sizeof(char ) * (j + 1));
	if (!ret)
	{
		free (serch);
		return ("Malloc Error\n");
	}
	ret = fill_key(serch, ret);
	free (serch);
	return (ret);
}
