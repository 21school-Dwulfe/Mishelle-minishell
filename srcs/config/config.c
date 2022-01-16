/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 20:08:57 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/07 20:09:49 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_shlvl(char **env)
{
	int		index;
	char	*shlvl;
	char	*new_shlvl[2];
	
	index = msh_env_exist(env, "SHLVL");
	shlvl = msh_get_env_by_key(env, "SHLVL");
	new_shlvl[0] = ft_itoa(ft_atoi(shlvl) + 1);
	new_shlvl[1] = ft_strjoin("SHLVL=", new_shlvl[0]);
	msh_modify_env_var(&env[index], new_shlvl[1]);
	ft_strdel(&new_shlvl[0]);
	ft_strdel(&new_shlvl[1]);
}

void	msh_shell_bin(char **env, char *path)
{
	int		index;
	int		new_len;
	char	*new_shell;

	index = msh_env_exist(env, "SHELL");
	new_len = ft_strlen(path) + 16;
	new_shell = ft_calloc(new_len, sizeof(char));
	new_shell = ft_strncat(new_shell, "SHELL=", new_len);
	new_shell = ft_strncat(new_shell, path, new_len);
	new_shell[6 + ft_strlen(path)] = '/';
	new_shell = ft_strncat(new_shell, "minishell", new_len);
	if(index != -1)
		msh_modify_env_var(&env[index], new_shell);
	else
		msh_create_env_var(new_shell);
	ft_strdel(&new_shell);
}

void	msh_init_functions(void)
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

void	msh_config(int argc, char **argv, char **env, int *regime)
{
	*regime = (argc > 1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, msh_sigint_handler);
	rl_catch_signals = 0;
	g_info.num_of_commands = 0;
	g_info.num_token = 0;
	g_info.env = msh_copy_env(env);
	g_info.pwd = getcwd(NULL, 0);
	msh_init_global_cmd();
	msh_init_functions();
	msh_shlvl(g_info.env);
	msh_shell_bin(g_info.env, g_info.pwd);
	g_info.f[0] = "export";
	g_info.f[1] = "exit";
	g_info.f[2] = "unset";
	g_info.f[3] = "cd";
	g_info.f[4] = "pwd";
	g_info.f[5] = "echo";
	g_info.f[6] = "env";
	g_info.f[7] = "minishell";
}
