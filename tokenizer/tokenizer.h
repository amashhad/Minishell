/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:30:31 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/19 18:03:38 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../srcs/minishell.h"

typedef struct s_token
{
	int		j;
	int		index;
	size_t		i;
	size_t		count;
	int		k;
	char		c;
	char		*input;
	char		**tokens;
}			t_tok;

char	**ft_tokenizer(char *input);
void	fill_tokens(t_tok *token);
void	quoted(t_tok *token);
void	fill_token(t_tok *token);
int		comper(char c);
void	string(t_tok *token);
void	piipe(t_tok *token);
void	greater(t_tok *token);
void	ft_free(t_tok *token);

#endif
