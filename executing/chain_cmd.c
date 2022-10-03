/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 19:48:16 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/30 11:31:17 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	dupin(int i_fd, t_cmd *cmd)
{
	int	fd;

	if (cmd->i_red && cmd->i_red->type <= 2)
	{
		if (access(cmd->i_red->file, R_OK))
		{
			return (0);
		}
		fd = open(cmd->i_red->file, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->i_red->file);
			return (0);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (cmd->pipe == 2 || cmd->pipe == 0)
		dup2(i_fd, STDIN_FILENO);
	return (1);
}

int	dupout(int o_fd, t_cmd *cmd)
{
	int	fd;

	if (cmd->o_red && cmd->o_red->type >= 3)
	{
		if (access(cmd->o_red->file, W_OK) && errno != ENOENT)
		{
			return (0);
		}
		if (cmd->o_red->type == 3)
			fd = open(cmd->o_red->file, O_WRONLY | O_APPEND | O_CREAT, 00666);
		else
			fd = open(cmd->o_red->file, O_WRONLY | O_CREAT | O_TRUNC, 00666);
		if (fd == -1)
		{
			perror(cmd->o_red->file);
			return (0);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (cmd->pipe == 2 || cmd->pipe == 1)
		dup2(o_fd, STDOUT_FILENO);
	return (1);
}

int	execute_cmd(int i_fd, t_cmd *cmd, int o_fd)
{
	if (!dupin(i_fd, cmd))
		return (1);
	if (i_fd != -1)
		close(i_fd);
	if (!dupout(o_fd, cmd))
		return (1);
	if (o_fd != -1)
		if (close(o_fd))
			return (-1);
	if (!cmd->name)
		return (0);
	if (!ft_strcmp(cmd->name, "pwd") || !ft_strcmp(cmd->name, "cd")
		|| !ft_strcmp(cmd->name, "echo") || !ft_strcmp(cmd->name, "export")
		|| !ft_strcmp(cmd->name, "env") || !ft_strcmp(cmd->name, "unset")
		|| !ft_strcmp(cmd->name, "exit"))
		return (built_in_exe(cmd));
	cmd->name = get_real_cmd(cmd);
	if (cmd->name == NULL)
		return (127);
	cmd->args[0] = cmd->name;
	execve(cmd->name, cmd->args, *(cmd->env));
	return (1);
}

int	forking_cmd(int i_fd, t_cmd *cmd, int o_fd, int oi_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		if (oi_fd != -1)
			close(oi_fd);
		cmd->exit = execute_cmd(i_fd, cmd, o_fd);
		exit(cmd->exit);
		return (0);
	}
	if (i_fd != -1)
		close(i_fd);
	return (pid);
}

int	start_chain(t_cmd *cmd)
{
	int		pipefd[2];
	int		infd;
	int		status;

	infd = -1;
	while (cmd->next)
	{
		if (pipe(pipefd) == -1)
			perror("Can't create pipe");
		forking_cmd(infd, cmd, pipefd[1], pipefd[0]);
		close(pipefd[1]);
		infd = pipefd[0];
		cmd = cmd->next;
	}
	if (cmd->pipe == 3 && (!ft_strcmp(cmd->name, "cd")
			|| !ft_strcmp(cmd->name, "export") || !ft_strcmp(cmd->name, "exit")
			|| !ft_strcmp(cmd->name, "unset")))
		return (built_in_exe(cmd));
	else
		forking_cmd(infd, cmd, -1, -1);
	while (waitpid(-1, &status, WUNTRACED) > 0)
		;
	return (WEXITSTATUS(status));
}
