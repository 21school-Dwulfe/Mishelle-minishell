/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:05:57 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/28 17:26:58 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	msh_perror(char *cmd_name)
{
	char	*str;

	str = strerror(errno);
	msh_save_error_code(errno);
	ft_putstr_fd("msh: ", 2);
	ft_putstr_fd(cmd_name, 2);
	write(2, ": ", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

int	msh_error_bash(char *message, char *str, int code)
{
	msh_save_error_code(code);
	ft_putstr_fd("msh: ", 2);
	ft_putstr_fd(str, 2);
	write(2, ": ", 2);
	ft_putendl_fd(message, 2);
	return (code);
}

int	msh_unexpected_token_error(char *token_str, int token_len)
{
	g_info.exit_code = 258;
	write(2, "Mishelle: syntax error near unexpected token", 44);
	write(2, " `", 2);
	write(2, token_str, token_len);
	write(2, "'\n", 2);
	return (ERROR);
}

int	msh_export_error(char *arg)
{
	char	*str[2];
	char	*tmp[2];

	str[0] = "mishelle: export: `";
	str[1] = "\': not a valid identifier\n";
	tmp[0] = ft_strjoin(str[0], arg);
	tmp[1] = ft_strjoin(tmp[0], str[1]);
	ft_strdel(&tmp[0]);
	write(2, tmp[1], ft_strlen(tmp[1]));
	ft_strdel(&tmp[1]);
	return (1);
}
