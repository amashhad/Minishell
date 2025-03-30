/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:26:42 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/30 22:46:42 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPANDER_H
# define FT_EXPANDER_H

# include "../srcs/minishell.h"

typedef struct s_expander
{
	size_t	j;
	size_t	i;
	size_t	i_result;
	size_t	count;
	size_t	k;
	char	*last_exit_code;
	char	*string;
	char	*argv;
	char	*quoted;
	char	*input;
	char	*var_name;
	char	*var_value;
	char	*result;
}			t_expand;

//int
int	comper_expander(char c);
int string_expander(char c);
//char
char	*ft_expander(char *input, char *last_exit_code, char *argv);
char	*get_string_expander(t_expand *pand);
//void
void	ft_free_expander(t_expand *pand, int error);
#endif
