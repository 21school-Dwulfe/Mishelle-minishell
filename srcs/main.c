#include "../includes/main.h"

void msh_readline(char *prefix, char **dest)
{
	char *line;

	line = readline(prefix);
	if (line)
		*dest = line;
	else
	{
		msh_struct_clear();
		exit(0);
	}
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
	g_info.func[14] = msh_token_quotes;
	g_info.func[14] = msh_token_d_quotes;
	g_info.func[15] = msh_curl_braces;
	g_info.func[16] = msh_dollar_braces;
	g_info.func[17] = msh_token_dollar;
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
		{
			ft_arrstr_del(cmds->args, ft_str_count(cmds->args));
		}
		//ft_delptr((void **)cmds->args);
		tmp_arg = cmds->args_token;
		while (tmp_arg)
		{
			cmds->args_token = cmds->args_token->next;
			ft_delptr((void **)tmp_arg->value_arr);
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
}

int	msh_validate_line(char *line)
{
	int				i;
	unsigned int	ascii[256];

	i = 0;
	ft_bzero(ascii, sizeof(char) * 256);
	while (line[i])
	{
		if (ft_isspace(line[i]))
			ascii[(unsigned char)line[i]]++;
		i++;
	}
	if (ft_strlen(line) == ascii[32])
		return (1);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	*buff_st_dy;
	char	buff[1024];
	
	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, msh_sigint_handler);
	msh_config(argc, argv, env);
	ft_bzero(buff, sizeof(char) * 1024);
	while (1)
	{
		msh_readline("\001\e[32m\002MISHELLE >>> \001\e[37m\002", &line);
		if (msh_validate_line(line))
			continue ;
		g_info.exit_code = 0;
		buff_st_dy = msh_strncat(line, buff, buff_st_dy);
		msh_check_unclosed_quotes(buff, line, buff_st_dy, 0);
		add_history(buff_st_dy);
		msh_cmd(buff_st_dy);
		ft_strdel(&line);
		ft_bzero(buff, sizeof(char) * 1024);
		ft_bzero(buff_st_dy, (ft_strlen(buff_st_dy) * sizeof(char))); //604 365 194
		msh_struct_clear();
	}
	return (0);
}