/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:33:10 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/30 12:13:15 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*get_last_cmd(t_cmd *act)
{
	while (act->next)
		act = act->next;
	return (act);
}

void	show_error_heredoc(int s_line, char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(s_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

t_redir	*show_error_redir(char *line, int *i, t_cmd *act, t_redir *redir)
{
	redir->file = get_word(line, i, act);
	if (access(redir->file, F_OK) == 0)
	{
		if ((redir->type == 1 && access(redir->file, R_OK) == -1)
			|| (redir->type > 1 && (access(redir->file, W_OK) == -1)))
		{
			redir->access = 0;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redir->file, 2);
			ft_putstr_fd(": Permission non accordée\n", 2);
		}
	}
	else if (redir->type == 1)
	{
		redir->access = 0;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": Aucun fichier ou dossier de ce type\n", 2);
	}
	if (redir->type == 4)
		close(open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 00666));
	else if (redir->type == 3)
		close(open(redir->file, O_WRONLY | O_CREAT, 00666));
	return (redir);
}

t_cmd	*create_cmd_malloc(char ***env, int exit)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	init_command(cmd, env, exit);
	return (cmd);
}
