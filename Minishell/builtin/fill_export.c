/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/03 21:47:36 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void    *add_quoted_for_value(char **arr, int size)
{
    char    *str;
    int     i;
    int     j;
    int     len;

    i = 0;
    j = 0;
    len = ft_strlen(arr[size]);
    str = malloc((len + 3) * sizeof(char));
    if (!str)
        return (NULL);
    while (arr[size][i] != '=')
    {
        str[j] = arr[size][i];
        j++;
        i++;
    }
    str[j] = arr[size][i];
    i++;
    j++;
    str[j] = '"';
    j++;
    while (arr[size][i] != '\0')
    {
        str[j] = arr[size][i];
        j++;
        i++;
    }
    str[j] = '"';
    j++;
    str[j] = '\0';
    arr[size] = ft_strdup(str);
    free (str);
    return (NULL);
}

char	**fill_export(char *str, char **old_arr)
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
	copy_without_quoted(str, size, arr);
	add_quoted_for_value(arr, size);
	arr[size + 1] = NULL;
	return (arr);
}
static  int is_odd(char *str)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '"')
        {
            j++;
        }
        if (str[i] == '\'')
        {
            k++;
        }
        i++;
    }
    if ((j % 2) != 0 || (k % 2) != 0)
        return (1);
    return (0);
}

static  int check_quoted_1(char *serch, int i)
{
    while (serch[i] != '\0')
    {
        if (ft_isspace(serch[i]))
            return (1);
        i++;
    }
    if (is_odd(serch))
        return (1);
    i = 0;
    while (serch[i] != '\0')
    {
        if (comper(serch[i]) && serch[i] != '\0')
            return (1);
        i++;
    }
    return (0);
}

static  int check_quoted_2(char *serch, int i)
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

static  char    *fill_key(char *str, char *ret)
{
    int i;
    int j;

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

char	*get_key(char *str, int c)
{
    char    *serch;
    char    *ret;
    int     i;
    int     j;

    i = 0;
    j = 0;
    if (c == 0)
    {
        serch = ft_strdup(str);
    }
    if (c != 0)
    {
        serch = rev_strchr(str, c);
    }
	if (check_quoted_1(serch, i) || check_quoted_2(serch, i))
        return (free (serch), NULL);
	while (serch[i] != '\0')
    {
        if (serch[i] != '"' && serch[i] != '\'')
            j++;
        i++;
    }
	if (j == 0)
		return (NULL);
    ret = malloc(sizeof(char ) * (j + 1));
    if (!ret)
        return (free (serch), "Malloc Error\n");
    ret = fill_key(serch, ret);
    free (serch);
    return (ret);
}