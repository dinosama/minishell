/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 12:56:32 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/28 20:55:49 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	ft_pwd(void)
{
	char	*res;

	res = getcwd(NULL, 0);
	if (res == NULL)
	{
		if (errno == ENOENT)
			write(STDERR_FILENO,
				"The current working directory has been unlinked.\n", 49);
		if (errno == ENOMEM)
			write(STDERR_FILENO, "Out of memory.\n", 15);
		if (errno == EACCES)
			write(STDERR_FILENO,
				"Permission to read or search path denied.\n", 42);
		return (errno);
	}
	write(STDOUT_FILENO, res, ft_strlen(res));
	write(STDOUT_FILENO, "\n", 1);
	free(res);
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	optn;

	i = 0;
	optn = 0;
	while (cmd->args[++i])
	{
		if (i == 1 && !ft_strcmp(cmd->args[1], "-n"))
			optn = 1;
		else
		{
			if (i > 1 + optn)
				write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		}
	}
	if (!optn)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	ft_exit(t_cmd *cmd)
{
	int	res;

	res = cmd->exit;
	if (cmd && cmd->name && cmd->args[1])
	{
		res = ft_atoi(cmd->args[1]);
		if (errno == ERANGE)
		{
			if (cmd->pipe == 3)
				write(1, "exit\n", 5);
			write(STDOUT_FILENO,
				"minishell: exit: numeric argument required\n", 43);
			res = 2;
		}
		if (cmd->args[2])
		{
			write(STDOUT_FILENO, "exit\nminishell: exit: trop d'arguments\n", 39);
			return (1);
		}
	}
	if (cmd->pipe == 3 && errno != ERANGE)
		write(1, "exit\n", 5);
	free_split(cmd->env);
	free_all_cmd(cmd);
	exit(res);
}

int	built_in_exe(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->name, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd->name, "cd"))
		return (ft_cd(cmd));
	if (!ft_strcmp(cmd->name, "echo"))
		return (ft_echo(cmd));
	if (!ft_strcmp(cmd->name, "unset"))
		return (ft_unset(cmd));
	if (!ft_strcmp(cmd->name, "exit"))
		return (ft_exit(cmd));
	if (!ft_strcmp(cmd->name, "env"))
		return (ft_env(cmd));
	if (!ft_strcmp(cmd->name, "export"))
		return (ft_export(cmd));
	return (-1);
}
