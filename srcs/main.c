/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:07:53 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/08 19:50:56 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	msh_init_functions(void)
{
	g_info.func[13] = msh_token_quotes;
	g_info.func[14] = msh_token_d_quotes;
	g_info.func[15] = msh_curl_braces;
	g_info.func[16] = msh_dollar_braces;
	g_info.func[17] = msh_token_dollar;
	g_info.condition[0] = msh_validation_closest_chars;
	g_info.condition[1] = msh_conditions_d_quotes_close;
	g_info.condition[2] = msh_conditions_quotes_close;
	g_info.condition[3] = msh_conditions_quotes;
	g_info.condition[4] = msh_conditions_d_quotes;
	g_info.condition[5] = msh_conditions_pipe;
	g_info.condition[6] = msh_conditions_semicolon;
	g_info.condition[7] = msh_conditions_dollar;
	g_info.condition[8] = msh_conditions_end;
}

void	msh_config(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	rl_catch_signals = 0;
	g_info.num_of_commands = 0;
	g_info.num_token = 0;
	g_info.env = msh_copy_env(env);
	g_info.pwd = getcwd(NULL, 0);
	msh_init_global_cmd();
	msh_init_functions();
	g_info.f[0] = "export";
	g_info.f[1] = "exit";
	g_info.f[2] = "unset";
	g_info.f[3] = "cd";
	g_info.f[4] = "pwd";
	g_info.f[5] = "echo";
	g_info.f[6] = "env";
	g_info.f[7] = "minishell";
}

void	msh_struct_clear()
{
	t_command 	*cmds;
	t_redirect	*tmp_red;
	t_arg		*tmp_arg;

	cmds = g_info.cur_cmd;
	g_info.exit_code = 0;
	g_info.num_token = 0;
	g_info.num_of_commands = 0;
	while (cmds)
	{
		if (cmds->args)
			ft_arrstr_del(cmds->args, ft_str_count(cmds->args));
		tmp_arg = cmds->args_token;
		while (tmp_arg)
		{
			cmds->args_token = cmds->args_token->next;
			free(tmp_arg);
			tmp_arg = cmds->args_token;
		}
		tmp_red = cmds->redirects;
		while (tmp_red)
		{
			cmds->redirects = cmds->redirects->next;
			ft_strdel(&tmp_red->file);
			free(tmp_red);
			tmp_red = cmds->redirects;
		}
		cmds = cmds->next;
		free(g_info.cur_cmd);
		g_info.cur_cmd = NULL;
		g_info.cur_cmd = cmds;
	}
	msh_init_global_cmd();
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	*buff_st_dy;
	char	buff[1024];
	
	line = NULL;
	buff_st_dy = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, msh_sigint_handler);
	msh_config(argc, argv, env);
	ft_bzero(buff, sizeof(char) * 1024);
	while (1)
	{
		msh_readline("\001\e[32m\002MISHELLE >>> \001\e[37m\002", &line);
		g_info.exit_code = 0;
		buff_st_dy = msh_strncat(line, buff, buff_st_dy);
		add_history(buff_st_dy);
		if (msh_validate_line(buff_st_dy))
			continue ;
		if (msh_check_unclosed_quotes(buff, line, buff_st_dy, 0) != -1)
			msh_cmd(buff_st_dy);
		ft_strdel(&line);
		ft_bzero(buff, sizeof(char) * 1024);
		ft_bzero(buff_st_dy, (ft_strlen(buff_st_dy) * sizeof(char))); //604 365 194
		msh_struct_clear();
	}
	return (0);
}