/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:59:19 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/11 10:58:11 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

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

static void	ft_export_success(t_read *line, char **cmd, int i)
{
	char	*srch;

	srch = NULL;
	if (ft_strchr(cmd[i], '='))
	{
		srch = rev_strchr(cmd[i], '=');
		if (ft_fetcharr(line->expo, srch))
			add_rplc(line, srch, cmd[i]);
		else
		{
			line->enviro = ft_addarr(cmd[i], line->enviro);
			line->expo = ft_addarr(cmd[i], line->expo);
			if (!line->expo || !line->enviro)
			{
				free(srch);
				ft_exit_with_error(line, "Malloc error", 1);
			}
		}
		free(srch);
	}
	else
		add_export(line, srch, cmd[i]);
}

static void	ft_export_err(t_read *line, char **cmd,  int i)
{
	ft_putstr_fd("Minishell: export: `" , 2);
	ft_putstr_fd(cmd[i], 2);
	ft_putendl_fd("': not a valid identifier", 2);
	line->exit_status = 1;
}

void	ft_handle_export(t_read *line, char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[1])
		ft_addprintarr("export ", line->expo);
	if (ft_fetcharr(cmd, "|"))
		return ;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "=", 1) ||
				ft_isdigit(cmd[i][0])
					|| !ft_strcmp(cmd[i], "="))
			ft_export_err(line, cmd, i);
		else
			{
				//write(1, "heress\n", 7);
				ft_export_success(line, cmd, i);
			}
		i++;
	}
}
