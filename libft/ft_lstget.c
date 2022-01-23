/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:57:45 by bmarecha          #+#    #+#             */
/*   Updated: 2021/09/22 12:57:50 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstget(t_list *lst, int i)
{
	t_list	*p;

	p = lst;
	if (p == NULL)
		return (NULL);
	while (p->next && i--)
	{
		p = p->next;
	}
	if (i > 0)
		return (NULL);
	return (p->content);
}
