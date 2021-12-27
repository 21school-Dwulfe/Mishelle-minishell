#include "../includes/main.h"

int		msh_check_syntax(char *str, int in, char *c, t_command *cmd)
{
	int		index;
	int		len_cmp;

	len_cmp = ft_strlen(str);
	index = 0;
	if (!ft_strchr(str, c[0]))
		return (0);
	while (str[index] == c[0])
		index++;
	if (in == cmd->num_args - 1 && cmd->piped && cmd->next == NULL)
		msh_redirect_error("|" , 1);
	else if (index > 2)
		msh_redirect_error(str + 2 , index - 2);
	else if (len_cmp > index && ft_abs(c[0] - str[index]) == 2)
		msh_redirect_error(str + index , len_cmp - index);
	else if ((index < len_cmp && (str[index + 1] == ';'
		|| (in == cmd->num_args - 1 && (str[index + 1] == '|' || (cmd->piped && cmd->next == NULL)))))  )
		msh_redirect_error(str + index , ft_strlen(str) - index);
	else if (in + 1 < cmd->num_args && !ft_strcmp(cmd->args[in], cmd->args[in + 1])
			&& (int)ft_strlen(cmd->args[in]) == index)
		msh_redirect_error(cmd->args[in + 1], ft_strlen(cmd->args[in + 1]));
	else if (in == cmd->num_args -1 && ((!ft_strcmp(cmd->args[in], "<<") || !ft_strcmp(cmd->args[in], ">>"))
		|| (!ft_strcmp(cmd->args[in], "<") || !ft_strcmp(cmd->args[in], ">"))))
		msh_redirect_error("newline", 7);
	if (!cmd)
		return (-1);
	if (!ft_strcmp(str, c))
		return (0);
	if (index == 0 || (index < len_cmp && str[index + 1] != '\0')) 
		return (1);
		
	return (0);
}

char	**msh_concat_args(char **args, int size)
{
	int		i[4];
	char	**tmp;

	tmp = args;
	ft_bzero(i, sizeof(int) * 4);
	i[0] = -1;
	while (args[++i[0]])
		i[3]++;
	i[2] = size;
	while (i[2] >= 0 && args[--i[2]])
		i[3]++;
	if (i[3])
	{
		tmp = ft_calloc(sizeof(char *), (i[3] + 1));
		while (i[1] < i[0])
		{
			tmp[i[1]] =  args[i[1]]; //tmp[k];
			i[1]++;
		}
		while (++i[2] < size)
		{
			tmp[i[1]] = args[i[2]];//;t; //tmp[k];
			i[1]++;
		}
		tmp[i[3]] = NULL;
	}
	return (tmp);
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

/**
 * @brief Cut current redirect & change next type for recursion
 * 
 * @param dest - redirect file name for adding in redirect struct
 * @param src  - income string or previos tail
 * @param tail - tail after first redirect
 * @param c - next type of redirect from list of  < , > , << , >>
 * @return int 1 - requirement to use recursion
 */
int	msh_first_redirect(t_command *cmd, char *src, char **tail, char *c)
{
	int		res;
	int		rr[4];
	char	ch[2];
	char	*dest;

	res = 0;
	ch[0] = '<';
	ch[1] = '>';
	ft_bzero(rr, sizeof(int) * 4);
	while (src[rr[2]] == c[0])
		rr[2]++;
	rr[0] = ft_index_of(src + rr[2], '<');
	rr[1] = ft_index_of(src + rr[2], '>');
	if (rr[0] == -1)
		rr[0] = ft_strlen(src);
	if (rr[1] == -1)
		rr[1] = ft_strlen(src);
	if (rr[0] < rr[1] && rr[0] != -1)
		res = 0;
	if (rr[1] < rr[0] && rr[1] != -1)
		res = 1;
	if (rr[1] == rr[0])
	{
		dest = ft_strdup(src + rr[2]);
		msh_add_redirect(&cmd->redirects, dest, msh_get_specials(c));
	}
	else
	{
		dest = ft_strndup_se(src + rr[2], rr[res], 0);
		msh_add_redirect(&cmd->redirects, dest, msh_get_specials(c));
		ft_bzero(c, sizeof(char) * ft_strlen(c));
		if (src[rr[res] + 1] == src[rr[res]])
			ft_memset(c, ch[res], 2);
		else
			c[0] = ch[res];
		*tail  = ft_strdup(src + rr[2] + ft_strlen(dest));
	}
	return (!(rr[1] == rr[0]));
}

/**
 * @brief Replace prefix before redirect
 * 
 * @param cmd current command
 * @param i index of current arg
 * @param tp temporary string pointers
 * @param c type of closest redirect
 */
void	msh_replace_prefix_before_redirect(t_command *cmd, int i, char **tp, char *c)
{
	if (cmd->args[i][0] != c[0])
	{
		tp[0] = ft_strndup_se(cmd->args[i] , 0, c[0]);
		tp[1] = ft_strdup(cmd->args[i] + ft_index_of(cmd->args[i], c[0]));
		ft_strdel(&cmd->args[i]);
		cmd->args[i] = tp[0];
	}
	else
	{
		tp[1] = cmd->args[i];
		cmd->args[i] = NULL;
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
	char		*tp[4];

	tmp = NULL;
	ft_bzero(j, sizeof(int) * 4);
	ft_bzero(tp, sizeof(char *) * 4);
	j[1] = 122 - c[0];
	j[2] = ft_index_of(cmd->args[i], j[1]);
	msh_replace_prefix_before_redirect(cmd, i, tp, c);
	if (j[2] < 0)
	{
		tmp = ft_split(tp[1], c[0]);
		while (tmp[j[3]])
			msh_add_redirect(&cmd->redirects, tmp[j[3]++], msh_get_specials(c));
	}
	else
	{
		j[3] = msh_first_redirect(cmd, tp[1], &cmd->args[i], c);
		if (j[3])
			msh_clumped_redirects(cmd, i, c);
	}
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
		else if (!ft_strcmp(cmd->args[i], c))
		{
			if (is_cmd && i + 2 < cmd->num_args && ft_strcmp(cmd->args[i + 2] , c) && is_cmd--)
				ft_swap_strs(cmd->args[0], cmd->args[i + 2]);
			ft_strdel(&cmd->args[i]);
			msh_add_redirect(&cmd->redirects, cmd->args[i + 1], msh_get_specials(c));
			cmd->args[i + 1] = NULL;
			cmd->num_args -= 2;
			i++;
		}
		i++;
	}
	cmd->args = msh_concat_args(cmd->args, cmd->num_args);
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
			// if (ft_strnstr(cmd->args[i], ">>", 3)
			// 	&& ((in[1] != -1 && in[0] == -1)
			// 	|| (in[1] != -1 && in[0] != -1 && in[1] < in[0])))
			// 	ft_memset(c, '>', 2);
			// else if (ft_strnstr(cmd->args[i], "<<", 3)
			// 	&& ((in[0] != -1 && in[1] == -1)
			// 	|| (in[0] != -1 && in[1] != -1 && in[0] < in[1])))
			// 	ft_memset(c, '<', 2);
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
