/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 12:56:32 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/21 15:04:55 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	ft_cd(t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0] || !cmd->args[1])
	{
		write(STDERR_FILENO, "Missing an argument.\n", 21);
		return (-1);
	}
	if (!chdir(cmd->args[1]))
		return (0);
	if (errno == EACCES || errno == EFAULT)
		write(STDERR_FILENO, "Access denied.\n", 15);
	if (errno == ELOOP || errno == ENAMETOOLONG)
		write(STDERR_FILENO, "Path too long or too much symbolic links.\n", 42);
	if (errno == ENOENT || errno == ENOTDIR)
		write(STDERR_FILENO,
			"The directory specified in path does not exist.\n", 48);
	if (errno == ENOMEM)
		write(STDERR_FILENO, "Insufficient kernel memory was available.\n", 42);
	return (-1);
}

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
		return (-1);
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
	free_all_cmd(cmd);
	return (3);
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
