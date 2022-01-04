#ifndef FEATURES_H
# define FEATURES_H

char     *msh_is_odd_quote(char *first, char *str, char *set);
void     msh_is_close_odd_quote(char *buf, char *line, char **buf_sd, char **c);
int 	msh_check_unclosed_quotes(char *buf, char *line, char *buf_sd, char *c);
void    msh_readline(char *prefix, char **dest);

#endif