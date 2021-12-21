#include "../includes/main.h"
//rl_clear_history, rl_on_new_line,
//rl_replace_line, rl_redisplay, add_history,

void msh_sigintHandler(int sig_num)
{
	(void)sig_num;
	printf("%d\n", sig_num);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	msh_sigtermHandler(int signum)
{
	printf("%d\n", signum);
}

void msh_readline(char *prefix, char **dest)
{
	char *line;

	pid_t	pid = getpid();

//	si.__sigaction_handler = msh_sigintHandler;
	printf("%d\n", pid);
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
		int len = ft_str_count(cmds->args);
		 	ft_arrstr_del(cmds->args, len);
	//	ft_delptr((void **)cmds->args);
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

char	*msh_strlcat(char *new, char *buff, char *dyn_buff)
{
	int	line_l;
	int	buff_l;
	int new_size;

	if (!dyn_buff)
		buff_l = ft_strlen(buff);
	else
		buff_l = ft_strlen(dyn_buff);
	line_l = ft_strlen(new);
	if (buff_l + line_l > 1024)
	{
		new_size = ft_abs((1024 - buff_l + line_l));
		dyn_buff = ft_realloc(buff, sizeof(char) * (new_size + 1));
		ft_strlcat(dyn_buff, new, new_size + 1);
		return (dyn_buff);
	}
	else
	{
		ft_strlcat(buff, new, 1024);
		return (buff);
	}
}

void	msh_child(int child)
{
	printf("handler %d\n", child);
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	*buff_st_dy;
	char	buff[1024];
//	struct sigaction si;
	pid_t	pid = getpid();

//	si.__sigaction_handler = msh_sigintHandler;
	printf("%d\n", pid);
	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, msh_sigintHandler);
	signal(SIGCHLD, msh_child);
	msh_config(argc, argv, env);
	ft_bzero(buff, sizeof(char) * 1024);
	while (1)
	{
		msh_readline("\001\e[32m\002MISHELLE >>> \001\e[37m\002", &line);
		if (msh_validate_line(line))
			continue ;
		buff_st_dy = msh_strlcat(line, buff, buff_st_dy);
		msh_check_unclosed_quotes(buff, line, buff_st_dy, 0);
		add_history(buff_st_dy);
		msh_cmd(buff_st_dy);
		ft_strdel(&line);
		ft_bzero(buff_st_dy, sizeof(char) * 1024); //604 365 194
		msh_struct_clear();
	}
	return (0);
}