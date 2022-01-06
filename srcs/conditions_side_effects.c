/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_side_effects.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:04:59 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/04 20:05:01 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_specials_cut(char **str, int *i, int end)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = ft_strlen(*str);
	ft_memset((*str) + *i, '\0', sizeof(char) * end);
	tmp = *str;
	*str = msh_concat_str(*str, len, NULL);
	ft_strdel(&tmp);
	(*i)--;
}

void    msh_specials_replace(char **str, char *insertion, int *start, int end)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = ft_strlen(*str);
	ft_memset((*str) + *start, '\0', sizeof(char) * end);
	tmp = *str;
	*str = msh_concat_str(*str, len, insertion);
	ft_strdel(&tmp);
	(*start)--;
}


char	*msh_specify_token(int *length, char *str, int specials)
{
	char		*name;
	t_arg		*arg;
	t_command	*cmd;

	cmd = msh_last_cmd();
	name = g_info.func[specials](str, length);
	arg = msh_add_token(cmd, name, g_info.num_token++, specials);
	if (ft_strchr(name, '$'))
		if (specials != QUOTES)
			msh_evaluate_env_if_exist(arg->value, g_info.env);
	
}
