/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:34:37 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/31 19:02:26 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	initialize(t_tok *token)
{
	token->i = 0;
	token->index = 0;
	token->j = 0;
	token->count = 0;
	token->k = 0;
	token->error_token = 1;
	token->c = '\0';
	token->input = NULL;
	token->tokens = NULL;
}

void	fill_token(t_tok *token)
{
	if (token->index > token->k)
	{
		token->tokens[token->k] = ft_calloc((token->i - token->count + 1),
				sizeof(char));
		if (!token->tokens[token->k])
			ft_free_tokenizer(token, 0);
		token->j = 0;
		while (token->count < token->i)
		{
			token->tokens[token->k][token->j] = token->input[token->count];
			token->count++;
			token->j++;
		}
		token->tokens[token->k][token->j] = '\0';
	}
}

size_t	count(t_tok *token)
{
	while (token->input[token->i] != '\0')
	{
		while (token->input[token->i] == ' ' || token->input[token->i] == '\t')
		{
			token->i++;
		}
		string_tokenizer(token);
		pipe_tokenizer(token);
		greater_tokenizer(token);
		dollar_tokenizer(token);
	}
	return (token->index++);
}

void	fill_tokens(t_tok *token)
{
	while (token->input[token->i] != '\0')
	{
		while (token->input[token->i] == ' ' || token->input[token->i] == '\t')
			token->i++;
		token->k = token->index;
		token->count = token->i;
		string_tokenizer(token);
		fill_token(token);
		token->k = token->index;
		token->count = token->i;
		pipe_tokenizer(token);
		fill_token(token);
		token->k = token->index;
		token->count = token->i;
		greater_tokenizer(token);
		fill_token(token);
		token->k = token->index;
		token->count = token->i;
		dollar_tokenizer(token);
		fill_token(token);
	}
}

char	**ft_tokenizer(char *input)
{
	t_tok	*token;
	size_t	i;

	token = (t_tok *)malloc(sizeof(t_tok));
	initialize(token);
	token->input = input;
	i = count(token);
	initialize(token);
	token->tokens = ft_calloc(i + 1, sizeof(char *));
	if (!(token->tokens))
		ft_free_tokenizer(token, 0);
	token->input = input;
	fill_tokens(token);
	free(input);
	token->tokens[i] = NULL;
	return (token->tokens);
}
