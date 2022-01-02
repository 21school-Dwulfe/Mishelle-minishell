#include "../includes/main.h"

int msh_validation_redirs(char *str, int *i)
{
	int length[4];
	char *ptr;

	ptr = NULL;
	ft_bzero(length, sizeof(int) * 4);
	length[0] = *i;
	while (str[length[0]] == str[*i] && (length[0] - *i) + 1 < 3)
			length[0]++;
	while (str[length[0]] == ' ')
		length[0]++;
	if (str[length[0]] == '<' && str[length[0] + 1] == '>')
		return (msh_unexpected_token_error(&str[length[0]], 2));
	ptr = ft_strchr("|;<>", str[length[0]]);
	if (ptr)
		length[2] = *ptr;
	if(str[length[0]] == '\0')
		return (msh_unexpected_token_error("newline", 7));
	if (!(ft_abs(length[2] - str[*i]) == 2))
		length[3] = 1;
	length[1] = length[0];
	while (str[length[1]] == length[2] && length[1] + length[3] - length[0] < 3)
		length[1]++;
	if (length[2] && length[2] != 'n')
		return (msh_unexpected_token_error(str + length[0],
			length[1] - length[0]));
	return (0);
}
