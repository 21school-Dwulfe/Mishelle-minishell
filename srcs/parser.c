// #include "../includes/main.h"

// char **msh_split_quatation(char *str)
// {
// 	int		length;
// 	char	**result;

// 	length = 0;

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

// t_token *msh_parse(char *str)
// {
// 	int		len;
// 	int		quatation;
// 	int		i;
// 	char	*cmds;
// 	t_token *token;

// 	i = 0;
// 	quatation = msh_is_quatation(str);
// 	if (quatation)
// 	 	cmds = msh_split_quatation(str);
// 	else
// 		cmds = ft_split(str, " ");
// 	return (token);
// }