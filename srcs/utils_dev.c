#include "../includes/main.h"

char *msh_tokens_pseudo_dev(int specials)
{
	char *str;

	if (specials == S_QOUTES)
		str = " S_QOUTES";
	else if (specials == QUOTES)
		str = " QUOTES";
	else if (specials == D_QUOTES)
		str = " D_QUOTES";
	else if (specials == CURL_BRACES)
		str = " CURL_BRACES";
	else if (specials == DOLLAR_BRACES)
		str = " DOLLAR_BRACES";
	else if (specials == DOLLAR)
		str = " DOLLAR";
	else if (specials == SLASH)
		str = " SLASH";
	return (ft_strdup(str));
}