/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:53:10 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/30 13:13:28 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	search_sig(char *str, int sig)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == sig)
			return (1);
		i++;
	}
	return (0);
}

void	heredoc_fill_two(char *read, int s_line, char *delimiter)
{
	if (read == NULL)
		show_error_heredoc(s_line, delimiter);
	if (read)
		free(read);
}

int	heredoc_fill_file(char *read, char *delimiter, int fd, t_cmd *act)
{
	static int	s_line;

	signal(SIGINT, handle_sig_heredoc);
	s_line++;
	read = readline("> ");
	while (read)
	{
		if (ft_strncmp(read, delimiter,
				ft_strlen(read) + ft_strlen(delimiter) + 2) != 0)
		{
			s_line++;
			if (!act->heredoc)
				read = get_env_variable(read, act, 1);
			write(fd, read, ft_strlen(read));
			write(fd, "\n", 1);
		}
		else
			break ;
		free(read);
		read = readline("> ");
	}
	heredoc_fill_two(read, s_line, delimiter);
	close(fd);
	return (1);
}

void	get_heredoc_two(int fail, t_cmd *act, int fd)
{
	waitpid(-1, &fail, 0);
	if (WEXITSTATUS(fail) == 3)
	{
		act = get_first_cmd(act);
		act->fail = 1;
	}
	close(fd);
}

char	*get_heredoc(char *line, int *i, t_cmd *act, int fail)
{
	char	*delimiter;
	char	*read;
	char	*file;
	char	*temp;
	int		fd;

	read = NULL;
	signal(SIGINT, SIG_IGN);
	if (quote_in_word(line, *i) == 1)
		act->heredoc = 1;
	delimiter = get_word(line, i, act);
	temp = ft_strjoin(".heredoc_", delimiter);
	fd = open(temp, O_RDWR | O_CREAT | O_EXCL, 00666);
	while (fd == -1)
	{
		file = temp;
		temp = ft_strjoin(temp, "x");
		free(file);
		fd = open(temp, O_RDWR | O_CREAT | O_EXCL, 00666);
	}
	if (!fork() && heredoc_fill_file(read, delimiter, fd, act) == 1)
		exit(1);
	get_heredoc_two(fail, act, fd);
	free(delimiter);
	return (temp);
}
