#include "../includes/main.h"
//rl_clear_history, rl_on_new_line,
//rl_replace_line, rl_redisplay, add_history,

void msh_sigintHandler(int sig_num)
{
	(void)sig_num;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	msh_sigtermHandler(int signum)
{
	printf("%d\n", signum);
}

char	*msh_readline(char *prefix)
{
	char *line;

	line = readline(prefix);
	if (line)
		return (line);
	else
		exit(0);
}

void	msh_config(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	rl_catch_signals = 0;
	g_info.func[0] = msh_redirect_parse;
	g_info.func[1] = msh_redirect_parse;
	g_info.func[2] = msh_help_parse_pipe;
	g_info.func[3] = msh_help_parse_ampersand;
	g_info.env = msh_copy_env(env);
	g_info.num_of_commands = 0;
}

void	msh_struct_clear()
{
	// ft_arrstr_del((*cmd)->args, (*cmd)->number_args);
	t_command *cmds;

	cmds = g_info.cur_cmd;
	while (cmds)
	{
		ft_delptr((void **)cmds->args);

		// ft_arrstr_del(cmds->input, ft_str_counter());
		// ft_strdel(cmds->err);
		// ft_strdel(cmds->out);
		cmds = cmds->next;
		free(g_info.cur_cmd);
		g_info.cur_cmd = NULL;
		g_info.cur_cmd = cmds;
	}
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	buff[1024];

	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, msh_sigintHandler);
	msh_config(argc, argv, env);
	ft_bzero(buff, sizeof(char) * 1024);
	while (1)
	{
		line = msh_readline("\001\e[32m\002MISHELLE >>> \001\e[37m\002");
		ft_strlcat(buff, line, 1024);
		msh_check_unclosed_quotes(buff, line, 0);
		add_history(buff);
		msh_cmd(buff);
		ft_strdel(&line);
		ft_bzero(buff, sizeof(char) * 1024); //604 365 194
		msh_struct_clear();
	}
	return (0);
}