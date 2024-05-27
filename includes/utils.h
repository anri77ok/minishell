#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "tokenization.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_isspace(char c);
int	ft_is_operator(char *s, int i);
int	ft_isalpha(int c);
size_t	ft_strlen(const char *s);
void	print_token_list(t_token *token_list);

#endif