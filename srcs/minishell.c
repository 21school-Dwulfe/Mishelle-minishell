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
	if (line && ft_strnstr(line, "exit", 4))
		exit(0);
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

int	msh_is_odd_quatation_on_line(char *str, int regime)
{
	int		i;
	int		quat[2];
	int		place[2];
	
	i = 0;
	place[0] = ft_strlen(str) + 1;
	place[1] = ft_strlen(str) + 1;
	ft_bzero(quat, sizeof(int) * 2);
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == 34)//"
		{
			quat[0]++;
			if (quat[0] % 2)
			{
				//printf("quat 0 = %d place 0 %d\n", quat[0], place[0]);
				place[0] = (i + 1);
			}
		}
		else if (str[i] == 39)//'
		{
			quat[1]++;
			if (quat[1] % 2)
			{
				place[1] = (i + 1);
				//printf("quat 1 = %d place 1 %d\n", quat[1], place[1]);
			}
		}
		i++;
	}
	printf("///////quat 0 = %d place 0 %d\n", (quat[0] % 2), place[0]);
	printf("////quat 1 = %d place 1 %d\n", (quat[1] % 2), place[1]);
	if (!regime)
		if ((quat[0] % 2) == (quat[1] % 2) && (quat[0] % 2) > 0 && (quat[1] % 2) > 0)
		{
			//printf("quat 1 = %d place 1 %d\n", quat[1], place[1]);
			if (place[1] < place[0])
			{
				printf("39");
				return (g_info.odd_quote = 39);
			}
			return (g_info.odd_quote = 34);
		}
		else if ((quat[0] % 2) > (quat[1] % 2) )//&& place[0] < place[1])
			return (g_info.odd_quote = 34);
		else if ((quat[0] % 2) < (quat[1] % 2) )//&& place[1] < place[0])
			return (g_info.odd_quote = 39);
		else
		{
			printf("zero");
			return (g_info.odd_quote = 0);
		}
	}
	else
	{
		if (!ft_strchr(line, regime))
			return (regime);
		else
			return (0);
	}
}


void	msh_check_unclosed_quotes(char *buff, char *line, char c)
{	
	if (c == 0)
		c = msh_is_odd_quatation_on_line(line, 0);
	else
		c = msh_is_odd_quatation_on_line(line, c);
	if (c)
	{
		line = msh_readline("quote> ");
		ft_strlcat(buff, line, 1024);
		printf("c = %c  g_c= %c", c, g_info.odd_quotations);
		msh_check_unclosed_quotes(buff, line, c);
		free(line);
		printf("buff %s", buff);
	}
}

void	msh_config_terminal(struct termios *saved, struct termios *tty)
{
	if (!isatty(0))
	{
		fprintf(stderr, "stdin not termminal\n");
		exit(EXIT_FAILURE);
	}
	tcgetattr(0, tty);
	saved = tty;
	tty->c_lflag &= ~(ICANON | ECHO | ISIG);
	tty->c_cc[VMIN] = 1;

}

// int	main(int argc, char **argv)
// {
// 	struct termios saved_tty;
// 	struct termios tty;
// 	char		*line;
// 	char		buff[2048];

// 	(void)argc;
// 	(void)argv;
// 	line = NULL;
// 	rl_catch_signals = 0;
// 	ft_bzero(buff, sizeof(char) * 2048);
// 	//signal(SIGINT, msh_sigintHandler);
// 	msh_config_terminal();
// 	while (1)
// 	{
// 		line = readline("\002\e[0;31m\003MISHELLE >>> \001\e[0m\002");
// 		if (line)
// 		{
// 			ft_strlcat(buff, line, 2048);
// 			msh_check_unclosed_quotes(buff, line, 0);
// 			add_history(buff);
// 			msh_parse_cmd(buff);
// 			ft_bzero(buff, sizeof(char) * 2048);
// 		}
// 		else
// 			exit(0);
// 		free(line);
// 	}
// 	return (0);
// }



void	msh_config(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
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
	while (1)
	{
		printf(GREEN);
		line = msh_readline("MISHELLE >>> \001\e[0m\002");
		ft_strlcat(buff, line, 1024);
		msh_check_unclosed_quotes(buff, line, 0);
		add_history(buff);
		msh_parse_cmd(buff);
		ft_bzero(buff, sizeof(char) * 1024);
	}
	return (0);
}