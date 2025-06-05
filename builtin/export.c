/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:59:19 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/05 18:04:20 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	add_rplc(t_read *line, char *srch, char *rplc)
{
	line->expo = rplc_export(srch, line->expo, rplc);
	if (ft_fetcharr(line->enviro, srch))
		line->enviro = rplc_env(srch, line->enviro, rplc);
	else
		line->enviro = ft_addarr(rplc, line->enviro);
	if (!line->expo || !line->enviro)
	{
		free(srch);
		line->exit_status = 1;
		ft_exit_with_error(line, "Malloc Error", "NULL", 1);
	}
}

static	int	fill_or_rplc(t_read *line, char *cmd, char *srch)
{
	if (!srch || !(ft_strcmp(srch, "Malloc Error\n")))
	{
		printf("The Key Not Valid\n");
		return (1);
	}
	if (check_name_of_key(line->expo, srch))
		add_rplc(line, srch, cmd);
	else
	{
		line->enviro = fill_env(cmd, line->enviro);
		line->expo = fill_export(cmd, line->expo);
		if (!line->expo || !line->enviro)
		{
			free(srch);
			ft_exit_with_error(line, "Malloc error", "NULL", 1);
		}
	}
	free(srch);
	return (0);
}

static void	ft_export_success(t_read *line, char *cmd)
{
	char	*srch;

	srch = NULL;
	if (ft_strchr(cmd, '='))
	{
		srch = get_key(cmd);
		if (fill_or_rplc(line, cmd, srch))
			return ;
	}
	else
	{
		if (!(check_name_of_key(line->expo, cmd)))
			line->expo = ft_addarr(cmd, line->expo);
	}
}

static void	ft_export_err(t_read *line, char **cmd, int i)
{
	ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(cmd[i], 2);
	ft_putendl_fd("': not a valid identifier", 2);
	line->exit_status = 1;
}

void	ft_handle_export(t_read *line, char **cmd)
{
	char	*str;
	int		i;

	i = 1;
	str = NULL;
	if (!cmd[1])
		ft_addprintarr("export ", line->expo);
	while (cmd[i])
	{
		if (check_redirections(cmd[i]))
			break ;
		str = token_without_quoted(cmd[i]);
		if (is_valid_export_key(str))
			ft_export_err(line, cmd, i);
		else if (is_valid_export_value(cmd[i]))
			ft_export_err(line, cmd, i);
		else
			ft_export_success(line, str);
		free(str);
		i++;
	}
}
