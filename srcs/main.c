/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:07:53 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/15 21:43:40 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_clear_tokens(t_command *cmd)
{
	t_arg		*tmp_arg;

	tmp_arg = cmd->args_token;
	while (tmp_arg)
	{
		cmd->args_token = cmd->args_token->next;
		ft_strdel(&tmp_arg->name);
		ft_strdel(&tmp_arg->pseudo);
		ft_strdel(&tmp_arg->value);
		free(tmp_arg);
		tmp_arg = cmd->args_token;
	}
}

void	msh_argv_regime(char **argv)
{
	int 	i;
	int 	len;
	char	*line;
	int 	offset;

	i = 0;
	len = 0;
	while (argv[i])
		len += ft_strlen(argv[i++]);
	line = ft_calloc(len, sizeof(char) + i);
	i = 0;
	offset = 0;
	while (argv[i])
	{
		ft_strncpy(line + offset, argv[i], len);
		line[ft_strlen(line)] = ' ';
		offset += ft_strlen(line);
		i++;
	}
	if (msh_validate_line(line))
			return ;
	if (!msh_unclosed_quotes(&line, NULL, 0))
		msh_cmd(&line);
	ft_strdel(&line);
	msh_struct_clear();
}

int main(int argc, char **argv, char **env)
{
	int	regime;

	msh_config(argc, argv, env, &regime);
	if (argc == 2 && !ft_strncmp(argv[1], "-cmd", 5))
	{
		write(1, "\nusage : -cmd [command ...args] \n\t or ", 39);
		write(1, "    [cmd >file or fd, < file or fd, >> file or fd, << file or fd] \n\t or ", 73);
		write(1, "    [command && command, command || command, command | command ]\n\n", 67);
		return (0);
	}
	if (regime)
		msh_argv_regime(argv + 2);
	else
		msh_stdin_regime();
	return (0);
}