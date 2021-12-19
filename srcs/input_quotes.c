#include "../includes/main.h"

int	msh_is_odd_quote(char *str)
{
	int		i;
	int		quat[2];
	int		place[2];
	
	i = 0;
	place[0] = ft_strlen(str) + 1;
	place[1] = ft_strlen(str) + 1;
	ft_bzero(quat, sizeof(int) * 2);
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == 34)//"
		{
			quat[0]++;
			if (quat[0] % 2)
				place[0] = (i + 1);
		}
		else if (str[i] == 39)//'
		{
			quat[1]++;
			if (quat[1] % 2)
				place[1] = (i + 1);
		}
		i++;
	}
	if ((quat[0] % 2) == (quat[1] % 2) && (quat[0] % 2) > 0 && (quat[1] % 2) > 0)
	{
		if (place[1] < place[0])
			return (g_info.odd_quote = 39);
		return (g_info.odd_quote = 34);
	}
	else if ((quat[0] % 2) > (quat[1] % 2))
		return (g_info.odd_quote = 34);
	else if ((quat[0] % 2) < (quat[1] % 2))
		return (g_info.odd_quote = 39);
	else
		return (g_info.odd_quote = 0);
}

void	msh_is_close_odd_quote(char *buff, char *line, char **buf_sd, char *c)
{
	int	i;

	i = 0;
	//ft_strlcat(buff, line, 1024);
	*buf_sd = msh_strlcat(buff, line, *buf_sd);
	if (!ft_strchr(line, g_info.odd_quote))
		*c = g_info.odd_quote;
	else
	{
		i = ft_index_of(line, g_info.odd_quote);
		return (msh_is_odd_quote(line + i + 1));
	}
}

void	msh_check_unclosed_quotes(char *buf, char *line, char *buf_sd, char c)
{
	char	*quote_type;

	if (c == 0)
		c = msh_is_odd_quote(line);
	else
		msh_is_close_odd_quote(buf, line, &buf_sd, &c);
	if (c)
	{
		if (c == '\'')
			quote_type = "quote> ";
		else
			quote_type = "dquote> ";
		msh_readline(quote_type, &line);
		msh_check_unclosed_quotes(buf, line, buf_sd, 1);
		free(line);
	}
}
