/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:26:45 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/07 22:06:52 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

static void	initialize(t_expand *pand)
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

char	*get_string_expander(t_expand *pand)
{
	pand->string = ft_calloc(pand->k + 1, sizeof(char));
	if (!pand->string)
		ft_free_expander(pand, 0);
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

void	var_expander(t_expand *pand)
{
    pand->j = pand->i + 1;
	while (string_expander(pand->input[pand->i + 1]))
		{
			pand->k++;
            pand->i++;
		}
        pand->var_name = get_string_expander(pand);
		pand->var_value = getenv(pand->var_name);
		free (pand->var_name);
		pand->var_name = NULL;
		pand->string = NULL;
        pand->count += ft_strlen(pand->var_value);
        pand->count--;
}

void	fill_expander(t_expand *pand)
{
	while (pand->input[pand->i] != '\0')
	{
		if (pand->input[pand->i] == '$')
			dollar_fill_expander(pand);
		else if (pand->input[pand->i] == '\'')
		{
			single_quoted(pand);
			pand->i++;
			fill_value_expander(pand, pand->quoted);
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

char	*ft_expander(char *input, char *last_exit_code, char *argv)
{
	t_expand	*pand;
	size_t	i;

	if (!input)
		return (NULL);
	pand = (t_expand *)malloc(sizeof(t_expand));
    if (!pand)
		ft_free_expander(pand, -1);
	i = 0;
	initialize(pand);
	pand->last_exit_code = last_exit_code;
	pand->argv = argv;
	pand->input = input;
	i = count_malloc(pand);
	initialize(pand);
	pand->result = ft_calloc(i + 1, sizeof(char));
	if (!(pand->result))
		ft_free_expander(pand, 0);
	pand->last_exit_code = last_exit_code;
	pand->argv = argv;
	pand->input = input;
	fill_expander(pand);
	pand->result[i] = '\0';
	free(input);
	free(last_exit_code);
	return (pand->result);
}

// int main(void)
// {
// 	t_expand	*pand;
// 	pand = (t_expand *)malloc(sizeof(t_expand));
//     if (!pand)
// 		exit (0);
//     ft_expander("  $$!$@$USER$ ali", "0", "dd", pand);
// 	printf("%s\n", pand->result);
// 	ft_free_expander(pand, 1);
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
