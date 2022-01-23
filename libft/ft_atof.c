/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:04:44 by bmarecha          #+#    #+#             */
/*   Updated: 2020/07/11 17:36:49 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float	numbers_process(char *str, int *coma)
{
	int		i;
	float	res;

	i = 6;
	res = 0;
	while (i && *str)
	{
		if (*str == '.')
		{
			if (*coma > 0)
				break ;
			else
				*coma = *coma + 1;
		}
		else if (*str < 48 || *str > 57)
			break ;
		else if (!(*str == 48 && res == 0 && *coma == 0) && i-- > -2)
		{
			res = res * 10 + *str - 48;
			if (*coma > 0)
				*coma += 1;
		}
		str++;
	}
	return (res);
}

float	ft_atof(char *str)
{
	float	res;
	int		coma;
	float	sign;

	coma = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	res = numbers_process(str, &coma);
	while (--coma > 0)
		res = res / 10;
	return (res * sign);
}
