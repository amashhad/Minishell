/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:26:45 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/27 21:39:58 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

static size_t  ft_strlen(char *str)
{
   size_t   i;

    i = 0;
    if (!str)
        return (0);
    while (str[i] != '\0')
        i++;
    return (i);
}

static void    *ft_calloc(size_t count, size_t size)
{
    unsigned char   *p;
    void    		*pa;
    size_t			i;

    i = 0;
    pa = malloc(count * size);
    if (!pa)
        return (NULL);
    p = pa;
    while (i < (count * size))
    {
        p[i] = 0;
        i++;
    }
    return (pa);
}

static void	ft_free(t_Band *pand, int error)
{
	if (pand)
	{
		if (pand->var_name)
			free (pand->var_name);
		if (pand->string)
			free (pand->string);
		if (pand->quoted)
			free (pand->quoted);
		if (pand->result)
			free (pand->result);
		free(pand);
	}
	if (error == 0)
	{
		printf("The Malloc Not Located\n");
		exit (0);
	}
}

static void	initialize(t_Band *pand)
{
	pand->i = 0;
	pand->i_result = 0;
	pand->count = 0;
	pand->j = 0;
	pand->count = 0;
	pand->k = 0;
	pand->last_exit_code = NULL;
	pand->string = NULL;
	pand->argv = NULL;
	pand->quoted = NULL;
	pand->input = NULL;
	pand->var_name = NULL;
	pand->var_value = NULL;
	pand->result = NULL;
}

static int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static char	*get_string(t_Band *pand)
{
	pand->string = ft_calloc(pand->k + 1, sizeof(char));
	if (!pand->string)
		ft_free(pand, 0);
	pand->k = 0;
	while (pand->j <= pand->i)
	{
		pand->string[pand->k] = pand->input[pand->j];
		pand->k++;
		pand->j++;
	}
	pand->string[pand->k] = '\0';
	return (pand->string);
}

static void	fill_value(t_Band *pand, char *value)
{
	int	i;

	if (value)
	{
		i = 0;
		while (value[i] != '\0')
		{
			pand->result[pand->i_result] = value[i];
			i++;
			pand->i_result++;
		}
	}
}

static int	comper(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	if (c == ' ')
		return (1);
	if (c == '\0')
		return (1);
	if (c == '$')
		return (1);
    if (c == '"' || c == '\'')
		return (1);
	return (0);
}

static int string(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (1);
    if (c >= 'a' && c <= 'z')
        return (1);
    if (c >= '0' && c <= '9')
        return (1);
    if (c == '_')
        return (1);
    return (0);
}

static void	single_quoted(t_Band *pand)
{
	if (pand->input[pand->i] == '\'')
	{
		pand->j = pand->i;
		pand->i++;
		pand->count++;
		while (pand->input[pand->i] != '\'' && pand->input[pand->i] != '\0')
		{
			pand->count++;
			pand->i++;
			pand->k++;
		}
		if (pand->input[pand->i] == '\0')
		{
			pand->count--;
			pand->i--;
		}
		pand->quoted = get_string(pand);
		pand->string = NULL;
	}
}

static void	var(t_Band *pand)
{
    pand->j = pand->i + 1;
	while (string(pand->input[pand->i + 1]))
		{
			pand->k++;
            pand->i++;
		}
        pand->var_name = get_string(pand);
		pand->var_value = getenv(pand->var_name);
		free (pand->var_name);
		pand->var_name = NULL;
		pand->string = NULL;
        pand->count += ft_strlen(pand->var_value);
        pand->count--;
}

static void	dollar_malloc(t_Band *pand)
{
	if (pand->input[pand->i + 1] == '?')
	{
		pand->count += ft_strlen(pand->last_exit_code);
		pand->count -= 1;
		pand->i++;
	}
	else if (pand->input[pand->i + 1] == '$')
	{
		pand->count += 1;
		pand->i++;
	}
	else if (pand->input[pand->i + 1] == '0')
	{
		pand->count += ft_strlen(pand->argv);
		pand->count -= 1;
		pand->i++;
	}
	else if (ft_is_digit(pand->input[pand->i + 1]))
	{
		pand->count -= 1;
		pand->i += 1;
	}
	else if (!(string(pand->input[pand->i + 1])))
	{
		if (!(comper(pand->input[pand->i + 1])))
		{
			pand->count -= 1;
			pand->i += 1;
		}
	}
	else if (!(comper(pand->input[pand->i + 1])))
		var(pand);
}

static size_t	count_malloc(t_Band *pand)
{
	while (pand->input[pand->i] != '\0')
	{
		if (pand->input[pand->i] == '$')
            dollar_malloc(pand);
		single_quoted(pand);
		if (pand->quoted)
		{
			free (pand->quoted);
			pand->quoted = NULL;
		}
        pand->count++;
        pand->i++;
	}
	return (pand->count);
}

static void	dollar_fill(t_Band *pand)
{
	if (pand->input[pand->i + 1] == '?')
	{
		pand->i += 2;
		fill_value(pand, pand->last_exit_code);
	}
	else if (pand->input[pand->i + 1] == '$')
	{
		pand->i += 2;
		fill_value(pand, "$$");
	}
	else if (pand->input[pand->i + 1] == '0')
	{
		pand->i += 2;
		fill_value(pand, pand->argv);
	}
	else if (ft_is_digit(pand->input[pand->i + 1]))
		pand->i += 2;
	else if (!(string(pand->input[pand->i + 1])))
	{
		if (comper(pand->input[pand->i + 1]))
		{
			pand->result[pand->i_result] = pand->input[pand->i];
			pand->i_result++;
			pand->i++;
		}
		else
			pand->i += 2;
	}
	else if (!(comper(pand->input[pand->i + 1])))
	{
		var(pand);
		pand->i++;
		fill_value(pand, pand->var_value);
	}
	else
	{
		pand->result[pand->i_result] = pand->input[pand->i];
		pand->i_result++;
		pand->i++;
	}
}

static void	fill_pands(t_Band *pand)
{
	while (pand->input[pand->i] != '\0')
	{
		if (pand->input[pand->i] == '$')
			dollar_fill(pand);
		else if (pand->input[pand->i] == '\'')
		{
			single_quoted(pand);
			pand->i++;
			fill_value(pand, pand->quoted);
			free (pand->quoted);
			pand->quoted = NULL;
		}
		else
		{
			pand->result[pand->i_result] = pand->input[pand->i];
			pand->i_result++;
			pand->i++;
		}
	}
}

char	*ft_expander(char *input, char *last_exit_code, char *argv, t_Band *pand)
{
	//t_Band	*pand;
	size_t	i;

	//pand = (t_Band *)malloc(sizeof(t_Band));
    //if (!pand)
		//exit (0);
	i = 0;
	initialize(pand);
	pand->last_exit_code = last_exit_code;
	pand->argv = argv;
	pand->input = input;
	i = count_malloc(pand);
	printf("%ld\n", i);
	initialize(pand);
	pand->result = ft_calloc(i + 1, sizeof(char));
	if (!(pand->result))
		ft_free(pand, 0);
	pand->last_exit_code = last_exit_code;
	pand->argv = argv;
	pand->input = input;
	fill_pands(pand);
	pand->result[i] = '\0';
	return (pand->result);
}

// int main(void)
// {
// 	t_Band	*pand;
// 	pand = (t_Band *)malloc(sizeof(t_Band));
//     if (!pand)
// 		exit (0);
//     ft_expander("  $$!$@$USER$ ali", "0", "dd", pand);
// 	printf("%s\n", pand->result);
// 	ft_free(pand, 1);
//     return 0;
// }
/*int	main(int argc, char **argv)
{
	argc = argc + 1 - 1;
	char 	*line;
	char	*argvs;
	char	*token;

	argvs = argv[0];
	while (1)
	{
		line = readline("ali: ");

		token = ft_expander(line, "0", argvs);
		printf("%s\n", token);
	}
	return (0);
}*/
