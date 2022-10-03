/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:08:40 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/29 22:47:35 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	is_in(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (i);
	return (-1);
}

void	free_split(char ***split)
{
	int	i;

	i = -1;
	while ((*split)[++i])
		free((*split)[i]);
	free(*split);
}

int	free_all_cmd(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->i_red)
	{
		if (cmd->i_red->type == 2)
			unlink(cmd->i_red->file);
		free(cmd->i_red->file);
		free(cmd->i_red);
	}
	if (cmd->o_red)
	{
		free(cmd->o_red->file);
		free(cmd->o_red);
	}
	if (cmd->args)
		free_split(&(cmd->args));
	if (cmd->prev)
	{
		cmd = cmd->prev;
		free(cmd->next);
		cmd->next = NULL;
		return (free_all_cmd(cmd));
	}
	free(cmd);
	return (1);
}

int	join_write(int fd, char *str1, char *str2)
{
	char	*temp;
	char	*joined;

	temp = ft_strjoin(str2, "\n");
	joined = ft_strjoin(str1, temp);
	free(temp);
	write(fd, joined, ft_strlen(joined));
	free(joined);
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 && s2)
		return (s2[0]);
	if (!s2 && s1)
		return (s1[0]);
	if (!s2 && !s1)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
