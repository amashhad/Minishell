/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:59:19 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/22 15:44:42 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void add_export(t_read *line, char *srch, char *rplc)
{
	if (ft_fetcharr(line->expo, srch))
		line->expo = ft_srchrarr(srch, line->expo, rplc);
	else
		line->expo = ft_addarr(rplc, line->expo);
	if (!line->expo)
	{
		free(srch);
		line->exit_status = 1;
		ft_exit_with_error(line, "Malloc Error", 1);
	}
	free(srch);
}

static void	add_rplc(t_read *line, char *srch, char *rplc)
{
	line->expo = ft_srchrarr(srch, line->expo, rplc);
	if (ft_fetcharr(line->enviro, srch))
		line->enviro = ft_srchrarr(srch, line->enviro, rplc);
	else
		line->enviro = ft_addarr(rplc, line->enviro);
	if (!line->expo || !line->enviro)
	{
		free(srch);
		line->exit_status = 1;
		ft_exit_with_error(line, "Malloc Error", 1);
	}
}

static void	ft_export_success(t_read *line, int i)
{
	char	*srch;

	srch = NULL;
	if (ft_strchr(line->tokens[i], '='))
	{
		srch = rev_strchr(line->tokens[i], '=');
		if (ft_fetcharr(line->expo, srch))
			add_rplc(line, srch, line->tokens[i]);
		else
		{
			line->enviro = ft_addarr(line->tokens[i], line->enviro);
			line->expo = ft_addarr(line->tokens[i], line->expo);
			if (!line->expo || !line->enviro)
			{
				free(srch);
				ft_exit_with_error(line, "Malloc error", 1);
			}
		}
		free(srch);
	}
	else
		add_export(line, srch, line->tokens[i]);
}

static void	ft_export_err(t_read *line, int i)
{
	ft_putstr_fd("Minishell: export: `" , 2);
	ft_putstr_fd(line->tokens[i], 2);
	ft_putendl_fd("': not a valid identifier", 2);
	line->exit_status = 1;
}

void	ft_handle_export(t_read *line)
{
	int	i;

	i = 1;
	if (!line->tokens[1])
		ft_addprintarr("declare -x", line->expo);
	if (ft_fetcharr(line->tokens, "|"))
		return ;
	while (line->tokens[i])
	{
		if (!ft_strncmp(line->tokens[i], "=", 1) ||
				ft_isdigit(line->tokens[i][0])
					|| !ft_strcmp(line->tokens[i], "="))
			ft_export_err(line, i);
		else
			{
				//write(1, "heress\n", 7);
				ft_export_success(line, i);
			}
		i++;
	}
}
