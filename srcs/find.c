#include "../includes/main.h"


char	*msh_read_fd(int fd)
{
	int		ret;
	char	*tmp;
	char	buff[1024];
	char	*result;

	result = NULL;
	ft_bzero(buff, 1024);
	if (fd < 0)
		return (NULL);
	while ((ret = read(fd, buff, 1024)) > 0)
	{
		if (!result)
			result = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(result, buff);
			ft_strdel(result);
			result = tmp;
		}
	}
	return (result);
}

char *msh_get_path(char *cmd_name, char **env)
{
	int		pid;
	int		fd[2];
	char	*path;
	char	*cmd[3];

	cmd[0] = "/usr/bin/which";
	cmd[1] = cmd_name;
	cmd[2] = NULL;
	path = NULL;
	if (pipe(fd) < 0)
		perror("Error");
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execve("/usr/bin/which", cmd, env) == -1)
		{
			perror("Pathfinder:");
			exit(EXIT_FAILURE);
		}
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	waitpid(0, NULL, 0);
	path = msh_read_fd(0);
	return (path);
}

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	char *re = msh_get_path("ls", env);
// 	if (re == NULL)
// 		printf("NULL\n");
// 	printf("%s", re);
// 	ft_strdel(re);
// 	return (0);
// }
