#ifndef FEATURES_H
# define FEATURES_H

int	msh_is_odd_quote(char *str);
int	msh_is_close_odd_quote(char *buff, char *line);
void	msh_check_unclosed_quotes(char *buff, char *line, char c);
char	*msh_readline(char *prefix);

#endif