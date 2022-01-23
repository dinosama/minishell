/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:43:45 by bmarecha          #+#    #+#             */
/*   Updated: 2022/01/23 02:28:02 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"

//type of redir : 1 == '<', 2 == '<<', 3 == '>>', 4 == '>'

typedef struct s_redir
{
	char	*file;
	int		type;
}				t_redir;

/*
** pipe : 0 == entree, 1 == sortie, 2 == sortie et entree, 3 == aucun des deux
** next et/ou prev sont mis a NULL dans les cas correspondants
*/

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;

	char			*name;
	char			**args;
	char			***env;
	int				pipe;
	int				exit;
	int				arg;

	t_redir			*i_red;
	t_redir			*o_red;
}					t_cmd;

int	start_chain(t_cmd *cmd);

#endif
