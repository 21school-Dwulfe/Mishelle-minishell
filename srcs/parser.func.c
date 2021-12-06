#include "../includes/main.h"

int		msh_check_syntax(char *str, int in, int c, int len_cmp)
{
	int index;

	index = 0;
	if (!ft_strchr(str, c))
		return (0);
	while (str[index] == c)
		index++;
	if (index == len_cmp && in + 1 < g_info.cur_cmd->num_args 
		&& ((ft_strcmp("<", g_info.cur_cmd->args[in + 1] ) && ft_strcmp(">", g_info.cur_cmd->args[in + 1])) ||
		(ft_strcmp("<<", g_info.cur_cmd->args[in + 1]) && ft_strcmp(">>", g_info.cur_cmd->args[in + 1]))))
	{
		g_info.cur_cmd->specials = ERROR;
		msh_error(str, "Mishelle: syntax error near unexpected token",
			g_info.cur_cmd->args[in + 1] , ft_strlen(g_info.cur_cmd->args[in + 1]));
	}
	else if (index > 2)
	{
		g_info.cur_cmd->specials = ERROR;
		msh_error(str, "Mishelle: syntax error near unexpected token",
				str + 2 , index - 2);
	}
	else if (len_cmp > index && ft_abs(c - str[index]) == 2)
	{
		g_info.cur_cmd->specials = ERROR;
		msh_error(str, "Mishelle: syntax error near unexpected token",
				str + 2 , len_cmp - index);
	}
	else if ((index < len_cmp && (str[index + 1] == ';'
		|| (len_cmp > 2 && str[index + 1] == '|')))  )
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
	else if (in == g_info.cur_cmd->num_args -1 && (!ft_strcmp(g_info.cur_cmd->args[in], "<<") || !ft_strcmp(g_info.cur_cmd->args[in], ">>")))
		msh_error(str, "Mishelle: syntax error near unexpected token", "newline", 7);
	if (!g_info.cur_cmd)
		return (-1);
	return (1);
}

int	msh_redirect_parse(void)
{
	t_command	*cmd;
	int			i;
	char		c[4];

	i = 0;
	ft_bzero(c, sizeof(char) * 4);
	cmd = g_info.cur_cmd;
	while (cmd->args[i])
	{
		if (ft_strnstr(cmd->args[i], ">>", 3))
		{
			c[0] = '>';
			c[1] = '>';
		}
		else if (ft_strnstr(cmd->args[i], "<<", 3))
		{
			c[0] = '<';
			c[1] = '<';
		}
		else if (ft_strchr(cmd->args[i], '<'))
			c[0] = '<';
		else if (ft_strchr(cmd->args[i], '>'))
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
	return (msh_redirect_parse());
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

void	msh_multiple_clump_redirects(int i, char *c)
{
	int			j[4];
	char		**tmp;
	t_redirect	*s;
	char		*t;

	tmp = NULL;
	ft_bzero(j, sizeof(int) * 4);
	j[1] = 122 - c[0];
	j[2] = ft_index_of(g_info.cur_cmd->args[i], j[1]);
	if (j[2] < 0)
	{
		tmp = msh_split(g_info.cur_cmd->args[i], c[0]);
		while (tmp[j[3]])
			if ((!ft_strcmp(c, ">") || !ft_strcmp(c, ">>")))
			{
				t = tmp[j[3]++];
				msh_add_redirect(&g_info.cur_cmd->out, t);
			}
			else
			{
				t = tmp[j[3]++];
				msh_add_redirect(&g_info.cur_cmd->input, t);
			}
	}
	else
	{
		msh_add_redirect(&s, ft_strndup_se(g_info.cur_cmd->args[i] + 1, 0, j[1]));
		tmp[0] = ft_strdup(g_info.cur_cmd->args[i] + j[2]);
		g_info.cur_cmd->args[i] = tmp[0];
		msh_multiple_clump_redirects(i, c);
	}
	ft_strdel(&g_info.cur_cmd->args[i]);
}

int	msh_help_parse_redirect(char *str, int *index, char *c)
{
	int			i;
	int 		is_cmd;
	int			err;

	i = *index;
	if (msh_if_cmd_found(str, index, c))
		is_cmd = 1;
	while (i < g_info.cur_cmd->num_args)
	{
		err = msh_check_syntax(g_info.cur_cmd->args[i], i, c[0], ft_strlen(g_info.cur_cmd->args[i]));
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
			msh_add_redirect(&g_info.cur_cmd->out, g_info.cur_cmd->args[i + 1]);
			g_info.cur_cmd->args[i + 1] = NULL;
			i++;
		}
		i++;
	}
	msh_concat_args(g_info.cur_cmd);
	return (*index = 0);
}

void	msh_help_parse_ampersand(char *str, int *length)
{
	(void)str;
	(void)length;
}
