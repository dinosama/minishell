/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:17:36 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/23 22:12:45 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// gérer les quotes, variables env, par exemple cd "par""sing"

char	*delete_quotes(char *word)
{
	int		i;
	int		j;
	int		in_quote;
	char	*new;

	i = 0;
	j = 0;
	in_quote = 0;
	new = ft_calloc(ft_strlen(word) + 1, sizeof(char));
	while (word[i])
	{
		in_quote = quote_check(word[i], in_quote);
		if ((word[i] != '\'' || in_quote == 2) && (word[i] != '\"' || in_quote == 1) && word[i])
		{
			new[j] = word[i];
			j++;
		}
		i++;
	}
	free(word);
	return (new);
}

char	*get_word(char *str, int *len, t_cmd *act)
{
	int		in_quote;
	int		start;
	char	*word;

	in_quote = 0;
	start = *len;
	while ((!whitespace(str[*len]) || in_quote) && (!is_pipe(str[*len]) || in_quote)
			&& (!is_redirect(str[*len]) || in_quote) && str[*len])
	{
		in_quote = quote_check(str[*len], in_quote);
		*len = *len + 1;
	}
	if (in_quote != 0)
		return (NULL);
	word = ft_substr(str, start, *len - start);
	if (act->arg == 1)
		word = get_env_variable(word, act);
	word = delete_quotes(word);
	return (word);
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
	if (line[*i] == ';')
	{
		*i = *i + 1;
		return ;
	}
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

int	take_command(char *line, int *i, t_cmd *act)
{
	int		arg;

	arg = 0;
	act->name = get_word(line, i, act);
	while (whitespace(line[*i]))
		*i = *i + 1;
	act->args = malloc(sizeof(char *) * calcul_arg(line, *i) + 2);
	act->args[0] = act->name;
	act->arg = 1;
	arg++;
	while (!is_pipe(line[*i]) && !is_redirect(line[*i]) && line[*i])
	{
		act->args[arg] = get_word(line, i, act);
		arg++;
		while (whitespace(line[*i]))
			*i = *i + 1;
	}
	act->args[arg] = NULL;
	if (is_redirect(line[*i]))
		get_redirect(line, i, act);
	while (whitespace(line[*i]))
		*i = *i + 1;
	if (is_pipe(line[*i]) || line[*i] == 0)
		get_pipe(line, i, act);
	return (1);
}

t_cmd	*get_line(char *line, char ***env, int exit)
{
	t_cmd	*act;
	t_cmd	*new;
	t_cmd	*tokens;
	int		i;

	i = 0;
	act = malloc(sizeof(t_cmd));
	tokens = act;
	init_command(act, env, exit);
	while (line[i])
	{
		while (whitespace(line[i]))
			i++;
		take_command(line, &i, act);
		if (line[i])
		{
			new = malloc(sizeof(t_cmd));
			init_command(new, env, exit);
			new->prev = act;
			act->next = new;
			act = new;
		}
	}
	return (tokens);
}

char	*get_prompt(char **env)
{
	char	*prompt;
	char	*temp;
	char	*pwd;

	prompt = NULL;
	prompt = ft_strdup("");
	temp = find_env("USER", env);
	prompt = ft_strjoin(prompt, temp);
	prompt = ft_strjoin(prompt, ":");
	pwd = getcwd(NULL, 0);
	prompt = ft_strjoin(prompt, pwd);
	prompt = ft_strjoin(prompt, "$ ");
	free(temp);
	free(pwd);
	return (prompt);
}

int	read_line(char ***env, struct sigaction *sa1, struct sigaction *sa2)
{
	char	*line;
	t_cmd	*tokens;
	char	*prompt;
	int		exit;

	line = NULL;
	tokens = NULL;
	(void)sa2;
	sigaction(SIGINT, sa1, NULL);
	sigaction(SIGQUIT, sa1, NULL);
	prompt = get_prompt(*env);
	line = readline(prompt);
	add_history(line);
	exit = 0;
	while (line != NULL)
	{
		tokens = get_line(line, env, exit);
		//show_tokens(tokens);
		sigaction(SIGINT, sa2, NULL);
		sigaction(SIGQUIT, sa2, NULL);
		exit = start_chain(tokens);
		sigaction(SIGINT, sa1, NULL);
		sigaction(SIGQUIT, sa1, NULL);
		free(line);
		free(prompt);
		if (exit == 3)
			break;
		prompt = get_prompt(*env);
		line = readline(prompt);
		add_history(line);
	}
	rl_clear_history();
	if (!exit)
		ft_putstr("exit\n");
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	**new_env;
	struct	sigaction	sa1;
	struct	sigaction	sa2;

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
	return (0);
}
