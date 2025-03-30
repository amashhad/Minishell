/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:30:31 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/30 22:13:57 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../srcs/minishell.h"

typedef struct s_token
{
	size_t	j;
	size_t	index;
	size_t	i;
	size_t	count;
	size_t	k;
	int		error_token;
	char	c;
	char	*input;
	char	**tokens;
}			t_tok;

char	**ft_tokenizer(char *input);
void	ft_free_tokenizer(t_tok *token, int error);
void	greater_tokenizer(t_tok *token);
void	pipe_tokenizer(t_tok *token);
void	dollar_tokenizer(t_tok *token);
void	string_tokenizer(t_tok *token);
#endif
