/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:07:53 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/20 21:53:27 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_cmd(char **line)
{
	int	in_out_s[2];
	int counter;

	if (msh_parse(line) == -1)
		return ;
	if (msh_cut_redirects_cmd() == -1)
		return ;
	in_out_s[0] = dup(0);
	in_out_s[1] = dup(1);
	counter = msh_executor(g_info.cur_cmd, g_info.env, in_out_s);
	close(in_out_s[1]);
	dup2(in_out_s[0], 0);
	close(in_out_s[0]);
	while (counter-- > 0)
		msh_wait_pid(-1);
	signal(SIGINT, msh_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
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
	if (regime)
		msh_argv_regime(argv + 1);
	else
		msh_stdin_regime();
	return (0);
}