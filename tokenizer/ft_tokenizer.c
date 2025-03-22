/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:56:57 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/22 08:57:32 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	ft_free(t_tok *token)
{
	int	i;

	if (token->tokens)
	{
		i = 0;
		while (token->tokens[i])
		{
			free(token->tokens[i]);
			i++;
		}
		free(token->tokens);
	}
	free (token);
	return ;
}

void	initialize(t_tok *token, int i)
{
	token->i = 0;
	token->index = 0;
	token->j = 0;
	token->count = 0;
	token->k = 0;
	token->c = '\0';
	token->input = "\0";
	token->tokens = NULL;
	token->tokens = malloc((i + 1) * sizeof(char *));

}

int	count(t_tok *token)
{
	while (token->input[token->i] != '\0')
	{
		while (token->input[token->i] == ' ' || token->input[token->i] == '\t')
		{
			token->i++;
		}
		quoted(token);
		string(token);
		piipe(token);
		greater(token);
	}
	return (token->index++);
}

char	**ft_tokenizer(char *input)
{
	t_tok	*token;
	char	**ret;
	int	i;

	i = 0;
	if (!input)
		return (NULL);
	token = ft_calloc(1, sizeof(t_tok));
    if (!token)
		return (NULL);
	token->input = input;
	i = count(token);
	initialize(token, i);
	if (!(token->tokens))
	{
		ft_free(token);
		return (NULL);
	}
	token->input = input;
	fill_tokens(token);
	token->tokens[i] = NULL;
	ret = ft_cpyarr(token->tokens);
	ft_farray(token->tokens);
	free(token);
	return (ret);
}
