/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:50:08 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/19 11:30:32 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include "../minishell.h"

int		is_in(char c, char *charset);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_unset(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
int		ft_export(t_cmd *cmd);
int		built_in_exe(t_cmd *cmd);
char	*get_real_cmd(t_cmd *cmd);
int		ft_alpha_print(char **tab);
void	free_split(char ***split);
void	join_write(int fd, char *str1, char *str2);
void	free_all_cmd(t_cmd *cmd);

#endif
