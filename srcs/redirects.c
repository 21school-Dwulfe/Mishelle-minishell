#include "../includes/main.h"

char	**msh_concat_args(char **args, int size)
{
	int		i[4];
	char	**tmp;

	tmp = NULL;
	ft_bzero(i, sizeof(int) * 4);
	i[0] = -1;
	while (args[++i[0]] && ft_strcmp(args[i[0]] ,""))
		i[3]++;
	i[2] = size;
	while (--i[2] > i[0] && args[i[2]] && ft_strcmp(args[i[2]] ,""))
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
			tmp[i[1]] = args[i[2]]; //;t; //tmp[k];
			i[1]++;
		}
		tmp[i[3]] = NULL;
	}
	return (tmp);
}

void	msh_set_specials(char *c, char *src, int *rr)
{
	char	ch[2];

	ch[0] = '<';
	ch[1] = '>';
	ft_bzero(c, sizeof(char) * ft_strlen(c));
	if (src[rr[rr[4]] + 1] == src[rr[rr[4]]])
		ft_memset(c, ch[rr[4]], 2);
	else
		c[0] = ch[rr[4]];
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

int	msh_prefix_redirect(t_command *cmd, int *i, char *c, int *rr)
{
	if (ft_strcmp(cmd->args[*i], c) == 0)
	{
		ft_strdel(&cmd->args[*i]);
		(*i)++;
		return (1);
	}
	msh_add_redirect(&cmd->redirects, ft_strdup(cmd->args[*i] + rr[2]), rr[3]);
	ft_strdel(&cmd->args[*i]);
	return (0);
}

int	msh_postfix_redirect(t_command *cmd, int *i, char *c, int *rr)
{
	char	*dest;
	char	*hren;

	dest = ft_strndup_se(cmd->args[*i] + rr[2], rr[rr[4]], 0);
	msh_add_redirect(&cmd->redirects, dest, rr[3]);
	msh_set_specials(c, cmd->args[*i] + rr[2], rr);
	hren = ft_strdup(cmd->args[*i] + rr[2] + ft_strlen(dest));
	ft_strdel(&cmd->args[*i]);
	cmd->args[*i] = hren;
	if (ft_strcmp(cmd->args[*i], c) == 0)
	{
		ft_strdel(&cmd->args[*i]);
		(*i)++;
	}
	return (1);
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
int	msh_first_redirect(t_command *cmd, int *i, char *c)
{
	int		rr[5];

	ft_bzero(rr, sizeof(int) * 5);
	while (cmd->args[*i][rr[2]] == c[0])
		rr[2]++;
	rr[0] = ft_index_of(cmd->args[*i] + rr[2], '<', 1);
	rr[1] = ft_index_of(cmd->args[*i] + rr[2], '>', 1);
	if (rr[0] < rr[1])
		rr[4] = 0;
	if (rr[1] < rr[0])
		rr[4] = 1;
	rr[3] = msh_get_specials(c);
	if (rr[1] == rr[0])
		return (msh_prefix_redirect(cmd, i, c, rr));
	else
		return (msh_postfix_redirect(cmd, i, c, rr));
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
void	msh_cut_recursion(t_command *cmd, int i, char *c)
{
	int		j;

	j = 0;
	j = msh_first_redirect(cmd, &i, c);
	if (j == 1)
		msh_cut_recursion(cmd, i, c);
}

void	msh_cut_redirects(t_command *cmd, int i, char *c, int *in)
{
	char	*tp[2];
	
	ft_bzero(tp, sizeof(char *) * 2);
	if (cmd->args[i][0] != c[0])
	{
		tp[0] = ft_strndup_se(cmd->args[i] , 0, c[0]);
		tp[1] = ft_strdup(cmd->args[i] + ft_index_of(cmd->args[i], c[0], 0));
		ft_strdel(&cmd->args[i]);
		cmd->args[i] = tp[1];
	}
	if (ft_strnstr(cmd->args[i], ">>", 3)
		&& ((in[1] != -1 && in[0] == -1)
		|| (in[1] != -1 && in[0] != -1 && in[1] < in[0])))
	ft_memset(c, '>', 2);
	else if (ft_strnstr(cmd->args[i], "<<", 3)
		&& ((in[0] != -1 && in[1] == -1)
		|| (in[0] != -1 && in[1] != -1 && in[0] < in[1])))
	ft_memset(c, '<', 2);
	msh_cut_recursion(cmd, i, c);
	if (tp[0])
	{
		if (i < cmd->num_args && cmd->args[i] == NULL)
			cmd->args[i] = tp[0];
	}
}

void	msh_replace_null_arg(t_command *cmd)
{
	char	**tmp;

	tmp = msh_concat_args(cmd->args, cmd->num_args);
	//ft_arrstr_del(cmd->args, cmd->num_args);
	free(cmd->args);
	cmd->args = tmp;
	cmd->num_args = ft_str_count(cmd->args);
}

int	msh_redirects(t_command *cmd, char *c, int *in)
{
	int	i;

	i = 0;
	while (i < cmd->num_args)
	{
		ft_bzero(c, sizeof(char) * 4);
		in[0] = ft_index_of(cmd->args[i], '<', 0);
		in[1] = ft_index_of(cmd->args[i], '>', 0);
		if ((in[0] != -1 && in[1] == -1)
			|| (in[0] != -1 && in[1] != -1 && in[0] < in[1]))
			c[0] = '<';
		else if ((in[1] != -1 && in[0] == -1)
			|| (in[1] != -1 && in[0] != -1 && in[1] < in[0]))
			c[0] = '>';
		if (in[0] > -1 || in[1] > -1)
		{
			msh_cut_redirects(cmd, i, c, in);
			msh_replace_null_arg(cmd);
			i = 0;
		}
		else
			i++;
	}
	return (0);
}

int	msh_redirects_parse()
{
	char		c[4];
	int			in[4];
	t_command	*cmd;

	cmd = g_info.cur_cmd;
	while (cmd)
	{
		if (msh_redirects(cmd, c, in) == -1)
			return (-1) ;
		cmd = cmd->next;
	}
	return (0);
}
