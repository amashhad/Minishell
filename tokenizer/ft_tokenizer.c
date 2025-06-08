/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:34:37 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/05 21:19:06 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	initialize_tok(t_tok *token)
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

void	fill_token(t_read *line)
{
	if (line->token->index > line->token->k)
	{
		line->token->tokens[line->token->k]
			= ft_calloc((line->token->i - line->token->count + 1),
				sizeof(char));
		if (!line->token->tokens[line->token->k])
			ft_exit_with_error(line, "malloc error", "token", 2);
		line->token->j = 0;
		while (line->token->count < line->token->i)
		{
			line->token->tokens[line->token->k][line->token->j]
				= line->token->input[line->token->count];
			line->token->count++;
			line->token->j++;
		}
		line->token->tokens[line->token->k][line->token->j] = '\0';
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

void	fill_tokens(t_read *line)
{
	while (line->token->input[line->token->i] != '\0')
	{
		while (line->token->input[line->token->i] == ' '
			|| line->token->input[line->token->i] == '\t')
			line->token->i++;
		line->token->k = line->token->index;
		line->token->count = line->token->i;
		string_tokenizer(line->token);
		fill_token(line);
		line->token->k = line->token->index;
		line->token->count = line->token->i;
		pipe_tokenizer(line->token);
		fill_token(line);
		line->token->k = line->token->index;
		line->token->count = line->token->i;
		greater_tokenizer(line->token);
		fill_token(line);
		line->token->k = line->token->index;
		line->token->count = line->token->i;
		dollar_tokenizer(line->token);
		fill_token(line);
	}
}

char	**ft_tokenizer(t_read *line)
{
	size_t	i;

	if (!line->line)
		return (NULL);
	initialize_tok(line->token);
	line->token->input = line->line;
	i = count(line->token);
	initialize_tok(line->token);
	line->token->tokens = ft_calloc(i + 1, sizeof(char *));
	if (!(line->token->tokens))
		ft_exit_with_error(line, "malloc error", "NULL", 2);
	line->token->input = line->line;
	fill_tokens(line);
	line->token->tokens[i] = NULL;
	i = 0;
	if (line->token->error_token == 2)
	{
		ft_putendl_fd("syntax error", 2);
		line->exit_status = 2;
	}
	return (line->token->tokens);
}
