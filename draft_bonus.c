

//regime 0 
// stop signs any
// stop varios special

//regime 1 output
//asdf< asdfg
//asdf <asdrfg
//sdfsd $? asd
//asdf$?asdfg

// char **msh_get_sides_ch(char *str, char *set, int side, int *reg)
// {
// 	unsigned int	first;
// 	int				i[6];
// 	char 			*stop[2];

// 	first = 0;
// 	ft_bzero(i, sizeof(int) * 6);
// 	if (side == -1)
// 		i[3]++;
// 	if (side == 1)
// 		i[5]++;
// 	if (reg[0] == 0)
// 		stop[0] = set[0];
// 	else if (reg[0] == 1)
// 	{
// 		stop[0] = set[1];
// 		stop[1] = set[2];
// 	}

// 	while (reg[1] == 0 && str[i[0]])
// 	{
// 		while (!first && set[i[1]])
// 		{
// 			if (ft_strncmp(str[i[0]], set[i[1]], ft_strlen(set[0])) == 0)
// 				first = i[1];
// 			i[1]++;
// 		}
// 		if (ft_strncmp(str[i[0]], set[first], ft_strlen(set[first])) == 0)
// 			break ;
// 		i[0]++;
// 	}
// 	while (reg[1] == 1 && !i[2])
// 	{
// 		if (!i[3] && i[0] + --i[4] != 0
// 			&& !((unsigned char)str[i[0] + i[4]] - (unsigned char )stop[0][0]))
// 			i[3]++;
// 		if (!i[5] && str[i[0] + ++i[6]]
// 			&& !((unsigned char)str[i[0] + i[6]] - (unsigned char)stop[1][0]))
// 			i[5]++;
// 		if (i[3] && i[5])
// 			i[2]++;
// 	}

// 	char **result;
// 	if (reg[2] == 0) // as is
// 	{
// 		result = malloc(sizeof(char *) * 2);
// 		result[0] = ft_strndup_se(str[first], i[0], 0);
// 		result[1] = NULL;
// 	}
// 	else if (reg[2] == 1) //pref & root+posrfix
// 	{
// 		result = malloc(sizeof(char *) * 3);
// 		result[0] = ft_strndup_se(str + first, 0, set[0]);
// 	}
// 	else if (reg[2] == 2) // pref+root & postfix
// 	{

// 	}
// }


// char	**msh_concat_args(char **args, int size)
// {
// 	int		i[4];
// 	char	**tmp;

// 	tmp = NULL;
// 	ft_bzero(i, sizeof(int) * 4);
// 	i[0] = -1;
// 	while (args[++i[0]] && ft_strcmp(args[i[0]],""))
// 		i[3]++;
// 	i[2] = size;
// 	while (--i[2] > i[0] && args[i[2]] && ft_strcmp(args[i[2]],""))
// 		i[3]++;
// 	if (i[3])
// 	{
// 		tmp = ft_calloc(sizeof(char *), (i[3] + 1));
// 		while (i[1] < i[0])
// 		{
// 			tmp[i[1]] = args[i[1]];
// 			i[1]++;
// 		}
// 		while (++i[2] < size)
// 		{
// 			tmp[i[1]] = args[i[2]];
// 			i[1]++;
// 		}
// 		tmp[i[3]] = NULL;
// 	}
// 	return (tmp);
// }