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

void	msh_parse_cmd(char *line)
{   
	int		i;
	t_command	*cmd;

	i = 0;
	msh_parse(line);
	cmd = g_info.current_command;
	while (i++ < g_info.num_of_commands)
	{
		if (ft_strnstr(cmd->arguments[0], "exit", 4))
			msh_custom_exit(cmd);
		else if (ft_strnstr(cmd->arguments[0], "pwd", 3))
			msh_custom_pwd(cmd);
		else if (ft_strnstr(cmd->arguments[0], "echo", 4))
			msh_custom_echo(cmd);
		else if (ft_strnstr(cmd->arguments[0], "env", 3))
			msh_custom_env(cmd);
		else if (ft_strnstr(cmd->arguments[0], "cd", 2))
			msh_custom_cd(cmd);
		else if (ft_strnstr(cmd->arguments[0], "export", 6))
			msh_custom_export(cmd);
		else if (ft_strnstr(cmd->arguments[0], "unset", 5))
			msh_custom_unset(cmd);
		else
			msh_execute(cmd);
		cmd = cmd->next;
	}
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

// void	msh_config_terminal(struct termios *saved, struct termios *tty)
// {
// 	if (!isatty(0))
// 	{
// 		fprintf(stderr, "stdin not termminal\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	tcgetattr(0, tty);
// 	saved = tty;
// 	tty->c_lflag &= ~(ICANON | ECHO | ISIG);
// 	tty->c_cc[VMIN] = 1;

// }

void	msh_config(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	g_info.func[0] = msh_help_parse_semi;
	g_info.func[1] = msh_help_parse_pipe;
	g_info.func[2] = msh_help_parse_redirect;
	g_info.func[3] = msh_help_parse_r_redirect;
	g_info.env = env;
	// g_info.func[4] = ;
	// g_info.func[5] = msh_help_parse_quotes;
	
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	buff[1024];

	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, msh_sigintHandler);
	msh_config(argc, argv, env);
	line = NULL;
	ft_bzero(buff, sizeof(char) * 1024);
	while (1)
	{
		line = msh_readline("\001\e[32m\002MISHELLE >>> \001\e[37m\002");
		ft_strlcat(buff, line, 1024);
		msh_check_unclosed_quotes(buff, line, 0);
		add_history(buff);
		msh_parse_cmd(buff);
		free(line);
		ft_bzero(buff, sizeof(char) * 1024);
	}
	return (0);
}