#include "../includes/main.h"

int	msh_perror(char *cmd_name)
{
	char	*str;

	str = strerror(errno);
	msh_save_error_code(errno);
	ft_putstr_fd("Mishelle", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putendl_fd(str, 2);
	return (1);
}

void	msh_redirect_error(char *message, char *token_str, int token_len)
{
	int i;

	i = 0;
	while (message[i])
		i++;
	write(2, message, i);
	write(2, " `", 2);
	write(2, token_str, token_len);
	write(2, "'\n", 3);
	msh_struct_clear();
}

void	msh_export_error(char *arg)
{
	char	*str[2];
	char 	*tmp[2];
	
	str[0] = "mishelle: export: `";
	str[1] = "\': not a valid identifier\n";
	tmp[0] = ft_strjoin(str[0], arg);
	tmp[1] = ft_strjoin(tmp[0], str[1]);
	ft_strdel(&tmp[0]);
	write(2, tmp[1], ft_strlen(tmp[1]));
	ft_strdel(&tmp[1]);
}

int	msh_export_invalid(char *arg)
{
	int 	i[4];
	int 	res;
	int		length;

	res = 0;
	i[0] = -1;
	length = ft_strlen(arg);
	if (!arg || (length == 1 && !ft_isalpha(arg[0])) || ft_ch_count(arg, '+') > 1 )
		return ((++res));
	i[1] = ft_index_of(arg, '+');
	if (i[1] > 0)
		i[2] = i[1];
	else if (i[1] == -1)
		i[2] = ft_index_of(arg, '=');
	else
		return ((++res));
	if (length > 2 && arg[i[1]] == '+' && arg[i[1] + 1] != '=')
		return ((++res));
	else if (!res && ((arg[length - 1] != '=' && !ft_isalpha(arg[length - 1]) && !ft_isdigit(arg[length - 1]))
		|| (arg[length - 1] != '=' && !ft_isalpha(arg[length - 1]))))
		return ((++res));
	while (length > 1 && !res && ++i[0] < i[2])
		if (!ft_isalpha(arg[i[0]]) && !ft_isdigit(arg[i[0]])  && ++res)
			return ((++res));
	return (0);
}