// #include "../includes/main.h"

// // parse string until occurs special or stop signs( ; | & > >> < << <& <<& \n)
// // validation operators order
// // validation cmd names
// // validation cmd args

// t_command	*msh_create_command(char	**dstr)
// {
// 	int			i;
// 	t_command	*cmd;	

// 	i = 0;
// 	cmd = malloc(sizeof(t_command));
	
// 	while (dstr[i])
// 	{
		
// 	}
// }

// t_s_command	*msh_create_command(char	**dstr)
// {
// 	int			i;
// 	t_s_command	*cmd;	

// 	i = 0;
// 	cmd = malloc(sizeof(t_s_command));
// 	while (dstr[i])
// 	{
		
// 	}
// }

// int	msh_check_special_signs(char c)
// {
// 	if (c == ';')
// 		return (0);
// 	if (c == '|')
// 		return (1);
// 	if (c == '&')
// 		return (2);
// 	if (c == '>')
// 		return (3);
// 	if (c == '<')
// 		return (4);
// 	if (c == '\n')
// 		return (5);
// 	return (0);
// }


// void	msh_cmd_to_struct(char **result)
// {
// 	void	*tmp;

// 	if (g_info.regime == 1)
// 	{
// 		if (!g_info.currentCommand)
// 			g_info.currentCommand = msh_create_command(result);
// 		else
// 		{
// 			tmp = msh_create_command(result);
// 			((t_command *)tmp)->next = g_info.currentCommand;
// 			g_info.currentCommand = g_info.currentCommand->next;
// 		}
// 	}
// 	else
// 	{
// 		if (!g_info.currentCommand)
// 			g_info.currentCommand = msh_create_s_comand(result);
// 		else
// 		{
// 			tmp = msh_create_s_comand(result);
// 			((t_command *)tmp)->next = g_info.currentCommand;
// 			g_info.currentCommand = g_info.currentCommand->next;
// 		}
// 	}
// }

// char **msh_split(char *str)
// {
// 	int		length;
// 	int		i;
// 	int		mem;
// 	char	**result;
// 	void	*tmp;

// 	i = 0;
// 	length = 0;
// 	mem = 0;
// 	while (str[length])
// 	{

// 		while (str[length] && !msh_check_special_signs(str[length]))
// 		{
// 			length++;
// 		}
		
// 		tmp = ft_substr(tmp, 0, length);
// 		result = ft_split(tmp, ' ');
// 		ft_delptr(tmp);
// 		msh_cmd_to_struct(result);
// 	}
	
// }

// int	msh_check_regime(char *str)
// {
// 	char *s;

// 	s = str;
// 	while (s)
// 	{
// 		if (*s == '>' || *s == '<' || *s == '|')
// 			return (2);
// 		s++;
// 	}
// 	return (1);
// }

// int	msh_is_quatation(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 27 || str[i] == 22)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void *msh_parse(char *str)
// {
// 	int			i;
// 	int			quatation;
// 	//char		*cmds;
// 	void		*cmd;
// 	i = 0;
// 	(void)cmd;
// 	quatation = msh_is_quatation(str);
// 	g_info.regime = msh_check_regime(str);
// 	if (quatation)
// 	{
// 	 	//cmds = msh_split_quatation(str);
// 	}
// 	else
// 	{
// 		//cmds = msh_split(str, " ");
// 	}
// 	return (cmd);
// }