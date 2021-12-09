#include "../includes/main.h"

int		msh_check_syntax(char *str, int in, char *c, int len_cmp)
{
	int index;

	index = 0;
	if (!ft_strchr(str, c[0]))
		return (0);
	while (str[index] == c[0])
		index++;
	// if (index == len_cmp && in + 1 < g_info.cur_cmd->num_args 
	// 	&& ((ft_strcmp("<", g_info.cur_cmd->args[in + 1] ) && ft_strcmp(">", g_info.cur_cmd->args[in + 1])) ||
	// 	(ft_strcmp("<<", g_info.cur_cmd->args[in + 1]) && ft_strcmp(">>", g_info.cur_cmd->args[in + 1]))))
	// {
	// 	g_info.cur_cmd->specials = ERROR;
	// 	msh_error(str, "Mishelle: syntax error near unexpected token",
	// 		g_info.cur_cmd->args[in + 1] , ft_strlen(g_info.cur_cmd->args[in + 1]));
	// }
	// else
	if (in == g_info.cur_cmd->num_args - 1 && g_info.cur_cmd->piped)
		msh_error(str, "Mishelle: syntax error near unexpected token", "|" , 1);
	else if (index > 2)
	{
		g_info.cur_cmd->specials = ERROR;
		msh_error(str, "Mishelle: syntax error near unexpected token",
				str + 2 , index - 2);
	}
	else if (len_cmp > index && ft_abs(c[0] - str[index]) == 2)
	{
		g_info.cur_cmd->specials = ERROR;
		msh_error(str, "Mishelle: syntax error near unexpected token",
				str + index , len_cmp - index);
	}
	else if ((index < len_cmp && (str[index + 1] == ';'
		|| (in == g_info.cur_cmd->num_args - 1 && (str[index + 1] == '|' || g_info.cur_cmd->piped))))  )
		{
			g_info.cur_cmd->specials = ERROR;
			msh_error(str, "Mishelle: syntax error near unexpected token",
					str + index , ft_strlen(str) - index);
		}
	
	else if (in + 1 < g_info.cur_cmd->num_args)
	{
		if (in + 1 < g_info.cur_cmd->num_args && !ft_strcmp(g_info.cur_cmd->args[in], g_info.cur_cmd->args[in + 1])
			&& (int)ft_strlen(g_info.cur_cmd->args[in]) == index)
		msh_error(str, "Mishelle: syntax error near unexpected token",
			g_info.cur_cmd->args[in + 1], ft_strlen(g_info.cur_cmd->args[in + 1]));
	}
	else if (in == g_info.cur_cmd->num_args -1 && ((!ft_strcmp(g_info.cur_cmd->args[in], "<<") || !ft_strcmp(g_info.cur_cmd->args[in], ">>"))
		|| (!ft_strcmp(g_info.cur_cmd->args[in], "<") || !ft_strcmp(g_info.cur_cmd->args[in], ">"))))
		msh_error(str, "Mishelle: syntax error near unexpected token", "newline", 7);
	if (index == 2 && c[0] == '<')
		g_info.cur_cmd->specials = RD_REDIRECT;
	if (index == 1 && c[0] == '<')
		g_info.cur_cmd->specials = R_REDIRECT;
	if (index == 2 && c[0] == '>')
		g_info.cur_cmd->specials = D_REDIRECT;
	if (index == 1 && c[0] == '>')
		g_info.cur_cmd->specials = REDIRECT;
	if (!g_info.cur_cmd)
		return (-1);
	if (!ft_strcmp(str, c))
		return (0);
	if (index == 0 || (index < len_cmp && str[index + 1] != '\0')) 
		return (1);
		
	return (0);
}

int	msh_redirect_parse(char *str, int *length)
{
	t_command	*cmd;
	int			i;
	char		c[4];
	int			in[4];

	(void)str;
	(void)length;
	i = 0;
	ft_bzero(c, sizeof(char) * 4);
	cmd = g_info.cur_cmd;
	while (cmd->args[i])
	{
		in[0] = ft_index_of(cmd->args[i], '<');
		in[1] = ft_index_of(cmd->args[i], '>');
		if (ft_strnstr(cmd->args[i], ">>", 3)
			&& ((in[1] != -1 && in[0] == -1)
			|| (in[1] != -1 && in[0] != -1 && in[1] < in[0])))
		{
			c[0] = '>';
			c[1] = '>';
		}
		else if (ft_strnstr(cmd->args[i], "<<", 3)
			&& ((in[0] != -1 && in[1] == -1)
			|| (in[0] != -1 && in[1] != -1 && in[0] < in[1])))
		{
			c[0] = '<';
			c[1] = '<';
		}
		if ((in[0] != -1 && in[1] == -1)
			|| (in[0] != -1 && in[1] != -1 && in[0] < in[1]))
			c[0] = '<';
		else if ((in[1] != -1 && in[0] == -1)
			|| (in[1] != -1 && in[0] != -1 && in[1] < in[0]))
			c[0] = '>';
		if (c[0] && msh_help_parse_redirect(cmd->args[i], &i, c) == -1)
			return (-1);
		i++;
	}
	return(0);
}

int	msh_help_parse_pipe(char *str, int *index)
{
	(void)str;
	(*index)++;
	g_info.cur_cmd->piped = 1;
	return (msh_redirect_parse(str, index));
}

void	msh_concat_args(t_command *cmd)
{
	int		i;
	int		j;
	int		num;
	int		k;
	char	**tmp;

	i = -1;
	num = 0;
	k = 0;
	while (cmd->args[++i])
		num++;
	j = cmd->num_args;
	while (j >= 0 && cmd->args[--j])
		num++;
	if (num)
	{
		tmp = cmd->args;
		cmd->args = malloc(sizeof(char) * (num + 1));
		while (k < i)
		{
			cmd->args[k] =tmp[k];
			k++;
		}
		while (++j < cmd->num_args)
		{
			cmd->args[k] = tmp[k];
			k++;
		}
		// ft_strdel(tmp);
		cmd->num_args = num;
	}
}

int		msh_if_cmd_found(char *str, int *index, char *c)
{
	(void)str;
	int	len;

	len = ft_strlen(c);
	if (ft_strcmp(g_info.cur_cmd->args[0] , c) == 0
		&& g_info.cur_cmd->num_args == 3 
		&& *index + len < g_info.cur_cmd->num_args)
	{
		ft_swap_strs(g_info.cur_cmd->args[0], g_info.cur_cmd->args[*index + 2]);
		return (0);
	}
	else if (ft_strcmp(g_info.cur_cmd->args[0] , c))
		return (0);
	else
		return (1);
}
/**
 * @brief Cut's redirect signs, if they are clumped with filename or previos arg
 * j[0] = NULL	
 * j[1] = int of redirect < , > 
 * j[2] = index of another type of redirect if it exist in the string
 * j[3] = iterator for loop
 * @param i - current index of args
 * @param c - string with redirect
 */
void	msh_multiple_clump_redirects(int i, char *c)
{
	int			j[4];
	char		**tmp;
	t_redirect	**l;
	char		*t;
	char		*tp[4];
	

	tmp = NULL;
	ft_bzero(j, sizeof(int) * 4);
	ft_bzero(tp, sizeof(char *) * 4);
	j[1] = 122 - c[0];
	j[2] = ft_index_of(g_info.cur_cmd->args[i], j[1]);
	// if (!ft_strcmp(c, ">") || !ft_strcmp(c, ">>"))
	// 	l = &g_info.cur_cmd->out;
	// else
	// 	l = &g_info.cur_cmd->input;
	if (g_info.cur_cmd->args[i][0] != c[0])
	{
		tp[0] = ft_strndup_se(g_info.cur_cmd->args[i] , 0, j[1]);
		tp[1] = ft_strdup(g_info.cur_cmd->args[i] + ft_index_of(g_info.cur_cmd->args[i], c[0]));
		ft_strdel(&g_info.cur_cmd->args[i]);
	}
	else
		tp[1] = g_info.cur_cmd->args[i];
	if (j[2] < 0)
	{
		tmp = ft_split(tp[1], c[0]);
		while (tmp[j[3]])
			{
				t = tmp[j[3]++];
				msh_add_redirect(&g_info.cur_cmd->redirects, t);
			}
	}
	else
	{
		msh_add_redirect(&g_info.cur_cmd->redirects, ft_strndup_se(tp[1] + 1, 0, j[1]));
		tmp[0] = ft_strdup(tp[1] + j[2]);
		tp[1] = tmp[0];
		ft_memset(c, j[1], sizeof(ft_strlen(c)));
		msh_multiple_clump_redirects(i, c);
	}
	g_info.cur_cmd->args[i] = ft_strjoin(tp[0], tp[1]);
	ft_strdel(&tp[1]);
}

int	msh_help_parse_redirect(char *str, int *index, char *c)
{
	int			i;
	int 		is_cmd;
	int			err;

	i = *index;
	is_cmd = 0;
	if (msh_if_cmd_found(str, index, c))
		is_cmd = 1;
	while (i < g_info.cur_cmd->num_args)
	{
		err = msh_check_syntax(g_info.cur_cmd->args[i], i, c, ft_strlen(g_info.cur_cmd->args[i]));
		if (err == 1)
			msh_multiple_clump_redirects(i, c);
		else if (err == -1)
			return (-1);
		else if (!ft_strcmp(g_info.cur_cmd->args[i], c)
			&& i + 1 < g_info.cur_cmd->num_args)
		{
			if (is_cmd && i + 2 < g_info.cur_cmd->num_args && ft_strcmp(g_info.cur_cmd->args[i + 3] , c) && is_cmd--)
				ft_swap_strs(g_info.cur_cmd->args[0], g_info.cur_cmd->args[i + 3]);
			ft_strdel(&g_info.cur_cmd->args[i]);
			msh_add_redirect(&g_info.cur_cmd->redirects, g_info.cur_cmd->args[i + 1]);
			g_info.cur_cmd->args[i + 1] = NULL;
			i++;
		}
		i++;
	}
	msh_concat_args(g_info.cur_cmd);
	return (*index = 0);
}

int	msh_help_parse_ampersand(char *str, int *length)
{
	(void)str;
	(void)length;
	return (0);
}
