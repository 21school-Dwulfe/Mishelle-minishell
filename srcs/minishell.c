#include "../includes/main.h"
//rl_clear_history, rl_on_new_line,
//rl_replace_line, rl_redisplay, add_history,


void msh_sigintHandler(int sig_num)
{
	(void)sig_num;
	printf("\n");
	rl_on_new_line();
	rl_redisplay();	
}

void	msh_parse_cmd(char *line)
{
	if (ft_strnstr(line, "exit", 4))
	{
		exit(0);
	}
}

void	msh_sigtermHandler(int signum)
{
	printf("%d\n", signum);
}

int	msh_is_odd_quatation_on_line(char *str)
{
	int		i;
	int		quat[2];
	int		place[2];
	
	i = 0;
	place[0] = ft_strlen(str);
	place[1] = ft_strlen(str);
	ft_bzero(quat, sizeof(int) * 2);
	printf("%ld\n", ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == 34)
		{
			quat[0]++;
			if (quat[0] % 2)
			{
				printf("quat 0 = %d place 0 %d\n", quat[0], place[0]);
				place[0] = (i + 1);
			}
		}
		else if (str[i] == 39)
		{
			quat[1]++;
			if (quat[1] % 2)
			{
				place[1] = (i + 1);
				printf("quat 1 = %d place 1 %d\n", quat[1], place[1]);
			}
		}
		i++;
	}
	if (((quat[0] % 2) > 0) == ((quat[1] % 2) > 0))
	{
		if (place[1] < place[0])
			return (39);
		return (34);
	}
	else if ((quat[0] % 2) > (quat[1] % 2) && place[0] < place[1])
		return (34);
	else if ((quat[0] % 2) < (quat[1] % 2) && place[1] < place[0])
		return (39);
	else
	{
		printf("zero");
		return (0);
	}
}


int	msh_check_unclosed_quotes(char **buff, char *line, char c)
{	
	c = msh_is_odd_quatation_on_line(line);
	if (c)
	{
		ft_strlcat(*buff, line, 2048);
		free(line);
		line = readline("> ");
		if ()
		{

		}
		printf("buff %s", buff);
	}
}

int	main(int argc, char **argv)
{
	char		c;
	char		*line;
	char		buff[2048];

	(void)argc;
	(void)argv;
	line = NULL;
	rl_catch_signals = 0;
	ft_bzero(buff, sizeof(char) * 2048);
	//printf("%s\n", rl_completer_quote_characters);
	signal(SIGINT, msh_sigintHandler);
	while (1)
	{
		line = readline("\002\e[0;31m\003MISHELLE >>> \001\e[0m\002");
		if (line)
		{
			ft_strlcat(buff, line, 2048);
			msh_check_unclosed_quotes(&buff, line, 0);
			add_history(buff);
			msh_parse_cmd(buff);
			ft_bzero(buff, sizeof(char) * 2048);
			
		}
		else
		{
			write(1, "\n", 1);
			exit(0);
		}
		free(line);
	}
	return (0);
}