/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vne_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 01:25:45 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/29 22:36:30 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	ft_envcmp(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!s1 && s2)
		return (s2[0]);
	if (!s2 && s1)
		return (s1[0]);
	if (!s2 && !s1)
		return (0);
	j = 0;
	if (s1[0] == (char)18)
		i++;
	if (s2[0] == (char)18)
		j++;
	while (s1[i] && s2[j] && s1[i] == s2[j])
	{
		if (s1[i++] == '=')
			return (0);
		j++;
	}
	if ((!s2[j] && s1[i] == '=') || (s2[j] == '=' && !s1[i]))
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

char	**add_env(char **env, char *var)
{
	int		i;
	int		n;
	char	**vne;

	i = -1;
	while (env[++i])
		if (!ft_envcmp(var, env[i]))
			break ;
	if (env[i])
	{
		free(env[i]);
		env[i] = ft_strdup(var);
		return (env);
	}
	n = i;
	while (env[n])
		n++;
	vne = malloc(sizeof(char *) * (++n + 1));
	vne[n] = NULL;
	vne[--n] = ft_strdup(var);
	while (--n >= 0)
		vne[n] = env[n];
	free(env);
	return (vne);
}

char	**remove_env(char **env, char *var)
{
	int		i;
	int		n;
	char	**vne;

	i = -1;
	while (env[++i])
		if (!ft_envcmp(var, env[i]))
			break ;
	if (!env[i])
		return (env);
	n = i;
	while (env[n])
		n++;
	vne = malloc(sizeof(char *) * n);
	vne[--n] = NULL;
	while (--n >= 0)
	{
		vne[n] = env[n + 1];
		if (n < i)
			vne[n] = env[n];
	}
	free(env[i]);
	free(env);
	return (vne);
}

int	ft_unset(t_cmd *cmd)
{
	int		n;
	int		i;
	char	*var;
	int		exit;

	n = 0;
	exit = 0;
	while (cmd->args[++n])
	{
		i = -1;
		var = cmd->args[n];
		while (var[++i])
			if (!ft_isalnum((int)var[i]) && var[i] != '_')
				break ;
		if (var[i] || i == 0)
		{
			join_write(STDERR_FILENO, "unset: identifiant non valable :", var);
			exit = 1;
		}
		else
			*(cmd->env) = remove_env(*(cmd->env), var);
	}
	return (exit);
}

int	ft_env(t_cmd *cmd)
{
	int		i;
	char	**vne;

	i = -1;
	vne = *(cmd->env);
	while (vne[++i])
	{
		if (vne[i][0] != (char)18)
		{
			write(STDOUT_FILENO, vne[i], ft_strlen(vne[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return (0);
}
