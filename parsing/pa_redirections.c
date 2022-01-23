/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 00:53:16 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/23 05:13:11 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

void	clean_redir(t_cmd *act)
{
	if (act->i_red)
	{
		free(act->i_red->file);
		free(act->i_red);
		act->i_red = NULL;
	}
	if (act->o_red)
	{
		free(act->o_red->file);
		free(act->o_red);
		act->o_red = NULL;
	}
}

int	wich_redirect(char *line, int *i)
{
	if (line[*i] == '<' && line[*i + 1] != '<')
	{
		*i = *i + 1;
		return (1);
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		*i = *i + 2;
		return (2);
	}
	if (line[*i] == '>' && line[*i + 1] != '>')
	{
		*i = *i + 1;
		return (3);
	}
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		*i = *i + 2;
		return (4);
	}
	return (0);
}

t_redir	*create_redirect(char *line, int *i, int type, t_cmd *act)
{
	t_redir		*redir;

	redir = malloc(sizeof(t_redir) * 1);
	/*if (type == 1 || type == 4)
		*i = *i + 1;
	if (type == 2 || type == 3)
		*i = *i + 1;*/
	while (whitespace(line[*i]))
		*i = *i + 1;
	redir->file = get_word(line, i, act);
	redir->type = type;
	return (redir);
}

void	get_redirect(char *line, int *i, t_cmd *act)
{
	int		redirect;

	redirect = wich_redirect(line, i);
	if (redirect == 1)
		act->i_red = create_redirect(line, i, 1, act);
	else if (redirect == 2)
		act->i_red = create_redirect(line, i, 2, act);
	else if (redirect == 3)
		act->o_red = create_redirect(line, i, 4, act);
	else if (redirect == 4)
		act->o_red = create_redirect(line, i, 3, act);
	while (whitespace(line[*i]))
		*i = *i + 1;
	if (is_redirect(line[*i]))
	{
		clean_redir(act);
		get_redirect(line, i, act);
	}
}
