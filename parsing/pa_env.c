/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 05:20:31 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/23 05:12:16 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*find_env(char *nail, char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		while (env[i][j] == nail[j])
			j++;
		if (env[i][j] == '=' && nail[j] == 0)
			return (ft_substr(env[i], j + 1, ft_strlen(env[i]) - j));
		i++;
		j = 0;
	}
	return (NULL);
}

char	*replace_in_word(char *word, int *i, int *start, int in_quote)
{
	int		j;
	char	*var;

	j = 0;
	*start = *i;
	*i = *i + 1;
	var = calloc(ft_strlen(word) + 1, sizeof(char));
	while (!ft_whitespace(word[*i]) && word[*i] && word[*i] != '$' && word[*i] != '\"' && (!is_pipe(word[*i]) || in_quote) && (!is_redirect(word[*i]) || in_quote))
	{
		var[j] = word[*i];
		j++;
		*i = *i + 1;
	}
	return (var);
}

char	*replace_with_env(char *word, int *i, t_cmd *act, int in_quote)
{
	char	*new;
	char	*var;
	char	*temp;
	int		start;

	new = ft_substr(word, 0, *i);
	var = replace_in_word(word, i, &start, in_quote);
	if (var[0] == '?' && var[1] == 0)
		temp = ft_itoa(act->exit);
	else
		temp = find_env(var, *act->env);
	if (temp != NULL)
	{
		start = start + ft_strlen(temp);
		new = ft_strjoin(new, temp);
		free(temp);
	}
	temp = ft_substr(word, *i, 500);
	new = ft_strjoin(new, temp);
	free(temp);
	free(word);
	free(var);
	*i = start - 1;
	return (new);
}

char	*get_env_variable(char *word, t_cmd *act)
{
	int		i;
	int		in_quote;

	i = 0;
	in_quote = 0;
	while (word[i])
	{
		in_quote = quote_check(word[i], in_quote);
		if (word[i] == '$' && (in_quote == 0 || in_quote == 2))
			word = replace_with_env(word, &i, act, in_quote);
		i++;
	}
	return (word);
}
