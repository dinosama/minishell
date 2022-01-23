/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <bmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:31:34 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/19 13:54:14 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

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
			if (ft_strcmp(pmax, tab[i]) < 0)
				if (!cmin || ft_strcmp(tab[i], cmin) < 0)
					cmin = tab[i];
		}
		if (!cmin)
			break ;
		printf("declare -x %s\n", cmin);
		pmax = cmin;
	}
	return (0);
}
