/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greater.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:55:17 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/19 17:55:43 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	greater(t_Tok *token)
{
	while (token->input[token->i] == '>' || token->input[token->i] == '<')
		{
			if (token->input[token->i] == token->input[token->i + 1])
			{
				token->i++;
				token->index++;
			}
			else
				token->index++;
			token->i++;
		}
}
