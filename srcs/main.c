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
	g_info.env = msh_copy_env(env);
	g_info.f[0] = "export";
	g_info.f[1] = "exit";
	g_info.f[2] = "unset";
	g_info.f[3] = "cd";
	g_info.f[4] = "pwd";
	g_info.f[5] = "echo";
	g_info.f[6] = "env";
}

void	msh_struct_clear()
{
	t_command 	*cmds;
	t_redirect	*tmp_red;

	cmds = g_info.cur_cmd;
	g_info.num_of_commands = 0;
	while (cmds)
	{
		// if (cmds->args)
		// 	ft_arrstr_del(cmds->args, ft_str_count(cmds->args));
		ft_delptr((void **)cmds->args);
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

void	msh_child(int child)
{
	printf("handler %d\n", child);
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	buff[1024];
	pid_t	pid = getpid();

	printf("%d\n", pid);
	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, msh_sigintHandler);
	signal(SIGCHLD, msh_child);
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