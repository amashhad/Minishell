/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:53:24 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/19 17:53:35 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	string(t_tok *token)
{
	while (!(comper(token->input[token->i])))
		{
			if ((token->input[token->i] == '"' || token->input[token->i] == '\'') && token->input[token->i] != '\\')
			{
				token->c = token->input[token->i];
				token->i++;
				while ((token->input[token->i] != token->c || (token->input[token->i] == token->c && token->input[token->i - 1] == '\\')) && token->input[token->i] != '\0')
					token->i++;
			}
			if (comper(token->input[token->i + 1]))
			{
				token->index++;
			}
			token->i++;
		}
}
