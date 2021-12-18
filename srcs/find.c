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
			ft_strdel(&result);
			result = tmp;
		}
	}
	return (result);
}

char	*msh_get_path(char *cmd_name, char **env)
{
	int		i;
	char	*tmp[4];
	char	*path;
	char	**splited;

	i = 0;
	path = msh_get_if_exist(env, "PATH");
	splited = ft_split(path, ':');
	while (splited[i])
	{
		tmp[0] = ft_strjoin(splited[i], "/");
		tmp[1] = ft_strjoin(tmp[0], cmd_name);
		ft_strdel(&tmp[0]);
		if (access(tmp[1], F_OK) == 0)
		{
			ft_arrstr_del(splited, ft_str_count(splited));
			return (tmp[1]);
		}
		else
			ft_strdel(&tmp[1]);
		i++;
	}
	perror(cmd_name);
	return (NULL);
}

// char *msh_get_path(char *cmd_name, char **env)
// {
// 	int		pid;
// 	int		fd[2];
// 	char	*path;
// 	char	*cmd[3];
// 	char	fds[2];

// 	fds[0] = dup(STDIN_FILENO);
// 	fds[1] = dup(STDOUT_FILENO);
// 	cmd[0] = "/usr/bin/which";
// 	cmd[1] = cmd_name;
// 	cmd[2] = NULL;
// 	path = NULL;
// 	if (pipe(fd) < 0)
// 		perror("Error");
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
		
// 		close(fd[0]);
// 		close(fd[1]);
// 		if (execve("/usr/bin/which", cmd, env) == -1)
// 		{
// 			perror("Pathfinder:");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[1]);
// 	close(fd[0]);
	
// 	waitpid(0, NULL, 0);
// 	path = msh_read_fd(0);
// 	if (path)
// 		path[ft_strlen(path) - 1] = '\0';
// 	dup2( fds[1], STDOUT_FILENO);
// 	dup2(fds[0], STDIN_FILENO);
	
	
// 	close(fds[0]);
// 	close(fds[1]);
// 	return (path);
// }



// char *msh_multy_pipe(t_command *cmds, char **env)
// {
// 	int		pid;
// 	int		fd[2];
// 	char	*result;
// 	int		file;

// 	result = NULL;
// 	if (pipe(fd) < 0)
// 		perror("Error");
// 	if (cmds->input_file)
// 	{
// 		file = open(cmds->input_file, O_RDONLY, 0777);
// 		dup2(fd[0], STDIN_FILENO);
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		if (execve(cmds->args[0], cmds->args, env) == -1)
// 		{
// 			perror("Execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	waitpid(0, NULL, 0);
// 	if (cmds->out_file)
// 	{
// 		file = open(cmds->out_file, O_CREAT | O_WRONLY, 0777);
// 		dup2(fd[0], file);
// 	}
// 	else
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		result = msh_read_fd(0);
// 	}
// 	close(fd[1]);
// 	close(fd[0]);
// 	return (result);
// }

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	char *re = msh_get_path(NULL, env);
// 	if (re == NULL)
// 		printf("NULL\n");
// 	printf("%s", re);
// 	ft_strdel(&re);
// 	return (0);
// }

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_command	*cmd;

// 	cmd = malloc(sizeof(t_command));
// 	cmd->args = argv + 1;
// 	char *re = msh_multy_pipe(cmd, env);
// 	if (re == NULL)
// 		printf("NULL\n");
// 	printf("%s", re);
// 	ft_strdel(re);
// 	return (0);
// }
