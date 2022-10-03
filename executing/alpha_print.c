/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:31:34 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/29 23:01:05 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	**add_spe_char(char **env, char *base)
{
	char	ctrl[2];
	char	**res;
	char	*baseslash;

	ctrl[0] = (char)18;
	ctrl[1] = '\0';
	baseslash = ft_strjoin(ctrl, base);
	res = add_env(env, baseslash);
	free(baseslash);
	return (res);
}

int	ft_alpha_print(char **tab)
{
	char	*cmin;
	char	*pmax;
	int		i;

	pmax = "";
	while (1)
	{
		i = 0;
		cmin = NULL;
		while (tab[++i])
		{
			if (ft_envcmp(pmax, tab[i]) < 0)
				if (!cmin || ft_envcmp(tab[i], cmin) < 0)
					cmin = tab[i];
		}
		if (!cmin)
			break ;
		join_write(STDOUT_FILENO, "declare -x ", cmin);
		pmax = cmin;
	}
	return (0);
}

int	ft_export(t_cmd *cmd)
{
	int		n[2];
	int		i;
	char	*var;

	*n = 0;
	n[1] = 0;
	while (cmd->args[++(*n)])
	{
		i = -1;
		var = cmd->args[*n];
		while (var[++i])
			if (var[i] == '=' || (!ft_isalnum((int)var[i]) && var[i] != '_'))
				break ;
		if (i == 0 || (var[i]
				&& !ft_isalnum((int)var[i]) && var[i] != 95 && var[i] != 61))
			n[1] = join_write(STDERR_FILENO,
					"export: identifiant non valable :", var);
		else if (var[i])
			*(cmd->env) = add_env(*(cmd->env), var);
		else
			*(cmd->env) = add_spe_char(*(cmd->env), var);
	}
	if (*n == 1)
		ft_alpha_print(*(cmd->env));
	return (n[1]);
}
