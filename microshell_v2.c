#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
// #include <stdio.h>
// #include <fcntl.h>


int ft_strlen(const char *str) {
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void error_cd_bad_args(void) {
	write(2, "error: cd: bad arguments\n", ft_strlen("error: cd: bad arguments\n"));
}

void error_cd_cannot_change(char *str) {
	write(2, "error: cd: cannot change directory to ", ft_strlen("error: cd: cannot change directory to "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void error_cannot_exec(char *str) {
	write(2, "error: cannot execute ", ft_strlen("error: cannot execute "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void exit_fatal(void) {
	write(2, "error: fatal\n", ft_strlen("error: fatal\n"));
	exit(1);
}

void ft_cd(char **line) {
	int i = 0;
	while (line[i])
		i++;
	if (i != 2) {
		error_cd_bad_args();
		return ;
	}
	if (chdir(line[1]))
		error_cd_cannot_change(line[1]);
}

int main(int ac, char **av, char **env) {
	int i = 1;
	int len, j;
	int fd[2], fds[2];
	int f_cd = 0;
	int f_pipe = 0;
	int opened = 0;
	int status = 0;
	pid_t pid;
	char **line = NULL;
	
	

	while (ac > 1 && i < ac) {
		if ((!strcmp(av[i], ";") || !strcmp(av[i], "|")) && i++) // пропускаем все ";" и "|" ищем команду
			continue ;
		len = 0;
		while (av[i + len] && strcmp(av[i + len], ";") && strcmp(av[i + len], "|")) // определяем кол-во аргументов у команды
			len++;
		if (!(line = (char **)malloc(sizeof(char *) * (len + 1)))) // выделяем память для записи команды и аргументов
			exit_fatal();
		line[len] = NULL;
		j = 0;
		while (j < len) {
			line[j] = av[i]; 									// заполняем созанныем массив комндой и аргументами
			if (!strcmp(av[i], "cd"))
				f_cd = 1;
			j++;
			i++;
		}
		if (av[i] && !strcmp(av[i], "|"))						// проверяем есть ли  "|" после команды
			f_pipe = 1;
		else
			f_pipe = 0;
		if ((av[i] && !strcmp(av[i], "cd")) || f_cd)			// проверяем комнду на  "cd"  если да то выполняем ft_cd
			ft_cd(line);
		if (opened) {											////////////////// выполняется после пайпа  "|"
			fds[0] = dup(0);									////////////////// сохраняем дискриптор на чтение 0 в fds[0]
			dup2(fd[0], 0);										////////////////// закрываем не нужный fds[0] 
			close(fd[0]);
		}
		if (f_pipe) {											// если после команды идет pipe "|"  то:  ////////////// делаем каждый последущий раз если будет после команды "|"
			if (pipe(fd))										// создаем pipe и назначаем ему fd
				exit_fatal();
			fds[1] = dup(1);									// сохраняем файловый дискриптор Вывода 1 в fds[1]
			dup2(fd[1], 1);										// перенапраляем Вывод 1 в pipe fd[1]
			close(fd[1]);										// закрываем ненужный fd[1]
		}
		pid = fork();											// делаем fork
		if (pid < 0)
			exit_fatal();
		else if (!pid){											// рабоаем в дочернем процессе если в команде не было "cd"
			if (!f_cd)
			{
				if (execve(line[0], line, env))					//  вапускаем биарник записанный в команде
					error_cannot_exec(line[0]);
			}
			exit(0);											// выход из дочернего процесса
		}
		else
			waitpid(pid, &status, 0);							// ждем завершения дочернего процесса
		if (opened) {											// если был запуск команды после "|" то были изменены файловые дискрипторы на чтение
			dup2(fds[0], 0);									// нужно переопределить файловые дискрипторы обратно fds[0] на 0
			close(fds[0]);
			opened = 0;
		}
		if (f_pipe) {											// если был pipe и подменены файловые дискрипторы то нужно их вернуть на место
			dup2(fds[1], 1);									// обратне перенапавоение Выхода из fds[1] на 1
			close(fds[1]);
			opened = 1;											// флаг выполненной записи в канал 1;
		}
		f_cd = 0;													
		free(line);												// очистка массива команд
	}
	return (0);
}
