/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:17:36 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/30 12:18:02 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_word(char *str, int *len, t_cmd *act)
{
	int		in_quote;
	int		start;
	char	*word;

	in_quote = 0;
	start = *len;
	word = NULL;
	while ((!whitespace(str[*len]) || in_quote)
		&& (!is_pipe(str[*len]) || in_quote)
		&& (!is_redirect(str[*len]) || in_quote) && str[*len])
	{
		in_quote = quote_check(str[*len], in_quote);
		*len = *len + 1;
	}
	if (in_quote != 0)
		return (NULL);
	if (*len != start)
		word = ft_substr(str, start, *len - start);
	word = get_env_variable(word, act, 0);
	word = delete_quotes(word);
	return (word);
}

void	take_command(char *line, int *i, t_cmd *act)
{
	if (!start_command(line, i, act))
		return ;
	while (!is_pipe(line[*i]) && line[*i])
	{
		if (is_redirect(line[*i]))
		{
			if (!get_redirect(line, i, act))
				return ;
		}
		while (whitespace(line[*i]))
			*i = *i + 1;
		if (is_pipe(line[*i]) || !line[*i])
			break ;
		act->args[act->arg] = get_word(line, i, act);
		if (act->args[act->arg] != NULL)
			act->arg = act->arg + 1;
		while (whitespace(line[*i]))
			*i = *i + 1;
	}
	while (whitespace(line[*i]))
		*i = *i + 1;
	if (is_pipe(line[*i]) || line[*i] == 0)
		get_pipe(line, i, act);
}

t_cmd	*get_line(char *line, char ***env, int exit)
{
	t_cmd	*act;
	t_cmd	*new;
	int		i;

	i = 0;
	act = create_cmd_malloc(env, exit);
	if (!check_error(line, act))
		return (NULL);
	while (line[i])
	{
		while (whitespace(line[i]))
			i++;
		take_command(line, &i, act);
		if (act->fail == 1)
			return (act);
		if (line[i])
		{
			new = create_cmd_malloc(env, exit);
			new->prev = act;
			act->next = new;
			act = new;
		}
	}
	return (get_first_cmd(act));
}

int	read_line(char ***env, struct sigaction *sa1, struct sigaction *sa2)
{
	char	*line;
	t_cmd	*tokens;

	line = NULL;
	manage_sig(1, sa1, sa2);
	line = reading(line, env);
	while (line != NULL)
	{
		manage_sig(3, sa1, sa2);
		tokens = get_line(line, env, g_return);
		free(line);
		manage_sig(0, sa1, sa2);
		if (tokens && !tokens->fail)
			g_return = start_chain(tokens);
		if (tokens && tokens->fail)
			tokens = get_last_cmd(tokens);
		manage_sig(1, sa1, sa2);
		if (tokens)
			free_all_cmd(tokens);
		line = reading(line, env);
	}
	rl_clear_history();
	ft_putstr("exit\n");
	return (0);
}

int	g_return = 0;

int	main(int ac, char **av, char **env)
{
	char				**new_env;
	struct sigaction	sa1;
	struct sigaction	sa2;

	sa1.sa_flags = SA_RESTART;
	sa1.sa_handler = &handle_sig;
	sigemptyset(&sa1.sa_mask);
	sa2.sa_flags = SA_RESTART;
	sa2.sa_handler = SIG_IGN;
	sigemptyset(&sa2.sa_mask);
	(void)ac;
	(void)av;
	new_env = copy_env(env);
	read_line(&new_env, &sa1, &sa2);
	free_split(&new_env);
	return (g_return);
}
