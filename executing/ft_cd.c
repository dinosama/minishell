/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:31:39 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/29 19:09:19 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

static int	chdir_with_error(char *curpath, t_cmd *cmd)
{
	char	*oldpwd;
	char	*path;

	path = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", path);
	free(path);
	if (!chdir(curpath))
	{
		*(cmd->env) = add_env(*(cmd->env), oldpwd);
		free(oldpwd);
		return (0);
	}
	if (errno == EACCES || errno == EFAULT)
		write(STDERR_FILENO, "Access denied.\n", 15);
	if (errno == ELOOP || errno == ENAMETOOLONG)
		write(STDERR_FILENO, "Path too long or too much symbolic links.\n", 42);
	if (errno == ENOENT || errno == ENOTDIR)
		write(STDERR_FILENO,
			"The directory specified in path does not exist.\n", 48);
	if (errno == ENOMEM)
		write(STDERR_FILENO, "Insufficient kernel memory was available.\n", 42);
	free(oldpwd);
	return (1);
}

static int	special_cd(t_cmd *cmd, int spe)
{
	char	*curpath;
	int		res;

	if (!spe)
	{
		curpath = find_env("HOME", *cmd->env);
		if (!curpath)
			return (1 + 0 * write(STDERR_FILENO,
					"minishell: cd: << HOME >> non défini\n", 38));
	}
	else
	{
		curpath = find_env("OLDPWD", *cmd->env);
		if (!curpath)
			return (1 + 0 * write(STDERR_FILENO,
					"minishell: cd: << OLDPWD >> non défini\n", 40));
	}
	res = chdir_with_error(curpath, cmd);
	free(curpath);
	if (!res && spe)
		ft_pwd();
	return (res);
}

static void	free_all(char ***split, char *str1, char *str2, char *str3)
{
	free_split(split);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
}

static int	use_cdpath(char *op, char **paths, t_cmd *cmd)
{
	int		i;
	char	*path;
	char	*op2;
	char	*oldpwd;

	i = -1;
	op2 = ft_strjoin("/", op);
	path = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", path);
	while (paths[++i])
	{
		if (path)
			free(path);
		path = ft_strjoin(paths[i], op2);
		if (path && !chdir(path))
		{
			*cmd->env = add_env(*cmd->env, oldpwd);
			free_all(&paths, op2, path, oldpwd);
			return (1);
		}
	}
	free_all(&paths, op2, oldpwd, path);
	return (0);
}

int	ft_cd(t_cmd *cmd)
{
	char	*path;
	char	**paths;

	if (!cmd->args[1])
		return (special_cd(cmd, 0));
	else if (cmd->args[1][0] == '-')
		return (special_cd(cmd, 1));
	else if (cmd->args[1][0] != '/' && cmd->args[1][0] != '.')
	{
		path = find_env("CDPATH", *cmd->env);
		if (path)
		{
			paths = ft_split(path, ":");
			free(path);
			if (paths && use_cdpath(cmd->args[1], paths, cmd))
				return (0);
		}
	}
	return (chdir_with_error(cmd->args[1], cmd));
}
