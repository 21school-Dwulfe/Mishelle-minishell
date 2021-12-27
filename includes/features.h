#ifndef FEATURES_H
# define FEATURES_H

int     msh_is_odd_quote(char *str);
void     msh_is_close_odd_quote(char *buf, char *line, char **buf_sd, char *c);
void	msh_check_unclosed_quotes(char *buf, char *line, char *buf_sd, char c);
void    msh_readline(char *prefix, char **dest);

#endif