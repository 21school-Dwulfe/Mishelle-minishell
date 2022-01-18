/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:11:43 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/18 22:57:10 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_is_token(char *arg)
{
	if (DEV_TOKENS)
		return (msh_tok_pseudo_reader_dev(arg));
	else
		return (msh_tok_pseudo_reader(arg));
}

t_arg	*msh_last_token(void)
{
	return (msh_last_cmd()->args_token->prev);
}
