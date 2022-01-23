/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 03:18:22 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/23 02:40:07 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_sig(int sig)
{
	if (sig == SIGQUIT)
		return ;
	ft_putstr_fd("\n", 0);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
