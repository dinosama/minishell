/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 04:54:34 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/30 12:32:11 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_prompt(char **env)
{
	char	*prompt;
	char	*temp;
	char	*pwd;
	char	*ok;

	prompt = NULL;
	prompt = ft_strdup("");
	temp = find_env("USER", env);
	if (!temp)
	{
		free(prompt);
		return (ft_strdup("$> "));
	}
	ok = ft_strjoin(prompt, temp);
	free(prompt);
	prompt = ft_strjoin(ok, ":");
	free(ok);
	pwd = getcwd(NULL, 0);
	ok = ft_strjoin(prompt, pwd);
	free(prompt);
	prompt = ft_strjoin(ok, "$ ");
	free(ok);
	free(temp);
	free(pwd);
	return (prompt);
}

char	*reading(char *line, char ***env)
{
	char	*prompt;

	prompt = get_prompt(*env);
	line = readline(prompt);
	add_history(line);
	free(prompt);
	return (line);
}

int	start_command(char *line, int *i, t_cmd *act)
{
	while (is_redirect(line[*i]))
	{
		if (!get_redirect(line, i, act))
			return (0);
		while (whitespace(line[*i]))
			*i = *i + 1;
	}
	act->name = get_word(line, i, act);
	if (act->name == NULL)
	{
		if (is_pipe(line[*i]) || line[*i] == 0)
			get_pipe(line, i, act);
		return (0);
	}
	while (whitespace(line[*i]))
		*i = *i + 1;
	act->args = calloc(calcul_arg(line, *i) + 3, sizeof(char *));
	act->args[0] = act->name;
	act->arg = 1;
	return (1);
}

void	get_pipe(char *line, int *i, t_cmd *act)
{
	if (act->prev != NULL)
	{
		if (act->prev->pipe == 1 || act->prev->pipe == 2)
			act->pipe = 0;
	}
	if (!line[*i])
		return ;
	if (line[*i] == '|')
	{
		*i = *i + 1;
		if (act->pipe == 0)
			act->pipe = 2;
		else
			act->pipe = 1;
		return ;
	}
}

t_cmd	*get_first_cmd(t_cmd *cmd)
{
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}
