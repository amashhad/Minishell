/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:26:42 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/27 22:09:19 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPANDER_H
#define FT_EXPANDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

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
}			t_Band;
char	*ft_expander(char *input, char *last_exit_code, char *argv, t_Band *pand);
#endif
