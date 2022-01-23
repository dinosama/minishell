/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarecha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:40:52 by bmarecha          #+#    #+#             */
/*   Updated: 2019/11/23 18:07:41 by bmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*p2;
	t_list	*res;

	if (lst == NULL || f == NULL)
		return (NULL);
	p = lst;
	res = ft_lstnew(f(lst->content));
	if (res == NULL)
		return (NULL);
	p2 = res;
	while (p->next)
	{
		p = p->next;
		p2->next = ft_lstnew(f(p->content));
		if (p2->next == NULL)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		p2 = p2->next;
	}
	return (res);
}
