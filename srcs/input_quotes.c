#include "../includes/main.h"

char	*msh_is_odd_quote(char *first, char *str, char *set)
{
	int 		i[2];

	ft_bzero(i, sizeof(int) * 2);
	while (str[i[0]])
	{
		i[1] = 0;
		while (first == 0 && set[i[1]])
		{
			if ((unsigned char)str[i[0]] - (unsigned char)set[i[1]] == 0)
			{
				first = &str[i[0]];
				i[0]++;
				break;
			}
			i[1]++;
		}
		if (first != 0
			&& (unsigned char)str[i[0]] - *(unsigned char *)first == 0)
		{
			first = 0;
			i[0]++;
			break ;
		}
		i[0]++;
	}
	if (first != 0)
		return (first);
	else if (i[0] != (int)ft_strlen(str) && first == 0)
		return (msh_is_odd_quote(first, str + i[0], set));
	else
		return (NULL);
}




char	*msh_strncat(char *new, char *buff, char *dyn_buff)
{
	int	line_l;
	int	buff_l;

	if (!dyn_buff)
		buff_l = ft_strlen(buff);
	else
		buff_l = ft_strlen(dyn_buff);
	line_l = ft_strlen(new);
	if (buff_l + line_l > 1024)
	{
		dyn_buff = ft_realloc(buff, sizeof(char) * (buff_l + line_l + 1));
		ft_strncat(dyn_buff, new, buff_l + line_l + 1);
		return (dyn_buff);
	}
	else
	{
		ft_strncat(buff, new, 1024);
		return (buff);
	}
}

void	msh_is_close_odd_quote(char *buff, char *line, char **buf_sd, char **c)
{
	int	buf_len;

	buf_len = ft_strlen(*buf_sd);
	*buf_sd = msh_strncat(line, buff, *buf_sd);
	*c = msh_is_odd_quote(*c, *buf_sd + buf_len, "'\"");
}

int	msh_check_unclosed_quotes(char *buf, char *line, char *buf_sd, char *c)
{
	char	*quote_type;

	if (c == NULL)
		c = msh_is_odd_quote(NULL, line, "'\"");
	else
		msh_is_close_odd_quote(buf, line, &buf_sd, &c);
	if (c)
	{
		if (QOUTES_ADD_REGIME)
		{
			if (*c == '\'')
				quote_type = "quote> ";
			else
				quote_type = "dquote> ";
			msh_readline(quote_type, &line);
			msh_check_unclosed_quotes(buf, line, buf_sd, c);
			free(line);
		}
		else
			return (msh_unexpected_token_error("unclosed quote", 15));
	}
	return (0);
}
