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
	g_info.func[0] = msh_help_parse_semi;
	g_info.func[1] = msh_help_parse_pipe;
	g_info.func[2] = msh_help_parse_redirect;
	g_info.func[3] = msh_help_parse_r_redirect;
	g_info.env = msh_copy_env(env);
	g_info.num_of_commands = 0;
	// g_info.func[4] = ;
	// g_info.func[5] = msh_help_parse_quotes;
	
}

void	msh_struct_clear()
{
	// ft_arrstr_del((*cmd)->args, (*cmd)->number_args);
	ft_delptr(g_info.current_command->args);
	ft_strdel(g_info.current_command->input_file);
	ft_strdel(g_info.current_command->err_file);
	ft_strdel(g_info.current_command->out_file);
	free(g_info.current_command);
	g_info.current_command = NULL;
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
		ft_strdel(line);
		ft_bzero(buff, sizeof(char) * 1024); //604 365 194
		msh_struct_clear();
	}
	return (0);
}