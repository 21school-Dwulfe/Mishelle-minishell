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

static void	msh_init_functions(void)
{
	g_info.condition[0] = msh_validation_closest_chars;
	g_info.condition[1] = msh_conditions_d_quotes_close;
	g_info.condition[2] = msh_conditions_quotes_close;
	g_info.condition[3] = msh_conditions_quotes;
	g_info.condition[4] = msh_conditions_d_quotes;
	g_info.condition[5] = msh_conditions_pipe;
	g_info.condition[6] = msh_conditions_semicolon;
	g_info.condition[7] = msh_conditions_dollar;
	g_info.condition[8] = msh_conditions_end;
	g_info.condition[9] = msh_conditions_slash;
	g_info.condition[10] = msh_conditions_d_pipe;
	g_info.condition[11] = msh_conditions_d_amp;
	g_info.condition[12] = msh_conditions_curl_braces;
	g_info.func[13] = msh_token_quotes;
	g_info.func[14] = msh_token_d_quotes;
	g_info.func[15] = msh_curl_braces;
	g_info.func[17] = msh_token_dollar;
	g_info.func[18] = msh_slash;
}

static void	msh_config(int argc, char **argv, char **env, int *regime)
{
	if (argc > 2)
		*regime = (ft_strncmp(argv[1], "-cmd", 5) == 0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, msh_sigint_handler);
	rl_catch_signals = 0;
	g_info.num_of_commands = 0;
	g_info.num_token = 0;
	g_info.env = msh_copy_env(env);
	g_info.pwd = getcwd(NULL, 0);
	msh_init_global_cmd();
	msh_init_functions();
	msh_build_preparings();
	g_info.f[0] = "export";
	g_info.f[1] = "exit";
	g_info.f[2] = "unset";
	g_info.f[3] = "cd";
	g_info.f[4] = "pwd";
	g_info.f[5] = "echo";
	g_info.f[6] = "env";
	g_info.f[7] = "minishell";
}

static void	msh_clear_tokens(t_command *cmd)
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

void	msh_struct_clear()
{
	t_command 	*cmd;
	t_redirect	*tmp_red;

	cmd = g_info.cur_cmd;
	g_info.num_token = 0;
	g_info.num_of_commands = 0;
	while (cmd)
	{
		if (cmd->args)
			ft_arrstr_del(cmd->args, ft_str_count(cmd->args));
		msh_clear_tokens(cmd);
		tmp_red = cmd->redirects;
		while (tmp_red)
		{
			cmd->redirects = cmd->redirects->next;
			ft_strdel(&tmp_red->file);
			free(tmp_red);
			tmp_red = cmd->redirects;
		}
		cmd = cmd->next;
		free(g_info.cur_cmd);
		g_info.cur_cmd = NULL;
		g_info.cur_cmd = cmd;
	}
}

void	msh_stdin_regime(void)
{
	char	*line;
	
	line = NULL;
	while (1)
	{
		msh_readline("\001\e[32m\002MISHELLE >>> \001\e[37m\002", &line);
		add_history(line);
		if (msh_validate_line(line))
			continue ;
		if (!msh_unclosed_quotes(&line, NULL, 0))
			msh_cmd(&line);
		ft_strdel(&line);
		msh_struct_clear();
		msh_init_global_cmd();
	}
}

void	msh_argv_regime(char **argv)
{
	int 	i;
	int 	len;
	char	*line;

	i = 0;
	len = 0;
	while (argv[i])
		len += ft_strlen(argv[i++]);
	line = ft_calloc(len, sizeof(char));
	i = 0;
	while (argv[i])
		line = ft_strncpy(line, argv[i++], len);
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
		msh_argv_regime(argv + 2);
	else
		msh_stdin_regime();
	return (0);
}