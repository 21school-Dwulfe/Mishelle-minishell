#include "../includes/main.h"

int		msh_check_syntax(char *str, int in, char *c, t_command *cmd)
{
	int index;
	int len_cmp; 
	
	len_cmp = ft_strlen(str);
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
	if (in == cmd->num_args - 1 && cmd->piped && cmd->next == NULL)
		msh_error( "Mishelle: syntax error near unexpected token", "|" , 1);
	else if (index > 2)
	{
		cmd->specials = ERROR;
		msh_error("Mishelle: syntax error near unexpected token",
				str + 2 , index - 2);
	}
	else if (len_cmp > index && ft_abs(c[0] - str[index]) == 2)
	{
		cmd->specials = ERROR;
		msh_error("Mishelle: syntax error near unexpected token",
				str + index , len_cmp - index);
	}
	else if ((index < len_cmp && (str[index + 1] == ';'
		|| (in == cmd->num_args - 1 && (str[index + 1] == '|' || (cmd->piped && cmd->next == NULL)))))  )
		{
			cmd->specials = ERROR;
			msh_error("Mishelle: syntax error near unexpected token",
					str + index , ft_strlen(str) - index);
		}
	
	else if (in + 1 < cmd->num_args)
	{
		if (in + 1 < cmd->num_args && !ft_strcmp(cmd->args[in], cmd->args[in + 1])
			&& (int)ft_strlen(cmd->args[in]) == index)
		msh_error("Mishelle: syntax error near unexpected token",
			cmd->args[in + 1], ft_strlen(cmd->args[in + 1]));
	}
	else if (in == cmd->num_args -1 && ((!ft_strcmp(cmd->args[in], "<<") || !ft_strcmp(cmd->args[in], ">>"))
		|| (!ft_strcmp(cmd->args[in], "<") || !ft_strcmp(cmd->args[in], ">"))))
		msh_error("Mishelle: syntax error near unexpected token", "newline", 7);
	if (!cmd)
		return (-1);
	if (!ft_strcmp(str, c))
		return (0);
	if (index == 0 || (index < len_cmp && str[index + 1] != '\0')) 
		return (1);
		
	return (0);
}

void	msh_concat_args(t_command *cmd)
{
	int		i;
	int		j;
	int		num;
	int		k;
	char	**tmp;
	char	*t;

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
		cmd->args = ft_calloc(sizeof(char *), (num + 1));
		while (k < i)
		{
			t = tmp[k];
			cmd->args[k] = t; //tmp[k];
			k++;
		}
		while (++j < cmd->num_args)
		{
			t = tmp[j];
			cmd->args[k] = t; //tmp[k];
			k++;
		}
		cmd->args[num] = NULL;
		cmd->num_args = num;
	}
}

int		msh_if_cmd_not_found(t_command *cmd, char *str, int *index, char *c)
{
	(void)str;
	int	len;

	len = ft_strlen(c);
	if (ft_strcmp(cmd->args[0] , c) == 0
		&& cmd->num_args == 3 
		&& *index + len < cmd->num_args)
	{
		ft_swap_strs(cmd->args[0], cmd->args[*index + 2]);
		return (0);
	}
	else if (ft_strcmp(cmd->args[0] , c))
		return (0);
	else
		return (1);
}

int msh_get_specials(char *c)
{
	int index;

	index = ft_strlen(c);
	if (index == 2 && c[0] == '<')
		return (RD_REDIRECT);
	if (index == 1 && c[0] == '<')
		return (R_REDIRECT);
	if (index == 2 && c[0] == '>')
		return (D_REDIRECT);
	if (index == 1 && c[0] == '>')
		return (REDIRECT);
	return (0);
}


int	msh_first_redirect(char *str, char *c)
{
	int r;
	int	rr;

	r = ft_index_of(str, '>');
	rr = ft_index_of(str, '<');
	if (rr < r)
	{
		if (str[r + 1] == '>')
			ft_memset(c, '>', 2);
		return (rr - 1);
	}
	else
	{
		if (str[r + 1] == '>')
			ft_memset(c, '>', 2);
		return (r - 1);
	}
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
void	msh_clumped_redirects(t_command *cmd, int i, char *c)
{
	int			j[4];
	char		**tmp;
	char		*t;
	char		*tp[4];

	tmp = NULL;
	ft_bzero(j, sizeof(int) * 4);
	ft_bzero(tp, sizeof(char *) * 4);
	j[1] = 122 - c[0];
	j[2] = ft_index_of(cmd->args[i], j[1]);
	if (cmd->args[i][0] != c[0])
	{
		tp[0] = ft_strndup_se(cmd->args[i] , 0, j[1]);
		tp[1] = ft_strdup(cmd->args[i] + ft_index_of(cmd->args[i], c[0]));
		ft_strdel(&cmd->args[i]);
	}
	else
		tp[1] = cmd->args[i];
	if (j[2] < 0)
	{
		tmp = ft_split(tp[1], c[0]);
		while (tmp[j[3]])
			{
				t = tmp[j[3]++];
				msh_add_redirect(&cmd->redirects, t, msh_get_specials(c));
			}
	}
	else
	{
		j[1] =  msh_first_redirect(tp[1], c);
		tp[3] =	ft_strndup_se(tp[1] + 1, 0, j[1]);
		msh_add_redirect(&cmd->redirects, tp[3], msh_get_specials(c));
		tmp[0] = ft_strdup(tp[1] + j[2]);
		tp[1] = tmp[0];
		ft_memset(c, j[1], sizeof(ft_strlen(c)));
		ft_strdel(&tp[3]);
		msh_clumped_redirects(cmd, i, c);
	}
	cmd->args[i] = ft_strjoin(tp[0], tp[1]);
	ft_strdel(&tp[1]);
}

int	msh_help_parse_redirect(t_command *cmd, char *arg, int *arg_i, char *c)
{
	int			i;
	int 		is_cmd;
	int			err;

	i = *arg_i;
	is_cmd = 0;
	if (msh_if_cmd_not_found(cmd, arg, arg_i, c))
		is_cmd = 1;
	while (i < cmd->num_args)
	{
		err = msh_check_syntax(cmd->args[i], i, c, cmd);
		if (err == 1)
			msh_clumped_redirects(cmd, i, c);
		else if (err == -1)
			return (-1);
		else if (!ft_strcmp(cmd->args[i], c)
			&& i + 1 < cmd->num_args)
		{
			if (is_cmd && i + 2 < cmd->num_args && ft_strcmp(cmd->args[i + 2] , c) && is_cmd--)
				ft_swap_strs(cmd->args[0], cmd->args[i + 3]);
			ft_strdel(&cmd->args[i]);
			msh_add_redirect(&cmd->redirects, cmd->args[i + 1], msh_get_specials(c));
			cmd->args[i + 1] = NULL;
			i++;
		}
		i++;
	}
	msh_concat_args(cmd);
	return (*arg_i = 0);
}

int	msh_common_parse()
{
	t_command	*cmd;
	int			i;
	char		c[4];
	int			in[4];

	i = 0;
	cmd = g_info.cur_cmd;
	while (cmd)
	{
		while (cmd->args[i])
		{
			ft_bzero(c, sizeof(char) * 4);
			in[0] = ft_index_of(cmd->args[i], '<');
			in[1] = ft_index_of(cmd->args[i], '>');
			if (ft_strnstr(cmd->args[i], ">>", 3)
				&& ((in[1] != -1 && in[0] == -1)
				|| (in[1] != -1 && in[0] != -1 && in[1] < in[0])))
			{
				ft_memset(c, '>', 2);
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
			if (c[0] && msh_help_parse_redirect(cmd, cmd->args[i], &i, c) == -1)
				return (-1);
			i++;
		}
		cmd = cmd->next;
	}
	return(0);
}
