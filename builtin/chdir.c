/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:14:34 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/05 21:24:25 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

static	void	ft_chng_pwd(t_read *line)
{
	char	*srch;

	ft_get_prompt(line);
	srch = ft_strjoin("PWD=", line->cwd);
	if (check_name_of_key(line->expo, "PWD"))
		add_rplc(line, "PWD", srch);
	free(srch);
}

static	void	ft_get_new_cwd(t_read *line, char *srch)
{
	int	dir;
	int	i;

	i = 0;
	dir = 0;
	while (line->enviro[i] != NULL)
	{
		if (ft_strnstr(line->enviro[i], srch, ft_strlen(srch)))
			break ;
		i++;
	}
	if (line->enviro[i] == NULL)
	{
		ft_printf("Minishell: cd: %s: No such file or directory\n", srch);
		return ;
	}
	dir = chdir(ft_strchr(line->enviro[i], '=') + 1);
	if (dir < 0)
	{
		ft_printf("Minishell: cd: %s: No such file or directory\n", srch);
		return ;
	}
	ft_chng_pwd(line);
}

static	void	ft_old_cwd(t_read *line)
{
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", line->cwd);
	if (!old_pwd)
		ft_exit_with_error(line, "Strjoin Error w/PWD", "NULL", 1);
	line->enviro = ft_srchrarr("OLDPWD", line->enviro, old_pwd);
	if (!line->enviro || *line->expo == NULL)
		ft_exit_with_error(line, "old CWD err", "NULL", 1);
	line->expo = ft_srchrarr("OLDPWD", line->expo, old_pwd);
	if (!line->expo || *line->expo == NULL)
		ft_exit_with_error(line, "old CWD err", "NULL", 1);
	free(old_pwd);
	ft_get_new_cwd(line, "HOME=");
}

static	void	ft_path(t_read *line, char **cmd)
{
	int		dir;
	char	*old_pwd;
	char	*str;

	str = token_without_quoted(cmd[1]);
	dir = chdir(str);
	free(str);
	if (dir < 0)
	{
		ft_printf("Minishell: cd: %s: No such file or directory\n", cmd[1]);
		line->exit_status = 1;
		return ;
	}
	old_pwd = ft_strjoin("OLDPWD=", line->cwd);
	if (!old_pwd)
		ft_exit_with_error(line, "strjoin Error w/PWD", "NULL", 1);
	line->enviro = ft_srchrarr("OLDPWD=", line->enviro, old_pwd);
	if (!line->enviro || *line->enviro == NULL)
		ft_exit_with_error(line, "srchrarr error", "NULL", 1);
	line->expo = ft_srchrarr("OLDPWD=", line->expo, old_pwd);
	if (!line->expo || *line->expo == NULL)
		ft_exit_with_error(line, "srchrarr error", "NULL", 1);
	free(old_pwd);
	ft_chng_pwd(line);
}

void	ft_handle_cd(t_read *line, char **cmd)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (ft_fetcharr(cmd, "|"))
		return ;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("./Minishell: cd: too many arguments\n", 1);
		return ;
	}
	str = token_without_quoted(cmd[1]);
	if (cmd[1] == NULL || ft_strcmp("~", str) == 0)
	{
		free(str);
		ft_old_cwd(line);
	}
	else
	{
		free(str);
		ft_path(line, cmd);
	}
}
