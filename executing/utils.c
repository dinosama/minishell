/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:08:40 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/19 14:16:02 by bmarecha         ###   ########.fr       */
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

void	free_all_cmd(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->i_red)
	{
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
		free_all_cmd(cmd);
	}
	else
		free(cmd);
}

void	join_write(int fd, char *str1, char *str2)
{
	write(fd, str1, ft_strlen(str1));
	write(fd, str2, ft_strlen(str2));
	write(fd, "\n", 1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
